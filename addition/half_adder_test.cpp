#include "systemc.h"
#include "half_adder.cpp"

SC_MODULE(testbench) {
	sc_signal<sc_bv<1>>  a,b;
	sc_signal<sc_bv<1>> sum,carry;

	sc_trace_file *pTracefile;

	void test() {
		srand(time(NULL));
		for (int i=0;i<10;i++) {
			a.write(rand()%4);
			b.write(rand()%4);
			cout<< "value of a " << a.read() <<  " value of b "<< b.read() << " value of sum "<< sum.read() << " value of carry "<< carry.read() << endl;
			wait(1, SC_NS);
		
		}
/*	// Test case 1: a=0, b=0
		a.write(0);
		b.write(0);
		wait(1, SC_NS);
		cout<< "value of a " << a.read() <<  " value of b "<< b.read() << " value of sum "<< sum.read() << " value of carry "<< carry.read() << endl;
		
		// Test case 2: a=0, b=1
		a.write(0);
		b.write(1);
		wait(1, SC_NS);
		cout<< "value of a " << a.read() <<  " value of b "<< b.read() << " value of sum "<< sum.read() << " value of carry "<< carry.read() << endl;
		
		// Test case 3: a=1, b=0
		a.write(1);
		b.write(1);
		wait(2, SC_NS);
		cout<< "value of a " << a.read() <<  " value of b "<< b.read() << " value of sum "<< sum.read() << " value of carry "<< carry.read() << endl;*/
	}

		SC_CTOR(testbench) {
			pTracefile = sc_create_vcd_trace_file("HA_vcd");
			sc_trace(pTracefile, a, "trace_a");
			sc_trace(pTracefile, b, "trace_b");
			sc_trace(pTracefile, sum, "trace_sum");
			sc_trace(pTracefile, carry, "trace_carry");

			
			SC_THREAD(test);
		}

                ~testbench()
		{
			sc_close_vcd_trace_file(pTracefile);
		}
};

int sc_main(int argc, char* argv[]) {
       HA HA1("HALF_ADDER");
       testbench tb("testbench");
       
       HA1.a(tb.a);
       HA1.b(tb.b);
       HA1.sum(tb.sum);
       HA1.carry(tb.carry);
       
       //sc_start(100, SC_NS);
       sc_start();
       //sc_stop();
       
       return 0;
}


