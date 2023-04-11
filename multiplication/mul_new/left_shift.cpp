#include <systemc.h>
#include "const.h"



SC_MODULE(left_shift_N) {
    sc_in<sc_bv<N>> inp;
    sc_in<sc_bv<N>> shift_by;
    sc_out<sc_bv<N+N>> out;
    sc_in<bool> clk, rst;
    sc_in<bool> valid;

    /*void left_shift_func() {
        if (rst) {
            out.write(0);
                    }

	else {
	    if (!valid.read()) {
            out.write(0);
   	    }
	    else {
		    sc_uint<N> shift_val = shift_by.read();
		    if (shift_val == 0) {
                     out.write(inp.read());
                     }
		    else {

                     sc_bv<N+N> out_val;
                     out_val = inp.read();

                     for (int j = N - 1; j >= 0; j--) {
                      out_val[j + shift_val] = out_val[j];
                      if (j == 0) {
                      for (int i = shift_val - 1; i >= 0; i--) {
                      out_val[i] = 0;
                }
            }
        }

        out.write(out_val);
		    }
	    }
	}
    }*/

    void left_shift_func(){
		sc_bv<N+N> temp0;
		sc_bv<N> shift0, valid_high;
		int i, j;

		shift0 = shift_by.read();
		valid_high = valid.read();    
		if(rst){
			out.write(0);
		}
		else {
			if(valid_high != 0b0){     
				if(shift0 == 0b0){
					out.write(inp.read());
				}
				else {
					temp0 = inp.read();
			
					sc_uint<N> k;
					k = shift0;
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

