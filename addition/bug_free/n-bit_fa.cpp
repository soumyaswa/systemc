#include "systemc.h"
#include "fa_ha.cpp"
#include "const.h"

SC_MODULE(N_FullAdder){
	sc_in<sc_uint<N>> a, b;
        sc_in<sc_uint<1>> c_in;	
        sc_out<sc_uint<1>> c_out;
        sc_out<sc_uint<N>> sum;
        sc_in<bool> clk, reset;
	
	int i, j, k;

	sc_signal<sc_uint<1>> carry[N];
	sc_signal<sc_uint<1>> sig_a[N], sig_b[N];
        sc_signal<sc_uint<1>> sig_sum[N];


	void n_fulladder_func(){                             
		sc_bv<N> a0, b0;
		a0 = a.read();
		b0 = b.read();
	        		
		for(j = 0; j < N; j++){
			sig_a[j] = a0[j].get_bit(0);          
			sig_b[j] = b0[j].get_bit(0);
		}
	}

	void n_sum_func(){                                
		sc_uint<N> sum_vec;
		sc_bv<1> sum_temp;
			
		for(k = 0; k < N; k++){
			sum_temp = sig_sum[k];
			sum_vec[k] = sum_temp.get_bit(0);			
		}
		sum.write(sum_vec);
	}

	
	SC_CTOR(N_FullAdder):
		a("FA_N_a"),
	    	b("FA_N_b"),
	    	c_in("FA_N_cin"),
	    	sum("FA_N_sum"),
	    	c_out("FA_N_c_out"),
	    	clk("fA_N_clk"),
	    	reset("FA_N_reset")
	{
		SC_METHOD(n_fulladder_func);      
		sensitive << clk.pos();
		sensitive << reset.pos();
		sensitive << a << b << c_in;


		FullAdder* FA[N];
		for(i = 0; i<N; i++){             
			FA[i] = new FullAdder(sc_gen_unique_name("FA"));
			FA[i]->a(sig_a[i]);
			FA[i]->b(sig_b[i]);

			if(i==0){
				FA[i]->c_in(c_in);
			}
			else{
				FA[i]->c_in(carry[i]);
				
			}

			FA[i]->sum(sig_sum[i]);      

			if(i==N-1){
				FA[i]->c_out(c_out);
			}
			else{
				FA[i]->c_out(carry[i + 1]);
			}

			FA[i]->clk(clk);
			FA[i]->reset(reset);
			
		}

		SC_METHOD(n_sum_func);
		for(int l = 0; l < N; l++){       
			sensitive << sig_sum[l];
		}
	}
};

