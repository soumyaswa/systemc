#include "systemc.h"
#include "add.cpp"
SC_MODULE(testbench) {
	sc_signal<sc_int<2>> a, b;
	sc_signal<sc_int<2>> f;

	sc_trace_file *pTracefile;


	
	void test() {
		for(int i=0; i<10 ;i++) {
		a.write(rand()%2);
		b.write(rand()%2);
		cout<< "value of a " << a.read() <<  " value of b "<< b.read() << " value of f "<< f.read() << endl;
		wait(1, SC_NS);

		}





		// Test case 1: a=0, b=0
	/*	a.write(0);
		b.write(0);
		wait(1, SC_NS);
	//	assert(f.read() == 0);
		cout<< "value of a " << a.read() <<  " value of b "<< b.read() << " value of f "<< f.read() << endl;
		
		// Test case 2: a=0, b=1
		a.write(0);
		b.write(1);
		wait(1, SC_NS);
		//assert(f.read() == 0);
		cout<< "value of a "<< a.read() <<  " value of b "<< b.read() << " value of f "<< f.read() << endl;

		
		// Test case 3: a=1, b=0
		a.write(1);
		b.write(0);
		wait(2, SC_NS);
		//assert(f.read() == 0);
		cout<< "value of a "<< a.read() <<  " value of b "<< b.read() << " value of f "<< f.read() << endl;

		
		// Test case 4: a=1, b=1
		a.write(1);
		b.write(1);
		wait(4, SC_NS);
		//assert(f.read() == 1);
		cout<< "value of a "<< a.read() <<  " value of b "<< b.read() << " value of f "<< f.read() << endl;

		
		// End of testbench
		//wait(10, SC_NS);
		//sc_stop();*/
	}
	
	SC_CTOR(testbench) {
				
		pTracefile = sc_create_vcd_trace_file("and_vcd");
		sc_trace(pTracefile, a, "trace_a");
		sc_trace(pTracefile, b, "trace_b");
		sc_trace(pTracefile, f, "trace_f");


		SC_THREAD(test);


	}
       
	~testbench()
	{
		sc_close_vcd_trace_file(pTracefile);
	}

};

int sc_main(int argc, char* argv[]) {
	and2 and_gate("and_gate");
	testbench tb("testbench");
	
	//tb.a(and_gate.a);
	and_gate.a(tb.a);
	and_gate.b(tb.b);
        //tb.f(and_gate.f);
	and_gate.f(tb.f);
	
	sc_start(100, SC_NS);
	sc_stop();
	
	return 0;
}

