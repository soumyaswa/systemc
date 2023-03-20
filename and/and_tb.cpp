#include "and2.cpp"
#include "const.h"
//#include <cstdlib>


SC_MODULE(and2_test){
	sc_signal<bool> x,y,z;
        sc_signal<bool> clr;   /// here sc_signal is a wire 
	sc_clock clk;   ///   no need to give bool as sc_clock will take care, note: we cannot do clk.write since sc_clock will take care.
	//("clk", 5, SC_NS);


	and2 and2_op;
	
	sc_trace_file *pTracefile;

	void stimulus();

	SC_CTOR(and2_test):
		clk("clk", tp),
		and2_op("and2_op")
	{
		and2_op.a(x);  /// connection 
	        and2_op.b(y);
	        and2_op.f(z);
	        and2_op.clk(clk);
		and2_op.clr(clr);

		pTracefile = sc_create_vcd_trace_file("and_vcd_waves");

	        sc_trace(pTracefile, x, "inp_1");
	        sc_trace(pTracefile, y, "inp_2");
	        sc_trace(pTracefile, z, "and_output");
                sc_trace(pTracefile, clk, "trace_clk");
		sc_trace(pTracefile, clr, "trace_clr");

		SC_THREAD(stimulus)    //sc_thread is like initial begin, and sc_cthread is like forever 
	}

	~and2_test(){
		sc_close_vcd_trace_file(pTracefile);
	}       ////  here ~ is known as destructor operator of module which is a member function of and2_test module that is automatically called by systemc framework. It performs any necessary cleanups like closing file, freeing memory, or releasing resources.
};


void and2_test::stimulus(){


	/*clr.write(true);
	wait(3*tp);
	clr.write(false);*/
 
	//int i;

	srand(time(NULL));   ///  generate a seed with random value: here we gave time in seconds as seed
	//for(i=0; i<20; i++)
	while(true)
	{
		//x.write(sc_random::bit());   //// sc_random::bit(), ::randbit(), ::randInt(), ::randInt(from_range, to_range),   might not work depending on the systemc version
		//y.write(sc_random::bit());
		clr.write(rand() % 2);      ///////  alternative for above code in older version of systemc
		x.write(rand() % 2);
		y.write(rand() % 2);
		cout << "clk = " << clk.read() << " clr = " << clr.read() << " a = " << x.read() << " b = " << y.read() << " c = " << z.read() << endl;
	        wait(tp);  //  wait for tp time and than value will channge after tp time(where tp is time period whihc is defined as constant in const.h file)
	}

	//clr.write(true);

	/*  clr.write(true);
	 for(i = 0; i<=4; i++){
		clk.write(true);
		wait(5, SC_NS);
		clk.write(false);
		wait(5, SC_NS);
	}



	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	clr.write(false);
	//----------------------------------------
	clk.write(true);
	x.write(true);
	y.write(false);
	clr.write(true);

	clk.write(false);
	cout << "clk = " << clk.read() << " clr = " << clr.read() << " a = " << x.read() << " b = " << y.read() << " c = " << z.read() << endl;
	wait(5, SC_NS);
	//----------------------------------------
        clk.write(true);
	x.write(true);
	y.write(true);
	cout << "clk = " << clk.read() << " clr = " << clr.read() << " a = " << x.read() << " b = " << y.read() << " c = " << z.read() << endl;
	wait(5, SC_NS);

	clk.write(false);
	cout << "clk = " << clk.read() << " clr = " << clr.read() << " a = " << x.read() << " b = " << y.read() << " c = " << z.read() << endl;
	wait(5, SC_NS);
        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	
	clr.write(true);

	for(i = 0; i<=4; i++){
		clk.write(true);
		wait(5, SC_NS);
		clk.write(false);
		wait(5, SC_NS);
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	clr.write(false);
	//----------------------------------------
	clk.write(true);
	x.write(false);
	y.write(false);
	cout << "clk = " << clk.read() << " clr = " << clr.read() << " a = " << x.read() << " b = " << y.read() << " c = " << z.read() << endl;
	wait(5, SC_NS);

	clk.write(false);
	cout << "clk = " << clk.read() << " clr = " << clr.read() << " a = " << x.read() << " b = " << y.read() << " c = " << z.read() << endl;
	wait(5, SC_NS);
	//----------------------------------------
        clk.write(true);
	x.write(false);
	y.write(true);
	cout << "clk = " << clk.read() << " clr = " << clr.read() << " a = " << x.read() << " b = " << y.read() << " c = " << z.read() << endl;
	wait(5, SC_NS);

	clk.write(false);
	cout << "clk = " << clk.read() << " clr = " << clr.read() << " a = " << x.read() << " b = " << y.read() << " c = " << z.read() << endl;
	wait(5, SC_NS);
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//
	for(i = 0; i<=4; i++){
		clk.write(true);
		wait(5, SC_NS);
		clk.write(false);
		wait(5, SC_NS);
	}*/

}

int sc_main(int argc, char* argv[]){
	and2_test test("and2_test");  /// and2_test is the module name and "and2_test" is the instance name given to that module (can be any string, mandatory)
	sc_start(30*tp);    //// start of simulation : will run for 30*tp (where tp is time period whihc is defined as constant in const.h file)
	//sc_clock clk("clk", tp);
	sc_stop();           //   $finish
	return 0;
}
