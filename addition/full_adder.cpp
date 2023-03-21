#include "systemc.h"
#include "const_fa.h"

SC_MODULE(half_adder) {
  sc_in<bool> a;
  sc_in<bool> b;
  sc_out<bool> sum;
  sc_out<bool> carry;

  void xor_gate() {
    sum.write(a.read() ^ b.read());
  }

  void and_gate() {
    carry.write(a.read() & b.read());
  }

  SC_CTOR(half_adder) {
    SC_METHOD(xor_gate);
    sensitive << a << b;

    SC_METHOD(and_gate);
    sensitive << a << b;
  }
};

SC_MODULE(full_adder) {
  sc_in<bool> a;
  sc_in<bool> b;
  sc_in<bool> cin;
  sc_out<bool> sum;
  sc_out<bool> cout;

  sc_vector<half_adder> half_adders;

  SC_HAS_PROCESS(full_adder);

  full_adder(sc_module_name name, int n_bits)
  : sc_module(name), half_adders("half_adders", n_bits) {
    half_adders[0].a(a);
    half_adders[0].b(b);
    half_adders[0].sum(sum);
    half_adders[0].carry(half_adders[1].a);

    for (int i = 1; i < n_bits - 1; i++) {
      half_adders[i].a(half_adders[i-1].carry);
      half_adders[i].b(b);
      half_adders[i].sum(half_adders[i-1].sum);
      half_adders[i].carry(half_adders[i+1].a);
    }

    half_adders[n_bits-1].a(half_adders[n_bits-2].carry);
    half_adders[n_bits-1].b(b);
    half_adders[n_bits-1].sum(half_adders[n_bits-2].sum);
    half_adders[n_bits-1].carry(cout);
  }
};


