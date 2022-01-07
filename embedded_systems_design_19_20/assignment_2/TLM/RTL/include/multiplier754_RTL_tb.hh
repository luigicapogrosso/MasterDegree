/**
 * @file multiplier754_UT_tb.hh
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#ifndef __MULTIPLIER754_RTL_TB_HH
#define __MULTIPLIER754_RTL_TB_HH

#include <systemc.h>

#define PERIOD 10

//==============================================================================
class multiplier754_RTL_tb : public sc_module
{
public:
    sc_in< sc_logic > p_in_enable;
    sc_in< sc_lv<32> > p_in_data;
    sc_out< sc_logic > p_out_enable;
    sc_out< sc_lv<32> > p_out_data_op1;
    sc_out< sc_lv<32> > p_out_data_op2;
    sc_out< sc_logic > reset_to_RTL;
    sc_out< sc_logic > clk;

    SC_HAS_PROCESS(multiplier754_RTL_tb);
    multiplier754_RTL_tb(sc_module_name name);

private:
    void run();
    void clk_gen();
};
//==============================================================================
#endif
