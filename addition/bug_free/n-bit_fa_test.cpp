#include "systemc.h"
#include "n-bit_fa.cpp"


SC_MODULE(FA_TEST){

    sc_clock clk;
    sc_signal<sc_uint<N>> a, b;
    sc_signal<sc_uint<1>> c_in;	
    sc_signal<sc_uint<1>> c_out;
    sc_signal<sc_uint<N>> sum;
    sc_signal<bool> reset;

    // Instantiate the N-bit adder
    sc_trace_file *tp;

    N_FullAdder* adder;


    void stimulus();


    SC_CTOR(FA_TEST):
	    a("fa_test_a"),
	    b("fa_test_b"),
	    c_in("fa_test_cin"),
	    sum("fa_test_sum"),
	    c_out("fa_test_c_out"),
	    reset("fa_test_reset"),
	    clk("clk", 10, SC_NS)
	{
	    // Connect the signals
	    adder = new N_FullAdder("adder");

            adder->clk(clk);
            adder->reset(reset);
	    adder->a(a);
            adder->b(b);	    
	    adder->sum(sum);
	    adder->c_in(c_in);
	    adder->c_out(c_out);



	    
                
	    tp = sc_create_vcd_trace_file("N_full_Adder_waves");
                
	    sc_trace(tp, a, "trace_a");
	    sc_trace(tp, b, "trace_b");
	    sc_trace(tp, sum, "trace_sum");
	    sc_trace(tp, clk, "clk");
            sc_trace(tp, reset, "reset");
            sc_trace(tp, c_in, "c_in");
            sc_trace(tp, c_out, "c_out");
	    


	    SC_THREAD(stimulus);
    }

    ~FA_TEST(){
	    sc_close_vcd_trace_file(tp);
	    
    }
};	


void FA_TEST::stimulus(){
	
	srand(time(NULL));	
	while (true){		
		reset.write(rand() % 2);
		
		/*a.write(rand()%2);
		b.write(rand()%2);*/
		a.write(rand());
		b.write(rand());
		c_in.write(rand() % 2);
		
		cout << " " << endl;
		cout << "********************************  test run " << " ***********************************" << endl;
		cout << " " << endl;
		cout << "rst = "  << reset.read() << "; a = "  << a.read() << "; b = "  << b.read() << "; c_in = " << c_in.read() << "; sum = " << sum.read() << "; c_out = "<< c_out.read() << endl;
				
		wait(10, SC_NS);
	}
}


int sc_main(int argc, char* argv[]){
       FA_TEST test("test");
       sc_start(100, SC_NS);
       sc_stop();
       return 0;
} 


