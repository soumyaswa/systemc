#include <systemc.h>
#include "left_shift.cpp"


SC_MODULE(left_shift_N_tb) {
    sc_signal<sc_bv<N>> inp;
    sc_signal<sc_bv<N>> shift_by;
    sc_clock clk;
    sc_signal<bool> rst;
    sc_signal<bool> valid;
    sc_signal<sc_bv<N+N>> out;
    
    // Module instance
    left_shift_N dut;

    sc_trace_file *tf;


    // Testbench process
    void tb_process() {
	    srand(time(NULL));
        while(true){
        // Randomly generate input values
        inp.write(rand() % (1 << N));
        shift_by.write(rand() % (N+1));
        valid.write(rand() % 2);
         

	/*inp.write(rand());
        shift_by.write(rand() );
        valid.write(rand() % 2);*/      ///while doing for 32 bit getting segementation fault


        // Wait for a few clock cycles
        /*for (int i = 0; i < 3; i++) {
            clk.write(false);
            wait(1, SC_NS);
            clk.write(true);
            wait(1, SC_NS);
        }
         cout << "BEFORE WAIT " << endl;

        // Wait for the output value to be updated
        wait(out.value_changed_event());*/
	

        // Print the input and output values
        cout << "inp = " <<  hex << inp.read() << ", shift_by = " << shift_by.read() << ", valid = " << valid.read() << endl;
        cout << "out = " << out.read() << endl;
	wait(10,SC_NS);
	}
    }

    
    SC_CTOR(left_shift_N_tb): dut("dut") ,
	
	clk("clk", 10, SC_NS)
	{
        
        dut.inp(inp);
        dut.shift_by(shift_by);
        dut.out(out);
        dut.clk(clk);
        dut.rst(rst);
        dut.valid(valid);

        SC_THREAD(tb_process);
        sensitive << clk ;
        dont_initialize();

        
        // Add waveform tracing
        tf = sc_create_vcd_trace_file("left_waveform");
        sc_trace(tf, clk, "clk");
        sc_trace(tf, rst, "rst");
        sc_trace(tf, inp, "inp");
        sc_trace(tf, shift_by, "shift_by");
        sc_trace(tf, valid, "valid");
        sc_trace(tf, out, "out");
    }

    // Destructor
    ~left_shift_N_tb() {
        sc_close_vcd_trace_file(tf);
    }
};

int sc_main(int argc, char* argv[]) {
    left_shift_N_tb tb("tb");

       sc_start(100, SC_NS);

    return 0;
}

