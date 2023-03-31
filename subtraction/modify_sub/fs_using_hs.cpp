#include "systemc.h"

SC_MODULE(HS) {
	sc_in<sc_bv<1>> a;
	sc_in<sc_bv<1>> b;
	sc_out<sc_bv<1>> diff;
	sc_out<sc_bv<1>> borrow;
	sc_in<bool> clk, reset;
       // sc_signal<bool> reset_tmp;

	void half_sun() {
		if(!reset.read()){
			diff.write(a.read() ^ b.read());
			borrow.write((~a.read() & b.read()));
		}
		else {
			diff.write(0);
			borrow.write(0);
		}
	}



         /////////WHILE DOING LIKE THIS THE OUTPUT IS COMMING WRONG 

	/*void xor_gate() {
		if(!reset){
			diff.write(a.read() ^ b.read());
		}
		else {
			diff.write(0);
		}
	}

	void and_gate(){
		if(!reset){
			borrow.write((~a.read() & b.read()));
		}
		else 
		{
			borrow.write(0);
		}
	}*/


	
	SC_CTOR(HS) {

		SC_METHOD(half_sun);
		sensitive << a << b<< clk.pos();
		 sensitive << reset;    //Note: no need to define reset_tmp signal
		
		//reset_signal_is(reset,true);
		/* reset_signal_is(reset,true);
	   // Wait for one clock cycle before generating the reset signal
      		  reset_tmp.write(true);
                  wait(clk.posedge_event());
                  reset_tmp.write(false);
                  reset(reset_tmp);*/
	
	/*	SC_METHOD(xor_gate);
		sensitive << clk.pos();
		sensitive << a << b;
		
		SC_METHOD(and_gate);
	//	sensitive << clk.pos();
		sensitive << a << b;*/
		
		
		}
};


// Full Adder module
SC_MODULE(FS) {
    sc_in<sc_bv<1>> a, b, b_in;
    sc_out<sc_bv<1>> b_out;
    sc_out<sc_bv<1>> diff;
    sc_in<bool> clk, reset;
    //sc_signal<bool> reset_tmp;

    sc_signal<sc_bv<1>> d1;
    sc_signal<sc_bv<1>> bo0, bo1;

    HS* hs1;
    HS* hs2;

    void borrow_out() {	    
	b_out.write(bo1.read() | bo0.read());
    }

    SC_CTOR(FS){

	    hs1 = new HS("hs1");
            hs2 = new HS("hs2");
	
	    hs1->a(a);
            hs1->b(b);
            hs1->diff(d1);
            hs1->borrow(bo0);
	    hs1->clk(clk);
	    hs1->reset(reset);
	    //hs1->b_in(b_in);

	    hs2->a(d1);
            hs2->b(b_in);
            hs2->diff(diff);
            hs2->borrow(bo1);
	    hs2->clk(clk);
	    hs2->reset(reset);
	
            SC_METHOD(borrow_out);
            sensitive << bo0 << bo1;
	    sensitive << reset; 
	   // reset_signal_is(reset, true);
	   // reset_signal_is(hs1->reset, true);
	   // reset_signal_is(hs2->reset, true);

	  /* reset_signal_is(reset,true);
	   // Wait for one clock cycle before generating the reset signal
      		  reset_tmp.write(true);
                  wait(clk.posedge_event());
                  reset_tmp.write(false);
                  reset(reset_tmp);*/



    }
};
