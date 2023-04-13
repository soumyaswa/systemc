#include "systemc.h"
#include "const.h"
SC_MODULE(Rshift) {
    sc_in< sc_uint<N> > i;
    sc_in<sc_uint<S>> shift_by;
    sc_out< sc_uint<N> > o;
    sc_signal<sc_uint<N> > temp_o;

    SC_CTOR(Rshift) {
        SC_METHOD(shift);
        sensitive << i << shift_by;
    }

    void shift() {
	    sc_uint<S> shift = shift_by.read();            // using this shift so that i can pick the range of value from N-1 to shift_by range from the input .
      //	 o.write((00, i.read().range(N-1, 2)));   //here i am doing :  seting the MSB bit as "0" after that i have the data from "N-1 TO 1" because the MSB BIT IS 0 and the 0th bit will get overflow and got outside                                                              from the range ,here we can also remove 00 from the starting that time also its working fine
	
	o.write((/*00,*/ i.read().range(N-1, shift)));     ///whit out giving hardcoded values i am using the shift_by varible for randome geeration of shift option

	  
	
	
	
	//o[N-1].write(0);                  error::message::::right_shift.cpp:15:18: error: request for member ‘write’ in ‘((Rshift*)this)->Rshift::o.sc_core::sc_out<sc_dt::sc_uint<16> >::<anonymous>.sc_core::sc_inout<sc_d                                                                 t::sc_uint<16> >::<anonymous>.sc_core::sc_port<sc_core::sc_signal_inout_if<sc_dt::sc_uint<16> >, 1, sc_core::SC_ONE_OR_MORE_BOUND>::<anonymous>.sc_core::sc_por                                                                 t_b<sc_core::sc_signal_inout_if<sc_dt::sc_uint<16> > >::operator[]((((int)N) - 1))’, which is of pointer type ‘sc_core::sc_signal_inout_if<sc_dt::sc_uint<16> >                                                                 *’ (maybe you meant to use ‘->’ ?)
                                                                      //15 |           o[N-1].write(0);
	//o[N-1]->write(0);
	//o.write((i.read().range(N-2, 0), 0));
	//temp_o[N-1] = 0b0;
	//temp_o.range(N-2, 1) = i.read(().range(N-1, 0));

	//o.write(temp_o);
	

    }
};



//------------in verilog design------------------------------
/*module Rshift#(parameter N=16)(
  input [N-1:0] i,
  output [N-1:0] o
);
  
  assign o[N-1] = 1'b0;
  assign o[N-2:0] = i[N-1:1];
  
endmodule*/
