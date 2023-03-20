#include <systemc.h>
//#include <cstdlib>

SC_MODULE(and2){
	sc_in<bool> a;
	sc_in<bool> b;
	sc_out<bool> f;
	sc_in<bool> clk;
	sc_in<bool> clr;

	void func(){
		if(clr) f.write(0);
		else f.write(a.read() && b.read());
	}

	SC_CTOR(and2){
		SC_METHOD(func){        /// sc_method is like @always
			//sensitive << a << b;
			sensitive << clk.pos();
			sensitive << clr.pos();
		}
	}
};


