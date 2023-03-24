#include "systemc.h"
#include "fa_ha.cpp"


SC_MODULE(FullAdder16) {
    sc_in<sc_bv<1>> a[16];
    sc_in<sc_bv<1>> b[16];
    sc_in<sc_bv<1>> c_in;
    sc_out<sc_bv<1>> sum[16];
    sc_out<sc_bv<1>> c_out;
    
    sc_in<bool> clk, reset;

    FA* fa[16];
    sc_signal<sc_bv<1>> c[16];

    SC_CTOR(FullAdder16) {
        // Instantiate 16 1-bit Full Adder modules
        for (int i = 0; i < 16; i++) {
            fa[i] = new FA(sc_gen_unique_name("fa"));
            fa[i]->a(a[i]);
            fa[i]->b(b[i]);
            //fa[i]->c_in(c[i]);
            
            if (i == 0) {
                fa[i]->c_in(c_in);
            }
            else {
                fa[i]->c_in(c[i]);
		//fa[i]->c_in(fa[i-1]->c_in);
            }
	    fa[i]->sum(sum[i]);
	    if(i==15){
		    fa[i]->c_out(c_out);
	    }
	    else {
		    fa[i]->c_out(c[i+1]);
		    //fa[i]->c_out(fa[i+1]->c_out);
	    }
	    fa[i]->clk(clk);
	    fa[i]->reset(reset);


        }

        
    }
};


