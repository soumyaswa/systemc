#include "fir.cpp"

SC_MODULE(fir_test){

	sc_signal<sc_uint<data_size>> inp, outp;
	sc_signal<bool> rst;
	sc_clock clk;

	sc_trace_file *pTracefile;

	fir_filter fir;

	void stimulus();

	SC_CTOR(fir_test):
		clk("clk", tp),
		fir("fir")
	{
		fir.inp(inp);
		fir.outp(outp);
		fir.rst(rst);
		fir.clk(clk);

		pTracefile = sc_create_vcd_trace_file("fir_vcd_waves");

		sc_trace(pTracefile, rst, "Reset");
		sc_trace(pTracefile, clk, "clk");
		sc_trace(pTracefile, inp, "inp");
                sc_trace(pTracefile, outp, "outp");

		SC_THREAD(stimulus)

	}

	~fir_test(){
		sc_close_vcd_trace_file(pTracefile);
	}
};


void fir_test::stimulus(){

	wait(tp/2);
	srand(time(NULL));
	while (true){
		rst.write(rand() % 2);
		inp.write(rand() % (1 << data_size));
		cout << "Input is " << inp.read() << ", FIR filter output is " << outp.read() << endl;
		wait(tp);
	}
}


int sc_main(int argc, char* argv[]){
       fir_test test("test");
       sc_start(15*tp);
       sc_stop();
       return 0;
}       
