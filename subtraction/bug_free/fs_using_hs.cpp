#include "systemc.h"

SC_MODULE(HalfSubtractor) {
    sc_in<sc_uint<1>> a, b;
    sc_out<sc_uint<1>> difference, borrow;
    sc_in<bool> clk, reset;

    void half_subtractor_process() {
	    if(reset){
		    difference.write(0);
		    borrow.write(0);
	    }
	    else {
		    difference.write(a.read() ^ b.read());        // XOR gate for difference
                    borrow.write((~a.read()) & b.read());     // AND gate for borrow
	    }
    }

    SC_CTOR(HalfSubtractor):
	    a("hs_a"),
	    b("hs_b"),
	    difference("hs_difference"),
	    borrow("hs_borrow"),
	    clk("hs_clk"),
	    reset("hs_reset")
	{
		SC_METHOD(half_subtractor_process);
        	sensitive << a << b;
		sensitive << clk.pos();
		sensitive << reset.pos();
	}
};


// Full Adder module
SC_MODULE(FullSubtractor) {
    sc_in<sc_uint<1>> a, b, c_in;
    sc_out<sc_uint<1>> borrow_out;
    sc_out<sc_uint<1>> difference;
    sc_in<bool> clk, reset;

    sc_signal<sc_uint<1>> difference_i;
    sc_signal<sc_uint<1>> borrow_0, borrow_1;

    HalfSubtractor* hs1;
    HalfSubtractor* hs2;

    void full_subtractor_process() {
	    if(reset) borrow_out.write(0);
	    else borrow_out.write(borrow_1.read() | borrow_0.read());
    }

    SC_CTOR(FullSubtractor):
	    a("fs_a"),
	    b("fs_b"),
	    c_in("fs_c_in"),
	    difference("fs_difference"),
	    borrow_out("fs_borrow"),
	    clk("fs_clk"),
	    reset("fs_reset")
	{
		hs1 = new HalfSubtractor("hs1");
            	hs2 = new HalfSubtractor("hs2");
	
	    	hs1->a(a);
            	hs1->b(b);
            	hs1->difference(difference_i);
            	hs1->borrow(borrow_0);
	    	hs1->clk(clk);
	    	hs1->reset(reset);

            	hs2->a(difference_i);
            	hs2->b(c_in);
            	hs2->difference(difference);
            	hs2->borrow(borrow_1);
	    	hs2->clk(clk);
	    	hs2->reset(reset);
	
            	SC_METHOD(full_subtractor_process);
            	sensitive << borrow_0 << borrow_1;
	}
};

