/**
 * @file multiplier754.ccp
 * @author Luigi Capogrosso
 * @date 11 Dec 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#ifndef MULTIPLIER754_RTL_HH
#define MULTIPLIER754_RTL_HH

#include <systemc.h>

//==============================================================================
#define SIZE 32
#define EXPONENT_SIZE 8
#define MANTISSA_SIZE 23
//==============================================================================
SC_MODULE(multiplier754_RTL)
{
    // FSM states definition.
    typedef enum
    {
        S_0,
        S_1,
        S_2,
        S_3,
        S_4,
        S_5,
        S_6,
        S_7,
        S_8,
        S_9,
        S_10,
        S_11,
        S_12,
        S_13,
        S_14,
        S_15,
        S_NAN,
        S_INF,
        S_ZERO,
        S_ROUND,
        S_NORM,
        S_DENORM,
        S_END
    } STATE_T;
    // Inputs.
    sc_in< sc_logic >       clk;
    sc_in< sc_logic >       rst;
    sc_in< sc_lv<SIZE> >    in_op1;
    sc_in< sc_lv<SIZE> >    in_op2;
    sc_in< sc_logic >       in_rdy;
    // Outputs.
    sc_out< sc_lv<SIZE> >   out_res;
    sc_out< sc_logic >      out_rdy;
    // To describe the finite set of states.
    sc_signal< STATE_T > state;
    sc_signal< STATE_T > next_state;
    // Floatig point 754 single precison rapresentation.
    sc_signal< sc_lv<EXPONENT_SIZE> >   e;
    sc_signal< sc_lv<MANTISSA_SIZE> >   m;
    sc_signal< sc_lv<1> >               s;
    // Temporary signals for calculation
    sc_signal< sc_lv<MANTISSA_SIZE + 1> >       m1;
    sc_signal< sc_lv<MANTISSA_SIZE + 1> >       m2;
    sc_signal< sc_lv<(MANTISSA_SIZE + 1) * 2> > tmp_m;
    sc_signal< sc_lv<EXPONENT_SIZE + 1> >       tmp_e;

    // FSM.
    void fsm();
    // Datapath.
    void datapath();

    SC_CTOR(multiplier754_RTL)
    {
        SC_METHOD(fsm);
        sensitive_pos << clk;
        sensitive << rst;

        SC_METHOD(datapath);
        sensitive << next_state;
    };
};
//==============================================================================
#endif
