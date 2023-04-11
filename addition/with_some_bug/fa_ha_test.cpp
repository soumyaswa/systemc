#include <systemc.h>
#include "fa_ha.cpp"

SC_MODULE(Testbench) {
    sc_out<sc_bv<1>> a;
    sc_out<sc_bv<1>> b;
    sc_out<sc_bv<1>> c_in;
    sc_in<sc_bv<1>> sum;
    sc_in<sc_bv<1>> c_out;

    
    sc_trace_file* tf; 
   
    void test() {
        srand(time(NULL));
        for (int i = 0; i < 10; i++) {
            a.write(rand() % 2);
            b.write(rand() % 2);
            c_in.write(rand() % 2);
            wait(1, SC_NS);
            cout << "a: " << a.read() << ", b: " << b.read() << ", c_in: " << c_in.read() << ", sum: " << sum.read() << ", c_out: " << c_out.read() << endl;
        }
        sc_stop();
    }

    SC_CTOR(Testbench) {
	    tf = sc_create_vcd_trace_file("fa_using_ha");
	    sc_trace(tf, a, "a");
	    sc_trace(tf, b, "b");
	    sc_trace(tf, c_in, "c_in");
	    sc_trace(tf, sum, "sum");
	    sc_trace(tf, c_out, "c_out");

    	    SC_THREAD(test);
	    sensitive << sum << c_out;
    }

    ~Testbench()
	{
	         	sc_close_vcd_trace_file(tf);

	}

};

int sc_main(int argc, char* argv[]) {
    FA fa("fa");
    Testbench tb("tb");

    

    sc_signal<sc_bv<1>> a, b, c_in, sum, c_out;
    fa.a(a);
    fa.b(b);
    fa.c_in(c_in);
    fa.sum(sum);
    fa.c_out(c_out);

    tb.a(a);
    tb.b(b);
    tb.c_in(c_in);
    tb.sum(sum);
    tb.c_out(c_out);

    sc_start();

    return 0;
}



/*int sc_main(int argc, char* argv[]) {
	sc_signal<sc_bv<1>> a;
	sc_signal<sc_bv<1>> b;
	sc_signal<sc_bv<1>> c_in;
	sc_signal<sc_bv<1>> sum;
	sc_signal<sc_bv<1>> c_out;

	FA* fa = new FA("fa");
	fa->a(a);
	fa->b(b);
	fa->c_in(c_in);
	fa->sum(sum);
	fa->c_out(c_out);

	sc_trace_file* tf = sc_create_vcd_trace_file("full_adder_waveform");
	tf->set_time_unit(1, SC_NS);
	sc_trace(tf, a, "a");
	sc_trace(tf, b, "b");
	sc_trace(tf, c_in, "c_in");
	sc_trace(tf, sum, "sum");
	sc_trace(tf, c_out, "c_out");

	// test case 1: 1 + 1 + 1 = 11, carry_out = 1
	a.write("1");
	b.write("1");
	c_in.write("1");
	sc_start(1, SC_NS);
	assert(sum.read() == "1");
	assert(c_out.read() == "1");

	// test case 2: 0 + 0 + 0 = 00, carry_out = 0
	a.write("0");
	b.write("0");
	c_in.write("0");
	sc_start(1, SC_NS);
	assert(sum.read() == "0");
	assert(c_out.read() == "0");

	// test case 3: 1 + 0 + 1 = 10, carry_out = 1
	a.write("1");
	b.write("0");
	c_in.write("1");
	sc_start(1, SC_NS);
	assert(sum.read() == "0");
	assert(c_out.read() == "1");

	// test case 4: 1 + 1 + 0 = 10, carry_out = 1
	a.write("1");
	b.write("1");
	c_in.write("0");
	sc_start(1, SC_NS);
	assert(sum.read() == "0");
	assert(c_out.read() == "1");

	// test case 5: 1 + 0 + 0 = 01, carry_out = 0
	a.write("1");
	b.write("0");
	c_in.write("0");
	sc_start(1, SC_NS);
	assert(sum.read() == "1");
	assert(c_out.read() == "0");

	// test case 6: 0 + 1 + 0 = 01, carry_out = 0
	a.write("0");
	b.write("1");
	c_in.write("0");
	sc_start(1, SC_NS);
	assert(sum.read() == "1");
	assert(c_out.read() == "0");

	// test case 7: 0 + 0 + 1 = 01, carry_out = 0
	a.write("0");
	b.write("0");
	c_in.write("1");
	sc_start(1, SC_NS);
	assert(sum.read() == "1");
	assert(c_out.read() == "0");

	sc_close_vcd_trace_file(tf);
	delete fa;
	return 0;
}*/

