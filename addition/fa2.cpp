#include <systemc.h>

// Half Adder module
SC_MODULE(HalfAdder) {
    sc_in<bool> a, b;
    sc_out<bool> sum, carry;

    void half_adder_process() {
        sum = a ^ b;        // XOR gate for sum
        carry = a & b;     // AND gate for carry
    }

    SC_CTOR(HalfAdder) {
        SC_METHOD(half_adder_process);
        sensitive << a << b;
    }
};

// Full Adder module
SC_MODULE(FullAdder) {
    sc_in<bool> a, b, c_in;
    sc_out<bool> sum, c_out;

    HalfAdder ha1, ha2;

    void full_adder_process() {
        ha1.a(a);
        ha1.b(b);
        ha1.sum(sum);
        ha1.carry(c_out);

        ha2.a(sum);
        ha2.b(c_in);
        ha2.sum(sum);
        ha2.carry(c_out);
    }

    SC_CTOR(FullAdder) : ha1("ha1"), ha2("ha2") {
        SC_METHOD(full_adder_process);
        sensitive << a << b << c_in;
    }
};

//N-bit Adder module
SC_MODULE(NBitAdder) {
    sc_in<bool> clk, reset;
    sc_in<sc_lv<8>> a, b;
    sc_out<sc_lv<8>> sum;

    FullAdder* fas[8];

    void n_bit_adder_process() {
        if (reset.read()) {
            for (int i = 0; i < 8; i++) {
                fas[i]->a(false);
                fas[i]->b(false);
                fas[i]->c_in(false);
            }
        } else {
            for (int i = 0; i < 8; i++) {
                fas[i]->a(a.read()[i]);
                fas[i]->b(b.read()[i]);
                fas[i]->c_in(i == 0 ? false : fas[i-1]->c_out.read());
            }
        }

        sc_lv<8> sum_temp;
        for (int i = 0; i < 8; i++) {
            sum_temp[i] = fas[i]->sum.read();
        }
        sum.write(sum_temp);
    }

    SC_HAS_PROCESS(NBitAdder);
    NBitAdder(sc_module_name name) : sc_module(name) {
        for (int i = 0; i < 8; i++) {
            fas[i] = new FullAdder("fa" + std::to_string(i));
        }

        SC_METHOD(n_bit_adder_process);
        sensitive << clk.pos() << reset;
    }

    ~NBitAdder() {
        for (int i = 0; i < 8; i++) {
            delete fas[i];
        }
    }
};

