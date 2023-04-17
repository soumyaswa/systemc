#include <systemc.h>
//#include "const.h"

SC_MODULE(Mul) {
    sc_in< sc_biguint<N> > A;
    sc_in< sc_biguint<N> > B;
    sc_out< sc_biguint<N> > O;

    void mul() {
        O.write(A.read() * B.read());
    }

    SC_CTOR(Mul) {
        SC_METHOD(mul);
        sensitive << A << B;
    }
};





/*module Mul#(parameter N=16)(
  input [N-1:0] A,
  input [N-1:0] B,
  output reg [N-1:0] O
);
  
  assign O = A*B;
  
endmodule*/

