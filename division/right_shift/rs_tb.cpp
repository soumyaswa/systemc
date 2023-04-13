#include "right_shift.cpp"



SC_MODULE(right_shift_tb){
	sc_signal<sc_biguint<N>> inp;
	sc_signal<sc_biguint<S>> shift_by;
	sc_signal<sc_biguint<N>> out;
	sc_clock clk;

	sc_trace_file *tf;

	right_shift_N shift_r;

	void stimulus();

	SC_CTOR(right_shift_tb):
		shift_r("shift_r"),
		clk("clk",10, SC_NS)
	{
		shift_r.inp(inp);
		shift_r.shift_by(shift_by);
		shift_r.out(out);
		shift_r.clk(clk);

		tf = sc_create_vcd_trace_file("right_shift");
		sc_trace(tf, inp, "input");
		sc_trace(tf, shift_by, "shift_by");
		sc_trace(tf, out, "output");
		sc_trace(tf, clk, "clk");
		
		SC_THREAD(stimulus);
	}

	~right_shift_tb(){
		sc_close_vcd_trace_file(tf);
	}
};

void right_shift_tb::stimulus(){
	srand(time(NULL));
	while(true){
		//for 16 bits
	/*	inp.write(rand() % (1 << N));
		shift_by.write(rand() % (1 << S));*/

		//for 32 bits
		inp.write(rand());
		shift_by.write(rand());

		cout << "input = " << inp.read() << " shift_r_by = " << shift_by.read() << " output = " << out.read() << endl;
		wait(10, SC_NS);
	}
}


int sc_main(int argc, char* argv[]){
	right_shift_tb test("test");
	sc_start(100,SC_NS);
	sc_stop();
	return 0;
}
