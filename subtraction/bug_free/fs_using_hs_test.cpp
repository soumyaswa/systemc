#include "systemc.h"
//#include "fs_using_hs.cpp"
#include "n_bit_fs.cpp"



SC_MODULE(FS_TEST){

    sc_clock clk;
    sc_signal<sc_uint<N>> a, b;
    sc_signal<sc_uint<1>> c_in;	
    sc_signal<sc_uint<1>> borrow_out;
    sc_signal<sc_uint<N>> difference;
    sc_signal<bool> reset;

    // Instantiate the N-bit adder
    sc_trace_file *tf;

    N_FullSubtractor* adder;


    void stimulus();


    SC_CTOR(FS_TEST):
	    a("fa_test_a"),
	    b("fa_test_b"),
	    c_in("fa_test_cin"),
	    difference("fa_test_difference"),
	    borrow_out("fa_test_borrow_out"),
	    reset("fa_test_reset"),
	    clk("clk", 10, SC_NS)
	{
	    // Connect the signals
	    adder = new N_FullSubtractor("adder");

            adder->clk(clk);
            adder->reset(reset);
	    adder->a(a);
            adder->b(b);	    
	    adder->difference(difference);
	    adder->c_in(c_in);
	    adder->borrow_out(borrow_out);



	                    
	    tf = sc_create_vcd_trace_file("N_full_Subtractor_waves");
                
	    sc_trace(tf, a, "trace_a");
	    sc_trace(tf, b, "trace_b");
	    sc_trace(tf, difference, "trace_difference");
	    sc_trace(tf, clk, "clk");
            sc_trace(tf, reset, "reset");
            sc_trace(tf, c_in, "c_in");
            sc_trace(tf, borrow_out, "borrow_out");
	   

	    SC_THREAD(stimulus);
    }

    ~FS_TEST(){
	    sc_close_vcd_trace_file(tf);
	    
    }
};	


void FS_TEST::stimulus(){
	
		srand(time(NULL));	
	
	while (true){		
		reset.write(rand() % 2);
		
		a.write(rand());
		b.write(rand());
		c_in.write(rand() % 2);
				
		cout << " " << endl;
		cout << "********************************  test run " << " ***********************************" << endl;
		cout << " " << endl;
		cout << "rst = " << reset.read() << "; a = " << a.read() << "; b = " << b.read() << "; c_in = " << c_in.read() << "; difference = " << difference.read() << "; borrow_out = " << borrow_out.read() << endl;
				
		wait(10, SC_NS);
	}
}


int sc_main(int argc, char* argv[]){
       FS_TEST test("test");
       sc_start(100, SC_NS);
       sc_stop();
       return 0;
} 


