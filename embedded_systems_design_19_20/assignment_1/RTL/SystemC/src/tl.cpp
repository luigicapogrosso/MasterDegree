/**
 * @file tl.cc
 * @author Luigi Capogrosso
 * @date 11 Dec 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#include "tl.hh"

//==============================================================================
void tl :: fsm()
{
    if (rst.read() == sc_dt::SC_LOGIC_1)
    {
        next_state = S_0;

        out_res.write(0);
        out_rdy.write("00");
        tmp.write(0);
    }
    else
    {
        switch (next_state)
        {
            case S_0:
            {
                next_state = S_1;

                break;
            }
            case S_1:
            {
                if (vhd_res_rdy == sc_dt::SC_LOGIC_1 &&
                    v_res_rdy == sc_dt::SC_LOGIC_0)
                {
                    next_state = S_2;

                    out_rdy.write("01");
                    out_res.write(vhd_res);
                }
                if (vhd_res_rdy == sc_dt::SC_LOGIC_0 &&
                    v_res_rdy == sc_dt::SC_LOGIC_1)
                {
                    next_state = S_3;

                    out_rdy.write("10");
                    out_res.write(v_res);
                }
                if (vhd_res_rdy == sc_dt::SC_LOGIC_1 &&
                    v_res_rdy == sc_dt::SC_LOGIC_1)
                {
                    next_state = S_4;

                    out_rdy.write("01");
                    out_res.write(vhd_res);
                    tmp = v_res;
                }
                else
                {
                    next_state = S_1;
                }
                break;
            }
            case S_2:
            {
                next_state = S_1;

                break;
            }
            case S_3:
            {
                next_state = S_1;

                break;
            }
            case S_4:
            {
                next_state = S_5;

                out_rdy.write("10");
                out_res.write(tmp);

                break;
            }
            case S_5:
            {
                next_state = S_0;

                out_res.write(0);
                out_rdy.write("00");
                tmp.write(0);

                break;
            }
            default:
            {
                next_state = S_0;

                out_res.write(0);
                out_rdy.write("00");
                tmp.write(0);

                break;
            }
        }
    }
}
//==============================================================================
