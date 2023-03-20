#include <systemc.h>
SC_MODULE(and2){
	sc_in<sc_int<2>> a,b;
	sc_out<sc_int<2>> f;
	
	void func(){
		f.write(a.read() & b.read());
	}
	SC_CTOR(and2){
		SC_METHOD(func);
		sensitive << a <<b;
	}
};
