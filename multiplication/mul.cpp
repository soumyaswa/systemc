#include <systemc.h>
#include "const.h"

//--------full adder---------------

SC_MODULE(full_adder) {
    sc_in<sc_bv<N>> A;
    sc_in<sc_bv<N>> B;
    sc_in<sc_bv<N>> Cin;
    sc_out<sc_bv<N>> Sum;
    sc_out<sc_bv<N>> Cout;

    void adder_func() {
        sc_bv<N> temp_sum = A.read() ^ B.read() ^ Cin.read();
        sc_bv<N> temp_carry = (A.read() & B.read()) | (Cin.read() & (A.read() ^ B.read()));
        Sum.write(temp_sum);
        Cout.write(temp_carry);
    }

    SC_CTOR(full_adder) {
        SC_METHOD(adder_func);
        sensitive << A << B << Cin;
    }
};


//-----------left shift ------------------------

SC_MODULE(Lshift) {
    sc_in<sc_bv<N>> i;
    sc_out<sc_bv<N>> o;

    void lshift_func() {
        o.write((sc_bv<N>(0), i.read().range(N-2, 0)));
    }

    SC_CTOR(Lshift) {
        SC_METHOD(lshift_func);
        sensitive << i;
    }
};


//-----------

SC_MODULE(zExtend) {
    sc_in<sc_bv<N>> i;
    sc_out<sc_bv<N*2>> o;

    void zExtend_func() {
        o.write((sc_bv<N>(0), i.read()));
    }

    SC_CTOR(zExtend) {
        SC_METHOD(zExtend_func);
        sensitive << i;
    }
};


//-------------multiplication-------------------

SC_MODULE(multiplier) {
    sc_in<sc_bv<N>> A;
    sc_in<sc_bv<N>> B;
    sc_out<sc_bv<N*2>> O;

    Lshift* left_shift_module[N];
    full_adder* adder_module[N];

    sc_signal<sc_bv<N>> shift_output;


    multiplier(sc_module_name name) : sc_module(name) {
       // left_shift_module = new Lshift<N>*[N];
        //adder_module = new full_adder<N>*[N];

        for (int i = 0; i < N; i++) {
            left_shift_module[i] = new Lshift(("left_shift_" + std::to_string(i)).c_str());
            adder_module[i] = new full_adder(("adder_" + std::to_string(i)).c_str());
        }

        for (int i = 1; i < N; i++) {
            left_shift_module[i]->i(A);
           // left_shift_module[i]->o(adder_module[i]->A);
	    left_shift_module[i]->o(shift_output);
	   adder_module[i]->A(shift_output);

            sc_bv<N> temp1,temp2;
	    sc_bv<N> b0=B.read();
           // temp = B.read()[i] ? left_shift_module[i]->o.read() : sc_bv<N*2>(0);
	   //
	   if (b0[i] != 0b0) {
		   temp2 = temp1;
	   }
	   else {
		   temp2 = 0b0;
	   }
	   sc_signal<sc_bv<N>> temp;
	    temp = temp2;
            adder_module[i]->B(temp);
             adder_module[i-1]->Sum(adder_module[i]->Cout);
        }

       O.write(adder_module[N-1]->Sum);
    }
};
