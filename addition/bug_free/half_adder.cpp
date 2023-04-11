#include "systemc.h"

SC_MODULE(HA) {
	sc_in<bool> a;
	sc_in<bool> b;
	sc_out<bool> sum;
	sc_out<bool> carry;


	/*void xor_gate() {
		sum.write(a.read() ^ b.read());
	}

	void and_gate(){
		carry.write(a.read() & b.read());
	}*/

	void half_adder()
  {
           sum= a xor b ;  
           carry = a and b;	   
  }

	SC_CTOR(HA) {
		SC_METHOD(half_adder);
		sensitive << a << b;

		/*SC_METHOD(xor_gate);
		sensitive << a << b;
		
		SC_METHOD(and_gate);
		sensitive << a << b;*/
	}
};

