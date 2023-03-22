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


// Full Adder module
SC_MODULE(FA) {
	sc_in<sc_bv<1>> a;
	sc_in<sc_bv<1>> b;
	sc_in<sc_bv<1>> c_in;
	sc_out<sc_bv<1>> sum;
	sc_out<sc_bv<1>> c_out;

	sc_signal<sc_bv<1>> s1;
	sc_signal<sc_bv<1>> c1;
	sc_signal<sc_bv<1>> c2;

	HA* ha1;
	HA* ha2;

	SC_CTOR(FA) {
		ha1 = new HA("ha1");
		ha2 = new HA("ha2");

		ha1->a(a);
		ha1->b(b);
		ha1->sum(s1);
		ha1->carry(c1);

		ha2->a(s1);
		ha2->b(c_in);
		ha2->sum(sum);
		ha2->carry(c2);

		SC_METHOD(carry_out);
		sensitive << c1 << c2;

		//delete ha1;
		//delete ha2;
	}

	void carry_out() {
		c_out.write(c1.read() | c2.read());
	}
	~FA() {
		delete ha1;
		delete ha2;
	}
	
};
