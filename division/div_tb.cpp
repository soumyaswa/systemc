#include <systemc.h>
//#include "new_div.cpp"
#include "div.cpp"

SC_MODULE(divider_N_tb) {
    sc_clock clk;
    sc_signal<bool> rst;
    sc_signal<sc_biguint<N>> dividend;
    sc_signal<sc_biguint<N>> divisor;
    sc_signal<sc_biguint<1>> req;
    sc_signal<sc_biguint<N>> Q;
    sc_signal<sc_biguint<N>> R;
    sc_signal<sc_biguint<1>> ready;
    sc_signal<sc_biguint<1>> exception;

    divider_N* dut;
     // Open trace file
        sc_trace_file* tf = sc_create_vcd_trace_file("trace");

    /*void run_test() {
        // Initialize signals
       // dividend = 15;
       // divisor = 2;
        srand(time(NULL)); // Seed the random number generator
        dividend = rand() % (1 << N); // Generate a random N-bit number
        divisor = rand() % (1 << N); // Generate a random N-bit number
        
        req = 0;
        rst = 1;
        wait(1, SC_NS);
        rst = 0;
        wait(1, SC_NS);
        req = 1;
        wait(1, SC_NS);
        // Wait until the divider is done
        while (ready.read() == 0) {
            wait(1, SC_NS);
        }
        // Check the result
        //assert(Q.read() == 1);
	cout<< "Current simulation time: " << sc_time_stamp() << " reset =  " << rst.read()<< " dividend =  " << dividend.read() << " divisor =  " << divisor.read() << " Q =  "<< Q.read() <<" R="<< R.read()<< endl;
    }*/
 void run_test() {
        
        for (int i = 0; i < 10; i++) {
            // Initialize signals with random values
            dividend = rand();
            divisor = rand();
            req = 0;
            rst = rand() % 2; // random reset
            wait(1, SC_NS);
            rst = 0;
            wait(1, SC_NS);
            req = rand() % 2; // random req
            wait(1, SC_NS);
            // Wait until the divider is done
            while (ready.read() == 0) {
                wait(1, SC_NS);
            }
            // Check the result
            //assert(Q.read() == 1);
            cout << "Current simulation time: " << sc_time_stamp() << " reset = " << rst.read() << " req = " << req.read()<< " dividend = " << dividend.read() << " divisor = " << divisor.read() << " Q = " << Q.read() << " R = " << R.read() << endl;
            wait(10, SC_NS);
	    // Dump signals to trace file
                }
 }
    

    SC_CTOR(divider_N_tb)
        : clk("clk", 1, SC_NS)
    {
        dut = new divider_N("dut");
        dut->dividend(dividend);
        dut->divisor(divisor);
        dut->Q(Q);
        dut->R(R);
        dut->req(req);
        dut->ready(ready);
        dut->exception(exception);
        dut->rst(rst);
        dut->clk(clk);

	sc_trace(tf, clk, "clk");
            sc_trace(tf, rst, "rst");
            sc_trace(tf, dividend, "dividend");
            sc_trace(tf, divisor, "divisor");
            sc_trace(tf, req, "req");
            sc_trace(tf, Q, "Q");
            sc_trace(tf, R, "R");
            sc_trace(tf, ready, "ready");
            sc_trace(tf, exception, "exception");
       

        SC_THREAD(run_test);
    }

    ~divider_N_tb() {
        //delete dut;

        // Close trace file
        sc_close_vcd_trace_file(tf);

    }
};

int sc_main(int argc, char* argv[]) {
    divider_N_tb tb("tb");
    sc_start(100,SC_NS);
    //sc_stop();
    return 0;
}

