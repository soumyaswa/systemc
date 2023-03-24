#include "systemc.h"
#include "n-bit_fa.cpp"


SC_MODULE(FA_TEST){

    sc_clock clk;
    sc_signal<bool> reset;
    sc_signal<sc_bv<1>> a[N], b[N], sum[N], c_in;
    sc_signal<sc_bv<1>> c_out;

    // Instantiate the N-bit adder
    //sc_trace_file *pTracefile;

    FullAdder16* adder;


    void stimulus();


    SC_CTOR(FA_TEST):
	    clk("clk", 10, SC_NS)
	{
	    // Connect the signals
	    adder = new FullAdder16("adder");

            adder->clk(clk);
            adder->reset(reset);

	    for(int i = 0; i< N; i++){
		    adder->a[i](a[i]);
            	    adder->b[i](b[i]);
            	    adder->sum[i](sum[i]);
	    }

	    adder->c_in(c_in);
	    adder->c_out(c_out);

	   

            //Open VCD file
           /*pTracefile = sc_create_vcd_trace_file("waveforms");
	    
            sc_trace(pTracefile, clk, "clk");
            sc_trace(pTracefile, reset, "reset");
	    for(int i = 0; i< N; i++){
                sc_trace(pTracefile, a[i], "a"+ std::to_string(i));
                sc_trace(pTracefile, b[i], "b"+ std::to_string(i));
                sc_trace(pTracefile, sum[i], "sum"+ std::to_string(i));
	    }
            sc_trace(pTracefile, c_in, "c_in");
            sc_trace(pTracefile, c_out, "c_out");*/

	    SC_THREAD(stimulus);
    }

    ~FA_TEST(){
	    //sc_close_vcd_trace_file(pTracefile);
	    /*for(i = 0; i<N; i++){
			delete FA[i];
		}*/
	    //delete adder;
	    
    }
};


void FA_TEST::stimulus(){
	
	srand(time(NULL));
	while (true){
		cout << "start" <<endl;

		reset.write(rand() % 2);
		cout << " reset = " << reset.read() << endl;
		
		for(int i = 0; i<N;i++){
			a[i].write(rand() % 2);
		        b[i].write(rand() % 2);
		}
	        c_in = rand() % 2;

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
		cout << " c_in = " << c_in.read() << endl;

		cout << "sum = ";
		for(int i = N-1; i>=0 ; i--){
			cout << sum[i];
		}
		cout << " ";

		cout << " c_out = " << c_out.read() << endl;
	
		cout << "end " << endl;
		wait(10, SC_NS);
	}
}


int sc_main(int argc, char* argv[]){
       FA_TEST test("test");
       sc_start(100, SC_NS);
       sc_stop();
       return 0;
} 


/*int sc_main(int argc, char* argv[]) {
    sc_signal<sc_bv<1>> a[N];
    sc_signal<sc_bv<1>> b[N];
    sc_signal<sc_bv<1>> c_in;
    sc_signal<sc_bv<1>> sum[N];
    sc_signal<sc_bv<1>> c_out;
    sc_signal<bool> clk, reset;

    // Initialize inputs
    //a.write(1010101010101010);
    //b[0] = 
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
	    a[i].write(rand() % 2);
	    b[i].write(rand() % 2);
    }
    c_in = rand() % 2;

    // Instantiate FullAdder16 module
    FullAdder16 fulladder("fulladder");
    for (int i = 0; i < N; i++) {
        fulladder.a[i](a[i]);
        fulladder.b[i](b[i]);
        fulladder.sum[i](sum[i]);
    }
    fulladder.c_in(c_in);
    fulladder.c_out(c_out);
    fulladder.clk(clk);
    fulladder.reset(reset);


    // Simulate for 10 ns
    sc_start(10, SC_NS);

    // Change inputs and continue simulating for another 10 ns
    //c_in = 1;
    //sc_start(10, SC_NS);

    // Print out results
    cout << "Inputs: a = ";
    for (int i = N-1; i >= 0; i--) {
        cout << a[i];
    }
    cout << ", b = ";
    for (int i = N-1; i >= 0; i--) {
        cout << b[i];
    }
    cout << ", c_in = " << c_in << std::endl;
    cout << "Outputs: sum = ";
    for (int i = N-1; i >= 0; i--) {
        cout << sum[i];
    }
    cout << ", c_out = " << c_out << std::endl;

    return 0;
}
*/



