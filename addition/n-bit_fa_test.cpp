#include "systemc.h"
#include "n-bit_fa.cpp"


int sc_main(int argc, char* argv[]) {
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




