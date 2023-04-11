#include "systemc.h"
#include "full_adder.cpp"


SC_MODULE(FA_tb) {
  sc_out<sc_bv<1>> a;
  sc_out<sc_bv<1>> b;
  sc_out<sc_bv<1>> cin;
  sc_in<sc_bv<1>> sum;
  sc_in<sc_bv<1>> carry;
  sc_in<bool> clk;
  sc_in<bool> reset;

  void test() {
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
      a.write(rand() % 2);
      b.write(rand() % 2);
      cin.write(rand() % 2);
      //wait();
      cout << "@" << sc_time_stamp() << std::endl;
      cout << "a = " << a.read() << ", b = " << b.read() << ", cin = " << cin.read() << endl;
      cout << "sum = " << sum.read() << ", carry = " << carry.read() << endl;
      wait(10, SC_NS);
    }
  }

  SC_CTOR(FA_tb) {
    SC_THREAD(test);
    sensitive << clk.pos();
    sensitive << a << b << cin;
  }
};

int sc_main(int argc, char* argv[]) {
  FA_tb tb("tb");
  FA fa("fa");

  sc_signal<sc_bv<1>> a;
  sc_signal<sc_bv<1>> b;
  sc_signal<sc_bv<1>> cin;
  sc_signal<sc_bv<1>> sum;
  sc_signal<sc_bv<1>> carry;
  sc_signal<bool> clk;
  sc_signal<bool> reset;

  tb.a(a);
  tb.b(b);
  tb.cin(cin);
  tb.sum(sum);
  tb.carry(carry);
  tb.clk(clk);
  tb.reset(reset);

  fa.a(a);
  fa.b(b);
  fa.cin(cin);
  fa.sum(sum);
  fa.carry(carry);
  fa.clk(clk);
  fa.reset(reset);

  reset.write(1);
  sc_start(1, SC_NS);
  reset.write(0);
  clk.write(1);

  sc_start(100, SC_NS);
  sc_stop();

  return 0;
}

