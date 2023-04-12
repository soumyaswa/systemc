#include "systemc.h"
#include "const.h"


//------------------- ADDER MODULE --------------------------------
SC_MODULE(half_adder){
	sc_in<sc_uint<3*N>> a;
	sc_in<sc_uint<2*N>> b;
        sc_out<sc_uint<3*N>> sum;
	sc_in<bool> rst, clk;

	void h_adder(){
		sc_uint<3*N> a0 = a.read();    
		sc_uint<3*N> b0 = b.read();
		sc_uint<3*N> s0;		        
              
		if(rst){
			s0 = 0;
		}
		else {
			s0 = a0 + b0;    		}
		sum.write(s0);
	}

	SC_CTOR(half_adder):
		a("ha_a"),
		b("ha_b"),
		sum("ha_sum"),
		rst("ha_rst"),
		clk("ha_clk")
	{
		SC_METHOD(h_adder);
		sensitive << a << b;
		sensitive << clk.pos();
		sensitive << rst.pos();
	}
};

