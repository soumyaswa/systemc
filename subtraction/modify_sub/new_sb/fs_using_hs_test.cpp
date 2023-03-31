#include "systemc.h"
//#include "fs_using_hs.cpp"
#include "n_bit_fs.cpp"



SC_MODULE(FS_TEST){

    sc_clock clk;
    sc_signal<bool> reset;
    sc_signal<sc_bv<1>> a[N], b[N], diff[N], b_in;
    sc_signal<sc_bv<1>> b_out;

    sc_bv<N> a_combined, b_combined, diff_combined;


    // Instantiate the N-bit sub
    //sc_trace_file *pTracefile;
    sc_trace_file *tf;

    n_bit_fs* sub;
    //FS_TEST test("test");


    void stimulus();


    SC_CTOR(FS_TEST):
	    clk("clk", 10, SC_NS)
	{
	    // Connect the signals
	    sub = new n_bit_fs("sub");

            sub->clk(clk);
            sub->reset(reset);

	    for(int i = 0; i< N; i++){
		    sub->a[i](a[i]);
            	    sub->b[i](b[i]);
            	    sub->diff[i](diff[i]);
	    }

	    sub->b_in(b_in);
	    sub->b_out(b_out);

	   

            //Open VCD file
	    /*tf = sc_create_vcd_trace_file("waveform");
	    // Add signals to trace
	    sc_trace(tf, test.clk, "clk");
	    sc_trace(tf, test.reset, "reset");
	    for (int i = 0; i < N; i++) {
		    sc_trace(tf, test.a[i], "a_" + std::to_string(i));
		    sc_trace(tf, test.b[i], "b_" + std::to_string(i));
		    sc_trace(tf, test.diff[i], "diff_" + std::to_string(i));
	    }
	    sc_trace(tf, test.b_in, "b_in");
	    sc_trace(tf, test.b_out, "b_out");*/

	    SC_THREAD(stimulus);
    }

    ~FS_TEST(){

	    
	    sc_close_vcd_trace_file(tf);
	     delete sub;
	    
    }
};


void FS_TEST::stimulus(){
	
	srand(time(NULL));
	while (true){
		cout << "start" <<endl;

		//reset.write(rand() % 2);
		cout << " reset = " << reset.read() << endl;
		
		for(int i = 0; i<N;i++){
			a[i].write(rand() % 2);
		        b[i].write(rand() % 2);
		}
	        b_in = rand() % 2;

		cout << "a = ";
		for(int i = N-1; i>=0 ; i--){
			cout << a[i];
		}
		cout << "  ";

		cout << "b = ";
		for(int i = N-1; i>=0 ; i--){
			cout << b[i];
		}
		cout << "  ";
		cout << " b_in = " << b_in.read() << endl;

		cout << "diff = ";
		for(int i = N-1; i>=0 ; i--){
			cout << diff[i];
		}
		cout << " ";

		cout << " b_out = " << b_out.read() << endl;
	
		cout << "end " << endl;
		//wait(0.01, SC_NS);   //added this because of in the wave form i am geting started from the 00 which is not needed but when reset is 1 is taking some extra datas



		// Combine signals for tracing
		sc_bv<N> a_combined, b_combined, diff_combined;
		// Update combined signals
		
		for (int i = 0; i < N; i++) {
                a_combined[i] = a[i].read().get_bit(0);
                b_combined[i] = b[i].read().get_bit(0);
                diff_combined[i] = diff[i].read().get_bit(0);
		
		}

		tf = sc_create_vcd_trace_file("waveform");

		// Add signals to trace
		sc_trace(tf, clk, "clk");
	       	sc_trace(tf, reset, "reset");
		sc_trace(tf, b_in, "b_in");
	       	sc_trace(tf, b_out, "b_out");
		
		// Trace combined signals
		sc_trace(tf, a_combined, "a_combined");
	       	sc_trace(tf, b_combined, "b_combined");
	       	sc_trace(tf, diff_combined, "diff_combined");


		wait(5, SC_NS);
	}
}


int sc_main(int argc, char* argv[]){
       FS_TEST test("test");
       sc_start(50, SC_NS);
       sc_stop();
       return 0;
} 




/*SC_MODULE(Testbench) {
    sc_signal<sc_bv<1>> a;
    sc_signal<sc_bv<1>> b;
    sc_signal<sc_bv<1>> b_in;
    sc_signal<sc_bv<1>> diff;
    sc_signal<sc_bv<1>> b_out;
    sc_clock clk;
    sc_signal<bool> reset;

    
    sc_trace_file* tf; 
   
    void test() {
        srand(time(NULL));
        for (int i = 0; i < 10; i++) {
            a.write(rand() % 2);
            b.write(rand() % 2);
            b_in.write(rand() % 2);
            wait(1, SC_NS);
            cout << "a: " << a.read() << ", b: " << b.read() << ", b_in: " << b_in.read() << ", diff: " << diff.read() << ", b_out: " << b_out.read() << endl;
        }
        sc_stop();
    }

    SC_CTOR(Testbench): clk("clk", 10, SC_NS)
{
	    tf = sc_create_vcd_trace_file("fs_using_hs");
	    sc_trace(tf, a, "a");
	    sc_trace(tf, b, "b");
	    sc_trace(tf, b_in, "b_in");
	    sc_trace(tf, diff, "diff");
	    sc_trace(tf, b_out, "b_out");
	    sc_trace(tf, clk, "clk");
	    sc_trace(tf, reset, "reset");

    	    SC_THREAD(test);
	    sensitive << diff << b_out;
    }

    ~Testbench()
	{
	         	sc_close_vcd_trace_file(tf);

	}

};

int sc_main(int argc, char* argv[]) {
    FS fs("fs");
    Testbench tb("tb");

    
    //sc_clock clk;
    //sc_signal<bool> reset;

   // sc_signal<sc_bv<1>> a, b, b_in, diff, b_out;
    fs.a(tb.a);
    fs.b(tb.b);
    fs.b_in(tb.b_in);
    fs.diff(tb.diff);
    fs.b_out(tb.b_out);
    fs.clk(tb.clk);
    fs.reset(tb.reset);
    
    sc_start();

    return 0;
}*/






//tb for half subtractor
/*SC_MODULE(testbench) {
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
}*/


