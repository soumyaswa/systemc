#include <systemc.h>
//#include "const.h"

SC_MODULE(GE) {
    sc_in< sc_biguint<N> > A;
    sc_in< sc_biguint<N> > B;
    sc_out< sc_biguint<1>> G;
    sc_out<sc_biguint<1> > E;

    void compare() {
        G.write(A.read() > B.read());
        E.write(A.read() == B.read());
    }

    SC_CTOR(GE) {
        SC_METHOD(compare);
        sensitive << A << B;
    }
};  
/*module GE#(parameter N=16)(
  //A>B
  input [N-1:0] A,
  input [N-1:0] B,
  output G,
  output E
);
  
  assign E = (A==B);
  assign G = A > B;
  
endmodule*/
