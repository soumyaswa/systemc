#include <systemc.h>
//#include "const.h"

SC_MODULE(Add) {
    sc_in< sc_biguint<N> > A;
    sc_in< sc_biguint<N> > B;
    sc_out< sc_biguint<N> > O;

    void add() {
        O.write(A.read() + B.read());
    }

    SC_CTOR(Add) {
        SC_METHOD(add);
        sensitive << A << B;
    }
};






/*module Add#(parameter N=16)(
  input [N-1:0] A,
  input [N-1:0] B,
  output reg [N-1:0] O
);
  assign O = A+B;
endmodule*/



