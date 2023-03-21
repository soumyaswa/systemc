#include "systemc.h"
#include "full_adder.cpp"
#include "const_fa.h"


SC_MODULE(testbench) {
  sc_out<bool> a;
  sc_out<bool> b;
  sc_out<bool> cin;
  sc_in<bool> sum;
  sc_in<bool> cout;

  void test() {
    wait(1, SC_NS);
    srand(time(NULL)); // seed random number generator

    for (int i = 0; i < 10; i++) {
      // generate random inputs
      bool a_val = rand() % 2;
      bool b_val = rand() % 2;
      bool cin_val = rand() % 2;
      
      // apply inputs
      a.write(a_val);
      b.write(b_val);
      cin.write(cin_val);

      // wait for outputs to stabilize
      wait(1, SC_NS);

      // check outputs
      bool expected_sum = (a_val ^ b_val) ^ cin_val;
      bool expected_cout = (a_val & b_val) | ((a_val ^ b_val) & cin_val);

      assert(sum.read() == expected_sum);
      assert(cout.read() == expected_cout);
    }

    sc_stop(); // stop simulation
  }

  SC_CTOR(testbench) {
    SC_THREAD(test);
  }
};

int sc_main(int argc, char *argv[]) {
  //const int n_bits = 4;

  full_adder fa("fa", n_bits);
  testbench tb("tb");

  sc_signal<bool> a;
  sc_signal<bool> b;
  sc_signal<bool> cin;
  sc_signal<bool> sum;
  sc_signal<bool> cout;

  fa.a(a);
  fa.b(b);
  fa.cin(cin);
  fa.sum(sum);
  fa.cout(cout);

  tb.a(a);
  tb.b(b);
  tb.cin(cin);
  tb.sum(sum);
  tb.cout(cout);

  sc_start();

  return 0;
}

