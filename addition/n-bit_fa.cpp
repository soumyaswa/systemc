#include "systemc.h"
#include "fa_ha.cpp"


SC_MODULE(FullAdder16) {
    sc_in<sc_bv<1>> a[16];
    sc_in<sc_bv<1>> b[16];
    sc_in<sc_bv<1>> c_in;
    sc_out<sc_bv<1>> sum[16];
    sc_out<sc_bv<1>> c_out;

    FA* fa[16];
    sc_signal<sc_bv<1>> c[16];

    SC_CTOR(FullAdder16) {
        // Instantiate 16 1-bit Full Adder modules
        for (int i = 0; i < 16; i++) {
            fa[i] = new FA(sc_gen_unique_name("fa"));
            fa[i]->a(a[i]);
            fa[i]->b(b[i]);
            //fa[i]->c_in(c[i]);
            fa[i]->sum(sum[i]);
            if (i == 0) {
                fa[i]->c_in(c_in);
            }
            else {
                fa[i]->c_in(c[i-1]);
            }
	    if(i==15){
		    fa[15]->c_out(c_out);
	    }
	    else {
		    fa[i]->c_out(c[i+1]);
	    }


        }

        // Connect carry-out of each bit to carry-in of next bit
        /*for (int i = 0; i < 15; i++) {
            fa[i]->c_out(c[i+1]);
        }
        fa[15]->c_out(c_out);*/

        // Delete dynamically allocated 1-bit Full Adder modules
        // This is not necessary since SC_MODULEs are automatically cleaned up
        // when the simulation ends
        //for (int i = 0; i < 16; i++) {
        //    delete fa[i];
        //}
    }
};

/*// Ripple Adder module
template<int N>
SC_MODULE(RippleAdder) {
	sc_in<sc_bv<N>> a;
	sc_in<sc_bv<N>> b;
	sc_out<sc_bv<N>> sum;

	sc_signal<sc_bv<1>> carry;

	FA* fas[N];

	SC_CTOR(RippleAdder) {

		// Create full adders
		for (int i = 0; i < N; i++) {
			//fas[i] = new FA("fa" + std::to_string(i));
			fas[i] = new FA(("fa" + std::to_string(i)).c_str());   //("fa" + std::to_string(i)).c_str() concatenates the string "fa" with the index i as a string, and converts the result to a const char* using the c_str() function. This const char* can then be passed to the FA constructor that takes a const char* argument.			
			fas[i]->a(a[i]);
			fas[i]->b(b[i]);
			fas[i]->c_in(carry);
			fas[i]->sum(sum[i]);
			if (i != N-1) { // connect the carry signal to the next adder
				fas[i]->c_out(fas[i+1]->c_in);
			}
		}
	}

	~RippleAdder() {
		for (int i = 0; i < N; i++) {
			delete fas[i];
		}
	}
};
*/
