/**
 * @file multiplier754.ccp
 * @author Luigi Capogrosso
 * @date 11 Dec 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#include <systemc.h>

#define SIZE 32

//==============================================================================
SC_MODULE(multiplierIEEE754_sc)
{
    // Convert uint in float bit to bit.
    typedef union
    {
        unsigned int uint;
        float        fp;
    } ieee754;

    // Inputs.
    sc_in_clk              clk;
	sc_in< sc_logic >      rst;
	sc_in< sc_lv<SIZE> >   in_op1;
	sc_in< sc_lv<SIZE> >   in_op2;
	sc_in< sc_logic >      in_rdy;

	// Outputs.
	sc_out< sc_lv<SIZE> >  out_res;
	sc_out< sc_logic >     res_rdy;

    // Do the multiplication between in_op1 and in_op2.
    void makeMul()
    {
        if (rst.read() == SC_LOGIC_1)
        {
            out_res.write(0);
            res_rdy.write(SC_LOGIC_0);
        }
        else if (clk.read() == 1)
        {
            if (in_rdy.read() == SC_LOGIC_1)
            {
                ieee754 tmp_in_op1, tmp_in_op2, mul;

                tmp_in_op1.uint = in_op1.read().to_uint();
                tmp_in_op2.uint = in_op2.read().to_uint();
                mul.fp = tmp_in_op1.fp * tmp_in_op2.fp;

                out_res.write(mul.uint);
                res_rdy.write(SC_LOGIC_1);
            }
            else
            {
                res_rdy.write(SC_LOGIC_0);
            }
        }
    }

    SC_CTOR(multiplierIEEE754_sc)
        : in_op1("in_op1_sc")
        , in_op2("in_op2_sc")
        , in_rdy("in_rdy_sc")
        , clk("clk_sc")
        , rst("rst_sc")
        , out_res("res_sc")
        , res_rdy("res_sc")
    {
        SC_METHOD(makeMul);
        sensitive_pos << clk;
        sensitive << rst;
    }
};
//==============================================================================
