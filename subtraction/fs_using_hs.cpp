#include "systemc.h"

SC_MODULE(HS) {
	sc_in<sc_bv<1>> a;
	sc_in<sc_bv<1>> b;
	sc_out<sc_bv<1>> diff;
	sc_out<sc_bv<1>> borrow;
	sc_in<bool> clk, reset;



	void xor_gate() {
		if(!reset){
			diff.write(a.read() ^ b.read());
		}
		else {
			diff.write(0);
		}
	}

	void and_gate(){
		if(!reset){
			borrow.write((~a.read() & b.read()));
		}
		else 
		{
			borrow.write(0);
		}
	}


	
	SC_CTOR(HS) {
		
	
		SC_METHOD(xor_gate);
	//	sensitive << clk.pos();
		sensitive << a << b;
		
		SC_METHOD(and_gate);
	//	sensitive << clk.pos();
		sensitive << a << b;
	}
};


// Full Adder module
/*SC_MODULE(FA) {
	sc_in<sc_bv<1>> a;
	sc_in<sc_bv<1>> b;
	sc_in<sc_bv<1>> c_in;
	sc_out<sc_bv<1>> sum;
	sc_out<sc_bv<1>> c_out;

	sc_in<bool> clk, reset;


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
		ha1->clk(clk);
		ha1->reset(reset);



		ha2->a(s1);
		ha2->b(c_in);
		ha2->sum(sum);
		ha2->carry(c2);
		ha2->clk(clk);
		ha2->reset(reset);


		SC_METHOD(carry_out);
		sensitive << c1 << c2;

		//delete ha1;
		//delete ha2;
	}

	void carry_out() {
		c_out.write(c1.read() | c2.read());
	}*/
	/*~FA() {
		delete ha1;
		delete ha2;
	}*/
	
//};
