#include <systemc.h>
#include "new_div.cpp"

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

    void run_test() {
        // Initialize signals
        dividend = 123;
        divisor = 7;
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
        assert(Q.read() == 17);
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

        SC_THREAD(run_test);
    }

    ~divider_N_tb() {
        delete dut;
    }
};

int sc_main(int argc, char* argv[]) {
    divider_N_tb tb("tb");
    sc_start(100,SC_NS);
    return 0;
}

