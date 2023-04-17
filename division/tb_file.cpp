#include <systemc.h>
//#include "add.cpp"
//#include "sub.cpp"
//#include "mul.cpp"
#include "comp.cpp"

//------------------tb for comp------------------------
SC_MODULE(Testbench) {
    sc_signal< sc_uint<N> > A, B;
    sc_signal<bool> G, E;

    GE dut;

    void test() {
        A.write(10);
        B.write(5);

        wait(1, SC_NS);

        if (G.read() != 1 || E.read() != 0) {
            cout << "Error: G is " << G.read() << " and E is " << E.read() << endl;
        }
	else { 
		cout << "GTR_correct: G is " << G.read() << " and E is " << E.read() << endl;
	}
        A.write(5);
        B.write(5);

        wait(1, SC_NS);

        if (G.read() != 0 || E.read() != 1) {
            cout << "Error: E is " << G.read() << " and E is " << E.read() << endl;
        }
	else { 
		cout << "EQL_correct: G is " << G.read() << " and E is " << E.read() << endl;
	}


        A.write(5);
        B.write(10);

        wait(1, SC_NS);

        if (G.read() != 0 || E.read() != 0) {
            cout << "Error: L is " << G.read() << " and E is " << E.read() << endl;
        }
	else { 
		cout << "LES_correct: G is " << G.read() << " and E is " << E.read() << endl;
	}

    }

    SC_CTOR(Testbench)
        : dut("dut")
    {
        dut.A(A);
        dut.B(B);
        dut.G(G);
        dut.E(E);

        SC_THREAD(test);
    }
};

int sc_main(int argc, char* argv[]) {
    Testbench tb("testbench");
    sc_start(10,SC_NS);
    return 0;
}


//-------------------tb for mul-------------------------
/*SC_MODULE(Testbench) {
    sc_clock clk;
    sc_signal< sc_biguint<N> > A, B;
    sc_signal< sc_biguint<N> > O;

    Mul dut;

    void test() {
        A.write(7);
        B.write(5);
        wait(1, SC_NS);
       	if (O.read() != 35) {
            cout << "Error: Output value is " << O.read() << endl;
        }
	 else 
	 cout << ": correct:Output value is " << O.read() << endl;

    }

    SC_CTOR(Testbench)
        : clk("clk", 10, SC_NS)
        , dut("dut")
    {
        dut.A(A);
        dut.B(B);
        dut.O(O);

        SC_THREAD(test);
    }
};

int sc_main(int argc, char* argv[]) {
    Testbench tb("testbench");
    sc_start(10,SC_NS);
    return 0;
}*/

//------------------tb for sub----------------------------
/*SC_MODULE(Testbench) {
    sc_clock clk;
    sc_signal< sc_biguint<N> > A, B;
    sc_signal< sc_biguint<N> > O;

    Sub dut;

    void test() {
        A.write(7);
        B.write(5);
        wait(1, SC_NS);
       	if (O.read() != 2) {
            cout << "Error: Output value is " << O.read() << endl;
        }
	 else 
	 cout << ": correct:Output value is " << O.read() << endl;

    }

    SC_CTOR(Testbench)
        : clk("clk", 10, SC_NS)
        , dut("dut")
    {
        dut.A(A);
        dut.B(B);
        dut.O(O);

        SC_THREAD(test);
    }
};

int sc_main(int argc, char* argv[]) {
    Testbench tb("testbench");
    sc_start(10,SC_NS);
    return 0;
}
*/


//--------------tb for add----------------------------
/*SC_MODULE(Testbench) {
    sc_clock clk;
    sc_signal< sc_biguint<N> > A, B;
    sc_signal< sc_biguint<N> > O;

    Add dut;

    void test() {
        A.write(5);
        B.write(7);
        wait(1, SC_NS);
       	if (O.read() != 12) {
            cout << "Error: Output value is " << O.read() << endl;
        }
	 else 
	 cout << ": correct:Output value is " << O.read() << endl;

    }

    SC_CTOR(Testbench)
        : clk("clk", 10, SC_NS)
        , dut("dut")
    {
        dut.A(A);
        dut.B(B);
        dut.O(O);

        SC_THREAD(test);
    }
};

int sc_main(int argc, char* argv[]) {
    Testbench tb("testbench");
    sc_start(10,SC_NS);
    return 0;
}*/

