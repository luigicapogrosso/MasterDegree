
#include "multiplier754_RTL.hh"
#include "multiplier754_RTL_tb.hh"


int sc_main(int argc, char **argv) {
    sc_signal< sc_logic > clock;

    sc_signal< sc_logic > reset_signal;
    sc_signal< sc_lv<32> > p_in_data_op1;
    sc_signal< sc_lv<32> > p_in_data_op2;
    sc_signal< sc_logic > p_in_enable;
    sc_signal< sc_logic > p_out_enable;
    sc_signal< sc_lv<32> > p_out_data;

    multiplier754_RTL_tb i_src_RTL("src_RTL"); // source module
    multiplier754_RTL i_multiplier_RTL("multiplier_RTL");         // multiplier RTL module

    i_multiplier_RTL.clk(clock);
    i_multiplier_RTL.rst(reset_signal);
    i_multiplier_RTL.in_rdy(p_in_enable);
    i_multiplier_RTL.in_op1(p_in_data_op1);
    i_multiplier_RTL.in_op2(p_in_data_op2);
    i_multiplier_RTL.out_res(p_out_data);
    i_multiplier_RTL.out_rdy(p_out_enable);

    i_src_RTL.clk(clock);
    i_src_RTL.p_in_enable(p_out_enable);
    i_src_RTL.p_in_data(p_out_data);
    i_src_RTL.p_out_enable(p_in_enable);
    i_src_RTL.p_out_data_op1(p_in_data_op1);
    i_src_RTL.p_out_data_op2(p_in_data_op2);
    i_src_RTL.reset_to_RTL(reset_signal);

    sc_start();

    return 0;
};
