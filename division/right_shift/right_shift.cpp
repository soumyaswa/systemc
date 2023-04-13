#include <systemc.h>
#include "const.h"

SC_MODULE(right_shift_N) {
	sc_in<sc_biguint<N>> inp;
	sc_in<sc_biguint<S>> shift_by;
	sc_out<sc_biguint<N>> out;
	sc_in<bool> clk;

	void right_shift_func(){
		sc_biguint<N> temp0;
		sc_biguint<S> shift0;
		int i, j;

		shift0 = shift_by.read();

		if(shift0 == 0b0){
			out.write(inp.read());
		}
		else {
			temp0 = inp.read();
			
			sc_uint<S> k;
			k = shift0;
			for(i = 0; i < k; i++){
				for(j = 0; j < N; j++){
					if(j!=N-1){
						temp0[j] = temp0[j+1];
					}
					else {
						temp0[j] = 0;
					}
				}
			}
			out.write(temp0);
		}			
	}

	SC_CTOR(right_shift_N){
		SC_METHOD(right_shift_func);
		sensitive << clk.pos();
		sensitive << inp << shift_by;
	}
};





////////////////////////-----------------------------NOTE--------------------------------------------------------------------------
//HERE IF WE DO "sc_bv<N>" AND DOING FOR THE 32 BITS ITS NOT CREATING ANY ERROR BUT 
//IF WE CHANGE IT TO "sc_biguint<N>" ITS GIVING ME ERROR FOR EXCEDDING BOUNDARY RANGE
//-----------------------------ERROR MESSAGE------------------------------------------
//Error: (E5) out of bounds: sc_biguint[_base] bit selection: index = 32 violates 0 <= index <= 31
//--------------------------------RESOLVE THIS ERROR--------------------------------------------
//
//CONVERT THE "sc_biguint" TO "sc_big_biguint" THEN ITS RUNNING FOR 32 BIT ITS BECOMES FLEXIBLE.
