#include "systemc.h"
#include "fs_using_hs.cpp"
#include "const.h"

SC_MODULE(n_bit_fs) {
    sc_in<sc_bv<1>> a[N];
    sc_in<sc_bv<1>> b[N];
    sc_in<sc_bv<1>> b_in;
    sc_out<sc_bv<1>> diff[N];
    sc_out<sc_bv<1>> b_out;
   sc_signal<bool> reset_tmp;
 
    sc_in<bool> clk, reset;

    FS* fs[N];
    HS* hs2[N];
    sc_signal<sc_bv<1>> temp_borrow[N];

    void reset_handler() {
        // Wait for one clock cycle before generating the reset signal
        reset_tmp.write(true);
        wait(clk.posedge_event());
        reset_tmp.write(false);

        // Reset all full adder and half sun modules
        for (int i = 0; i < N; i++) {
            fs[i]->reset_signal_is(true);
        }
        hs2->reset_signal_is(true);

        wait(clk.posedge_event());

        // Release the reset signal
        reset_tmp.write(true);
        wait(clk.posedge_event());
        reset_tmp.write(false);

        for (int i = 0; i < N; i++) {
            fs[i]->reset_signal_is(false);
        }
        hs2->reset_signal_is(false);
    }
    /*SC_CTOR(n_bit_fs) {
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
		
            }
	    fs[i]->diff(diff[i]);
	    if(i==N-1){
		    fs[i]->b_out(b_out);
	    }
	    else {
		    fs[i]->b_out(temp_borrow[i+1]);
		    
	    }
	    fs[i]->clk(clk);
	    fs[i]->reset(reset);
	    fs[i]->reset_tmp = false;
            
	    	    }
	    SC_METHOD(reset_signal);
        sensitive << clk.posedge_event();
        async_reset_signal_is(reset, true);	    
	    

        }*/
//	reset_signal_is(reset,true);
	   // Wait for one clock cycle before generating the reset signal
      		  /*reset_tmp.write(true);
                  wait(clk.posedge_event());
                  reset_tmp.write(false);
                  reset(reset_tmp);*/	


        
   // };
   //
  SC_CTOR(n_bit_fs) {
        // Instantiate 16 1-bit Full Adder modules
        for (int i = 0; i < N; i++) {
            fs[i] = new FS(sc_gen_unique_name("fs"));
            fs[i]->a(a[i]);
            fs[i]->b(b[i]);

            if (i == 0) {
                fs[i]->b_in(b_in);
            }
            else {
                fs[i]->b_in(temp_borrow[i]);
            }

            fs[i]->diff(diff[i]);

            if (i == N-1) {
                fs[i]->b_out(b_out);
            }
            else {
                fs[i]->b_out(temp_borrow[i+1]);
            }

            fs[i]->clk(clk);

            // Disable the reset signal for now
            fs[i]->reset_signal_is(false);
        }

        for (int i = 0; i < 16; i++) {
    hs2[i] = new HS("hs2_" + to_string(i));
}
for (int i = N-1; i >= 0; i--) {
    hs2[i]->a(diff[i]);
    hs2[i]->b(b_out[i]);
    hs2[i]->diff(diff[i]);
    hs2[i]->borrow(temp_borrow[i]);
    hs2[i]->clk(clk);
    hs2[i]->reset_signal_is(false);
}
        SC_METHOD(reset_handler);
        sensitive << reset.posedge_event();
    }
};


