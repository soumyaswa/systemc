#include "systemc.h"

SC_MODULE(HA) {
	sc_in<sc_bv<1>> a;
	sc_in<sc_bv<1>> b;
	sc_out<sc_bv<1>> sum;
	sc_out<sc_bv<1>> carry;


	void xor_gate() {
		sum.write(a.read() ^ b.read());
	}

	void and_gate(){
		carry.write(a.read() & b.read());
	}

	SC_CTOR(HA) {
		SC_METHOD(xor_gate);
		sensitive << a << b;
		
		SC_METHOD(and_gate);
		sensitive << a << b;
	}
};

