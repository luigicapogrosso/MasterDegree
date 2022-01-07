/**
 * @file tl.hh
 * @author Luigi Capogrosso
 * @date 11 Dec 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#ifndef TB_HH
#define TB_HH

#include <systemc.h>

//==============================================================================
SC_MODULE(tb)
{
    // Inputs.
    sc_in< sc_lv<32> >  out_res;
    sc_in< sc_lv<2> >   out_rdy;
    // Outputs.
    sc_out< sc_logic >  clk;
    sc_out< sc_logic >  rst;
    sc_out< sc_lv<32> > in_op1;
    sc_out< sc_lv<32> > in_op2;
    sc_out< sc_logic >  vhd_in_rdy;
    sc_out< sc_logic >  v_in_rdy;

    // Update clock.
    void clk_gen();
    // Running stimuli.
    void run();

    SC_CTOR(tb)
    {
        SC_THREAD(clk_gen);
        
        SC_THREAD(run);
            sensitive << clk.pos();
    };
};
//==============================================================================
#endif
