#include <systemc.h>

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



