#include "systemc.h"

SC_MODULE(HA) {
	sc_in<sc_logic> a,b;
	sc_out<sc_logic> sum,carry;

	void xor_gate() {
		sum.write(a.read() ^ b.read());
	}

	void and_gate() {
		carry.write(a.read() & b.read());
	}

	SC_CTOR(HA) {
		SC_METHOD(xor_gate);
		sensitive << a << b;

		SC_METHOD(and_gate);
		sensitive << a << b;

		//sum.initialize(false);
		//carry.initialize(false);
	}
};





/*SC_MODULE(half_adder) {
	sc_in<bool> a;
	sc_in<bool> b;
	sc_out<bool> sum;
	sc_out<bool> carry;
	
	sc_signal<bool> s;
	sc_signal<bool> c;
	
	void xor_gate() {
		s.write(a.read() ^ b.read());
	}
	
	void and_gate() {
		c.write(a.read() & b.read());
	}
	
	
	SC_CTOR(half_adder) {
		SC_METHOD(xor_gate);
		sensitive << a << b;
		
		SC_METHOD(and_gate);
		sensitive << a << b;
		
		sum.initialize(false);
		carry.initialize(false);
	}
};*/


/*SC_MODULE(half_adder) {
  sc_in<bool> a;
  sc_in<bool> b;
  sc_out<bool> sum;
  sc_out<bool> carry;

  sc_signal<bool> s;
  sc_signal<bool> c;

  void xor_gate() {
    sc_uint<1> a_val, b_val;
    a_val = a.read();
    b_val = b.read();

    s.write(a_val.xor(b_val));
  }

  void and_gate() {
    sc_uint<1> a_val, b_val;
    a_val = a.read();
    b_val = b.read();

    c.write(a_val.and(b_val));
  }

  SC_CTOR(half_adder) {
    SC_METHOD(xor_gate);
    sensitive << a << b;

    SC_METHOD(and_gate);
    sensitive << a << b;

    sum.initialize(0);
    carry.initialize(0);
  }
};*/



