#include "systemc.h"
#include "fs_using_hs.cpp"

SC_MODULE(testbench) {
	sc_signal<sc_bv<1>>  a,b;
	sc_signal<sc_bv<1>> diff,borrow;
	sc_signal<bool> clk, reset;


	sc_trace_file *pTracefile;

	void test() {
		srand(time(NULL));
		for (int i=0;i<10;i++) {
			a.write(rand()%4);
			b.write(rand()%4);
			cout<< "value of a " << a.read() <<  " value of b "<< b.read() << " value of diff "<< diff.read() << " value of borrow "<< borrow.read() << endl;
			wait(1, SC_NS);
		
		}
/*	// Test case 1: a=0, b=0
		a.write(0);
		b.write(0);
		wait(1, SC_NS);
		cout<< "value of a " << a.read() <<  " value of b "<< b.read() << " value of diff "<< diff.read() << " value of borrow "<< borrow.read() << endl;
		
		// Test case 2: a=0, b=1
		a.write(0);
		b.write(1);
		wait(1, SC_NS);
		cout<< "value of a " << a.read() <<  " value of b "<< b.read() << " value of diff "<< diff.read() << " value of borrow "<< borrow.read() << endl;
		
		// Test case 3: a=1, b=0
		a.write(1);
		b.write(1);
		wait(2, SC_NS);
		cout<< "value of a " << a.read() <<  " value of b "<< b.read() << " value of diff "<< diff.read() << " value of borrow "<< borrow.read() << endl;*/
	}

		SC_CTOR(testbench) {
			pTracefile = sc_create_vcd_trace_file("HS_vcd");
			sc_trace(pTracefile, a, "trace_a");
			sc_trace(pTracefile, b, "trace_b");
			sc_trace(pTracefile, diff, "trace_diff");
			sc_trace(pTracefile, borrow, "trace_borrow");
			sc_trace(pTracefile, clk, "clk");
			sc_trace(pTracefile, reset, "reset");


			
			SC_THREAD(test);
		}

                ~testbench()
		{
			sc_close_vcd_trace_file(pTracefile);
		}
};

int sc_main(int argc, char* argv[]) {
       HS HS1("HSLF_SUB");
       testbench tb("testbench");
       
       HS1.a(tb.a);
       HS1.b(tb.b);
       HS1.diff(tb.diff);
       HS1.borrow(tb.borrow);
       HS1.clk(tb.clk);
       HS1.reset(tb.reset);
       //sc_start(100, SC_NS);
       sc_start();
       //sc_stop();
       
       return 0;
}


