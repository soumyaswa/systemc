#include "new_mul.cpp"



SC_MODULE(multiplier_test){
	sc_signal<sc_uint<N>> multiplicand;
	sc_signal<sc_uint<N>> multiplier;
	sc_signal<sc_uint<3*N>> mul_op;
	sc_signal<bool> rst;
	sc_clock clk;

	sc_trace_file *tf;

	multiplier_N* mul;

	void stimulus();

	SC_CTOR(multiplier_test):
		clk("mul_clk", 10,SC_NS),
		multiplicand("mul_multiplicand"),
		multiplier("mul_multiplier"),
		mul_op("mul_mul_op"),
		rst("mul_rst")
	{
		mul = new multiplier_N("mul");
		mul->clk(clk);
		mul->rst(rst);
		mul->multiplicand(multiplicand);
		mul->multiplier(multiplier);
		mul->mul_op(mul_op);
		

		tf = sc_create_vcd_trace_file("multiplier_wave");
		sc_trace(tf, multiplicand, "multiplicand");
		sc_trace(tf, multiplier, "multiplier");
		sc_trace(tf, mul_op, "mul_opput");
		sc_trace(tf, clk, "clk");
		sc_trace(tf, rst, "rst");
		
		SC_THREAD(stimulus);
	}

	~multiplier_test(){
		sc_close_vcd_trace_file(tf);
	}
};

void multiplier_test::stimulus(){
	srand(time(NULL));
	while(true){
		rst.write(rand() % 2);
		multiplicand.write(rand());
		multiplier.write(rand());
		
		cout << " " << endl;
		cout << "********************************  test run " << " ***********************************" << endl;
		cout << " " << endl;

		cout << "rst = " << rst.read() << " multiplicand = " << multiplicand.read() << " multiplier = "<< multiplier.read() << " mul_op_dut = "<< mul_op.read() << endl;
		wait(10,SC_NS);
	}
}


int sc_main(int argc, char* argv[]){
	multiplier_test test("test");
	sc_start(100,SC_NS);
	sc_stop();
	return 0;
}
