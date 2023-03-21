#include <systemc.h>
#include "fa2.cpp"


int sc_main(int argc, char* argv[]) {

    sc_clock clk("clk", 10, SC_NS);
    sc_signal<bool> reset;
    sc_signal<sc_lv<8>> a, b, sum;

    // Instantiate the N-bit adder
    NBitAdder n_bit_adder("n_bit_adder");

    // Connect the signals
    n_bit_adder.clk(clk);
    n_bit_adder.reset(reset);
    n_bit_adder.a(a);
    n_bit_adder.b(b);
    n_bit_adder.sum(sum);

    // Open VCD file
    sc_trace_file *trace_file = sc_create_vcd_trace_file("waveforms");
    sc_trace(trace_file, clk, "clk");
    sc_trace(trace_file, reset, "reset");
    sc_trace(trace_file, a, "a");
    sc_trace(trace_file, b, "b");
    sc_trace(trace_file, sum, "sum");

    // Initialize the input signals
    reset = true;
    a = "00000000";
    b = "00000000";

    // Reset
    sc_start(20, SC_NS);
    reset = false;

    // Test addition of 1 + 2
    a = "00000001";
    b = "00000010";
    sc_start(20, SC_NS);
    assert(sum.read() == "00000011");

    // Test addition of 127 + 1
    a = "01111111";
    b = "00000001";
    sc_start(20, SC_NS);
    assert(sum.read() == "10000000");

    // Close the trace file and exit
    sc_close_vcd_trace_file(trace_file);
    return 0;
}

