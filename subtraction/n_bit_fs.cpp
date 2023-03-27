#include "systemc.h"
#include "fs_using_hs.cpp"
#include "const.h"

SC_MODULE(n_bit_fs) {
    sc_in<sc_bv<1>> a[N];
    sc_in<sc_bv<1>> b[N];
    sc_in<sc_bv<1>> b_in;
    sc_out<sc_bv<1>> diff[N];
    sc_out<sc_bv<1>> b_out;
    
    sc_in<bool> clk, reset;

    FS* fs[N];
    sc_signal<sc_bv<1>> temp_borrow[N];

    SC_CTOR(n_bit_fs) {
        // Instantiate 16 1-bit Full Adder modules
        for (int i = 0; i < N; i++) {
            fs[i] = new FS(sc_gen_unique_name("fs"));
            fs[i]->a(a[i]);
            fs[i]->b(b[i]);
            //fs[i]->b_in(c[i]);
            
            if (i == 0) {
                fs[i]->b_in(b_in);
            }
            else {
                fs[i]->b_in(temp_borrow[i]);
		//fs[i]->b_in(fs[i-1]->b_in);
            }
	    fs[i]->diff(diff[i]);
	    if(i==N-1){
		    fs[i]->b_out(b_out);
	    }
	    else {
		    fs[i]->b_out(temp_borrow[i+1]);
		    //fs[i]->b_out(fs[i+1]->b_out);
	    }
	    fs[i]->clk(clk);
	    fs[i]->reset(reset);


        }

        
    }
};


