#include <systemc.h>
#include "half_adder.cpp"
#include "left_shift.cpp"
//#include "const.h"

//-------------------multiplication -----------------------------


SC_MODULE(multiplier_N) {                            
	sc_in<sc_biguint<N>> multiplicand;
	sc_in<sc_biguint<N>> multiplier;
	sc_out<sc_biguint<3*N>> mul_op;
	sc_in<bool> clk, rst;

	int i, j, k;
	
	sc_signal<sc_biguint<2*N>> ls_out[N];
	sc_signal<sc_biguint<3*N>> temp_mul_op[N];
	sc_signal<sc_biguint<N>> temp_shift[N];
	sc_signal<sc_biguint<N>> temp_valid[N];


	void multiplier_func(){
		sc_bv<N> temp_multiplier;
		temp_multiplier = multiplier.read();    
		sc_bv<N> s0[N];
		sc_bv<N> v1[N];
		
	        for(j = 0; j < N; j++){
			if(j==0) {
				temp_mul_op[j] = 0; 
			}

			if(temp_multiplier[j] == 1){             
				s0[j] = j;           
				v1[j] = 1;            		
			}
			else {
				s0[j] = 0;            
				v1[j] = 0;           
			}
			temp_shift[j].write(s0[j]);
			temp_valid[j].write(v1[j]);
		}
	}

	SC_CTOR(multiplier_N):
		multiplicand("mul_multiplicand"),
		multiplier("mul_multiplier"),
		mul_op("mul_mul_op"),
		rst("mul_rst"),
		clk("mul_clk")
	{		
		SC_METHOD(multiplier_func);
		sensitive << clk.pos();
		sensitive << multiplicand << multiplier;
		
		left_shift_N* ls_N[N];                            
		for(i = 0; i<N; i++){
			ls_N[i] = new left_shift_N(sc_gen_unique_name("LS"));
			ls_N[i]->clk(clk);
			ls_N[i]->rst(rst);
			ls_N[i]->inp(multiplicand);
			ls_N[i]->valid(temp_valid[i]);               ///   required , we want only the output of left shift for which multiplier input bit is high  
			ls_N[i]->shift_by(temp_shift[i]);            ///   shift by index number of multiplier bit which is high 
			ls_N[i]->out(ls_out[i]);		 ///   getting the output of left shift and storing in a signal of vector 
			}

		half_adder* ha[N];                               ///   connecting adder module 
		for(k = 0; k<N; k++){
			ha[k] = new half_adder(sc_gen_unique_name("HA"));
			ha[k]->clk(clk);
			ha[k]->rst(rst);
			
			ha[k]->a(temp_mul_op[k]);               ///   for first iteration input is 0 and for next interations temp_prduct will be the sum of previous results 
			ha[k]->b(ls_out[k]);                     ///   output of left_shift 
			if(k!=N-1) ha[k]->sum(temp_mul_op[k+1]);///   store sum in next address location so that for next interation(k+1) input 1 for sum will be the same as current iteration(k).
			else ha[k]->sum(mul_op);                ///   if its the last iteration(depends on size of input) than store the final sum in mul_op.
		}
	}
};




////------------------------------------NOTE------------------------------------------------
//ERROR:
//Error: (E5) out of bounds: sc_uint[_base] initialization: length = 96 violates 1 <= length <= 64
//
//WHEN I AM USING "sc_uint" ITS GIVING ME OUTOF MEMORY(BOUNDRY) ISSUE AS: FAULT BECAUSE IT ONLY SUPPORTS UPTO 64 BITS AND I AM GIVING 32 AS INPUT AND IT WILL GOES UPTO 94 .
//
//NOW I HAVE CHANGE THE "sc_uint" to "sc_biguint" where it will support upto 64 ,128......that's why now i am geting the output


