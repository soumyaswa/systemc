#include "systemc.h"
#include "const.h"
#include "mul.cpp"
#include "sub.cpp"
#include "add.cpp"
#include "right_shift.cpp"
#include "comp.cpp"

SC_MODULE(Divider) {
  sc_in<bool> clk, rstn, req;
  sc_in<sc_biguint<N>> Dividend, Divisor;
  sc_out<sc_biguint<N>> Q, R;
  sc_out<sc_biguint<N>> ready, exception;

  sc_signal<sc_biguint<N>> D, d, Counter, RefCounter, refD, refd, Num_cycles;
  sc_signal<sc_biguint<1>> g, e;
  sc_signal<sc_biguint<N>> Dr, temp1, temp2, temp3;

  GE ge;
  Mul M;
  Sub S;
  Add A;
  Rshift Rs;

  enum state {START, COMPARE};
  state s;

  void state_machine() {
    while (true) {
      wait();

      if (!rstn) {
        s = START;
        RefCounter = 0;
        Counter = 0;
        exception = 0;
        ready = 0;
        Num_cycles = 0;
      }
      else {
	      if (s == START) {
		      if (req) {
			      if (Divisor == 0) {
				      exception = 1;
				      ready = 1;
				      s = START;
				      Num_cycles = 1;
			      }
			      else if (Divisor == 1) {
				      exception = 0;
				      ready = 1;
				      s = START;
				      //Q = Dividend;
				      Q.write(Dividend.read());
				      Num_cycles = 1;
			      }
			      else {
				      s = COMPARE;
				      refD = Dividend.read();
				      refd = Divisor.read();
				      D = Dividend.read();
				      d = Divisor.read();
				      Num_cycles = 1;
			      }
		      } 
		      else {
			      s = START;
			      ready = 0;
			      Num_cycles = 0;
		      }
	      }
	      else if (s == COMPARE) {
		      Num_cycles = Num_cycles + 1;
		      
		      ge.A = D;
		      ge.B = d;
		      g = ge.G;
		      e = ge.E;
		      
		      if (e==1 || g ==1) {
			      Rs.i = D;
			      Dr = Rs.o;
			      D = Dr;
			      
			      Counter = (Counter == 0) ? 1 : Counter << 1;
		      
		      } 
		      else {
			      if (Counter != 0) {
				      M.A = refd;
				      M.B = Counter;
				      temp1 = M.O;
				      
				      S.A = refD;
				      S.B = temp1;
				      temp2 = S.O;
				      
				      A.A = RefCounter;
				      A.B = Counter;
				      temp3 = A.O;
				      
				      RefCounter = temp3;
				      Counter = 0;
				      D = temp2;
				      refD = temp2;
			      }
			      else {
				      Q = RefCounter;
				      ready = 1;
				      s = START;
			      }
		      }
	      }
      }
    }
  }

  SC_CTOR(Divider) : ge("ge"), M("M"), S("S"), A("A"), Rs("Rs") {
    SC_CTHREAD(state_machine, clk.pos());
    ge.A(D);
    ge.B(d);
    ge.G(g);
    ge.E(e);
  }
};

