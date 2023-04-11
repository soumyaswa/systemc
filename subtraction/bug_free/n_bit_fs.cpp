#include "systemc.h"
#include "fs_using_hs.cpp"
#include "const.h"

SC_MODULE(N_FullSubtractor){
	sc_in<sc_uint<N>> a, b;
	sc_in<sc_uint<1>> c_in;
	
        sc_out<sc_uint<1>> borrow_out;
        sc_out<sc_uint<N>> difference;
        sc_in<bool> clk, reset;

	sc_signal<sc_uint<1>> temp_borrow[N];
	sc_signal<sc_uint<1>> sig_a[N], sig_b[N];
        sc_signal<sc_uint<1>> sig_difference[N];
	
	int i, j, k;

	void n_fullSubtractor_func(){                             
		sc_bv<N> a0, b0;
		a0 = a.read();
		b0 = b.read();
	        		
		for(j = 0; j < N; j++){
			sig_a[j] = a0[j].get_bit(0);          
			sig_b[j] = b0[j].get_bit(0);
		}
	}

	void n_difference_func(){                                
		sc_uint<N> difference_vec;
		sc_bv<1> difference_temp;
			
		for(k = 0; k < N; k++){
			difference_temp = sig_difference[k];
			difference_vec[k] = difference_temp.get_bit(0);			
		}
		difference.write(difference_vec);
	}


	SC_CTOR(N_FullSubtractor):
		a("fsN_a"),
	    	b("fsN_b"),
	    	c_in("fsN_c_in"),
	    	difference("fsN_difference"),
	    	borrow_out("fsN_borrow"),
	    	clk("fsN_clk"),
	    	reset("fsN_reset")
	{

		SC_METHOD(n_fullSubtractor_func);      
		sensitive << clk.pos();
		sensitive << reset.pos();
		sensitive << a << b << c_in;

		
		FullSubtractor* FS[N];
		for(i = 0; i<N; i++){
			FS[i] = new FullSubtractor(sc_gen_unique_name("FS"));
			FS[i]->a(sig_a[i]);
			FS[i]->b(sig_b[i]);

			if(i==0){
				FS[i]->c_in(c_in);
			}
			else{
				FS[i]->c_in(temp_borrow[i]);
				
			}

			FS[i]->difference(sig_difference[i]);

			if(i==N-1){
				FS[i]->borrow_out(borrow_out);
			}
			else{
				FS[i]->borrow_out(temp_borrow[i+1]);
			}

			FS[i]->clk(clk);
			FS[i]->reset(reset);
			
		}
		SC_METHOD(n_difference_func);
		for(int l = 0; l < N; l++){       
			sensitive << sig_difference[l];
		}
	}

};


