#include "right_s_with_range.cpp"

SC_MODULE(testbench) {
    sc_signal< sc_uint<N> > i;
    sc_signal<sc_uint<S>> shift_by;
    sc_signal< sc_uint<N> > o;

    SC_CTOR(testbench) {
        SC_THREAD(run);
    }

    void run() {
	    srand(time(NULL));
	    while (true){
      	    i = rand() ;
	    shift_by = rand();
       	    cout << "input = " << i.read() << " shift_by = " << shift_by.read() << " output = " << o.read() << endl;
	    wait(10,SC_NS);
            
           }
    }
};

int sc_main(int argc, char* argv[]) {
	Rshift dut("dut");
	testbench tb("tb");
	
	dut.i(tb.i);
	dut.shift_by(tb.shift_by);
	dut.o(tb.o);
	
	// Start simulation
         sc_start(100, SC_NS);
         sc_stop();

          return 0;
}



