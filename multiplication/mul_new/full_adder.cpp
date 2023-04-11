#include "systemc.h"

SC_MODULE(FA) {
	sc_in<sc_bv<1>> a;
	sc_in<sc_bv<1>> b;
	sc_in<sc_bv<1>> cin;
	sc_out<sc_bv<1>> sum;
	sc_out<sc_bv<1>> carry;
	sc_in<bool> clk, reset;



	void full_adder() {
		if(!reset){
			sum.write(a.read() ^ b.read() ^ cin.read());
			carry.write((a.read() & b.read()) | (b.read() & cin.read()) | (a.read() & cin.read()));

		}
		else {
			sum.write(0);
			carry.write(0);

		}
	}



	
	SC_CTOR(FA) {
		
	
		SC_METHOD(full_adder);
		sensitive << clk.pos();
		sensitive << a << b <<cin;
		
		}
};

