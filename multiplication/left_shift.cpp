#include <systemc.h>
//#include "const.h"

//--------------------LEFT SHIFT MODULE-----------------------------
SC_MODULE(left_shift_N) {
    sc_in<sc_biguint<N>> inp;
    sc_in<sc_biguint<N>> shift_by;
    sc_out<sc_biguint<2*N>> out;
    sc_in<bool> clk, rst;
    sc_in<sc_biguint<N>> valid;

    void left_shift_func(){
		sc_biguint<2*N> temp0;
		sc_biguint<N> temp_shift, valid_high;
		int i, j;

		temp_shift = shift_by.read();
		valid_high = valid.read();    
		if(rst){
			out.write(0);
		}
		else {
			if(valid_high != 0b0){     
				if(temp_shift == 0b0){
					out.write(inp.read());
				}
				else {
					temp0 = inp.read();
			
					sc_uint<N> k;
					k = temp_shift;
					for(j = N-1; j >= 0; j--){
						temp0[j+k] = temp0[j];     
						if(j==0) {
							for(i = k-1; i >= 0; i--){     
								temp0[i] = 0;
							}
						}
					}			
					out.write(temp0);
				}
			}
			else{                                    
				out.write(0);
			}

		}			
	}


    SC_CTOR(left_shift_N):
        inp("inp"),
        shift_by("shift_by"),
        out("out"),
        valid("valid"),
        clk("clk"),
        rst("rst")
    {
        SC_METHOD(left_shift_func);
        sensitive << clk.pos() << rst.pos();
        sensitive << inp << shift_by << valid;
    }
};




