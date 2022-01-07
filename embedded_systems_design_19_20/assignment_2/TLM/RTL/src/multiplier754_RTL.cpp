/**
 * @file multiplier754.ccp
 * @author Luigi Capogrosso
 * @date 11 Dec 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#include "multiplier754_RTL.hh"

//==============================================================================
void multiplier754_RTL :: fsm()
{
    if (rst.read() == SC_LOGIC_1)
    {
        next_state = S_0;
    }
    else if (clk.read() == SC_LOGIC_1)
    {
        switch (state)
        {
            case S_0:
            {
                // S_0 to S_1.
                next_state.write(S_1);

                break;
            }
            case S_1:
            {
                // S_1 to S_2.
                if (in_rdy.read() == SC_LOGIC_1)
                    next_state.write(S_2);
                // S_1 to S_1.
                else
                    next_state.write(S_1);

                break;
            }
            case S_2:
            {
                // S_2 to S_NAN (e1 & e2 are NaN).
                if ((in_op1.read().range(30, 23) == 0xFF &&
                    m1.read() != 0) ||
                    (in_op2.read().range(30, 23) == 0xFF &&
                    m2.read() != 0))
                {
                    next_state.write(S_NAN);
                }
                // S_2 to S_NAN (e1 is inf. & e2 is 0 or vice-versa).
                else if ((in_op1.read().range(30, 23) == 0xFF &&
                        m1.read() == 0 &&
                        in_op2.read().range(30, 23) == 0 &&
                        m2.read() == 0) ||
                        (in_op1.read().range(30, 23) == 0 &&
                        m1.read() == 0 &&
                        in_op2.read().range(30, 23) == 0xFF &&
                        m2.read() == 0))
                {
                    next_state.write(S_NAN);
                }
                // S_2 to S_INF (e1 & e2 are inf).
                else if ((in_op1.read().range(30, 23) == 0xFF &&
                        m1.read() == 0) ||
                        (in_op2.read().range(30, 23) == 0xFF &&
                        m2.read() == 0))
                {
                    next_state.write(S_INF);
                }
                // S_2 to S_ZERO (e1 & e2 are 0).
                else if ((in_op1.read().range(30, 23) == 0 &&
                        m1.read() == 0) ||
                        (in_op2.read().range(30, 23) == 0 &&
                        m2.read() == 0))
                {
                    next_state.write(S_ZERO);
                }
                // S_2 to S_3 (e1 & e2 are normalized or denormalized).
                else
                {
                    next_state.write(S_3);
                }

                break;
            }
            case S_3:
            {
        		// S_3 to S_6 (e1 is denormalized).
        		if (in_op1.read().range(30, 23) == 0 &&
        			in_op2.read().range(30, 23) == 0)
        		{
        		    next_state.write(S_6);
        		}
                // S_3 to S_4 (e2 is denormalized).
                else if (in_op1.read().range(30, 23) == 0)
                {
                    next_state.write(S_4);
                }
                // S_3 to S_5 (e1 & e2 are denormalized).
                else if (in_op2.read().range(30, 23) == 0)
                {
                    next_state.write(S_5);
                }
                // S_3 to S_7 (e1 & e2 are normalized).
                else
                {
                    next_state.write(S_7);
                }

                break;
            }
            case S_4:
            {
                // S_4 to S_7.
                next_state.write(S_7);

                break;
            }
            case S_5:
            {
                // S_5 to S_7.
                next_state.write(S_7);

                break;
            }
            case S_6:
            {
                // S_6 to S_7.
                next_state.write(S_7);

                break;
            }
            case S_7:
            {
                // S_7 to S_8 (shift-right once).
                if (tmp_m.read().range(47, 46) == "10" ||
                    tmp_m.read().range(47, 46) == "11")
                {
                    next_state.write(S_8);
                }
                // S_7 to S_9 (do shift-left).
                else if (tmp_m.read().range(47, 46) == "00")
                {
                    next_state.write(S_9);
                }
                // S_7 to S_NORM (no right/left-shift is necessary).
                else
                {
                    next_state.write(S_NORM);
                }

                break;
            }
            case S_8:
            {
                // S_8 to S_NORM.
                next_state.write(S_NORM);

                break;
            }
            case S_9:
            {
                // S_9 to S_10 (overflow).
                if (tmp_e.read()[8] == 1)
                {
                    next_state.write(S_10);
                }
                // S_9 to S_11 (not in overflow, but risk underflow).
                else
                {
                    next_state.write(S_11);
                }

                break;
            }
            case S_10:
            {
                // S_10 to S_10 (still shif).
                if (tmp_m.read().range(47, 46) == "00")
                {
                    next_state.write(S_10);
                }
                // S_10 to S_NORM (end shift).
                else
                {
                    next_state.write(S_NORM);
                }

                break;
            }
            case S_11:
            {
                // S_11 to S_11 (still shif).
                if (tmp_e.read().range(8, 0) == 0)
                {
                    next_state.write(S_DENORM);
                }
                // S_11 to S_DENORM (underflow).
                else if (tmp_m.read().range(47,46) == "00")
                {
                    next_state.write(S_11);
                }
                // S_11 to S_NORM (end shift).
                else
                {
                    next_state.write(S_NORM);
                }

                break;
            }
            case S_12:
            {
                // S_12 to S_13.
                next_state.write(S_13);

                break;
            }
            case S_13:
            {
                // S_13 to S_ROUND.
                if (tmp_m.read()[22] == 1)
                {
                    next_state.write(S_ROUND);
                }
                // S_13 to S_14.
                else
                {
                    next_state.write(S_14);
                }

                break;
            }
            case S_14:
            {
                // S_14 to S_END.
                next_state.write(S_END);

                break;
            }
            case S_15:
            {
                // S_15 to S_NORM.
                next_state.write(S_NORM);

                break;
            }
            case S_NAN:
            {
                // S_NAN to S_END.
                next_state.write(S_END);

                break;
            }
            case S_INF:
            {
                // S_INF to S_END.
                next_state.write(S_END);

                break;
            }
            case S_ZERO:
            {
                // S_ZERO to S_END.
                next_state.write(S_END);

                break;
            }
            case S_ROUND:
            {
                if (tmp_m.read().range(47, 46) == "01")
                {
                    next_state.write(S_14);
                }
                else if (tmp_m.read().range(47, 46) == "10")
                {
                    next_state.write(S_15);
                }

                break;
            }
            case S_NORM:
            {
                // S_NORM to S_12 (not in overflow).
                if (tmp_e.read()[8] == 0)
                {
                    next_state.write(S_12);
                }
                // S_NORM to S_INF (overflow).
                else
                {
                    next_state.write(S_INF);
                }

                break;
            }
            case S_DENORM:
            {
                // S_DENORM to S_13.
                next_state.write(S_13);

                break;
            }
            case S_END:
            {
                // S_END to S_0.
                next_state.write(S_0);

                break;
            }
            default:
            {
                next_state.write(S_0);

                break;
            }
        }
    }
}
//==============================================================================
// Datapath.
void multiplier754_RTL :: datapath()
{
    state.write(next_state.read());
    switch (next_state)
    {
        case S_0:
        {
            e       = 0;
            m       = 0;
            s       = 0;

            m1      = 0;
            m2      = 0;
            tmp_m   = 0;
            tmp_e   = 0;

            out_rdy.write(sc_dt::SC_LOGIC_0);
            out_res.write(0);

            break;
        }
        case S_1:
        {
            // NTD.
            break;
        }
        case S_2:
        {
            sc_uint<1> bit_zero = 0;
            m1 = (bit_zero, in_op1.read().range(22, 0));
            m2 = (bit_zero, in_op2.read().range(22, 0));

            break;
        }
        case S_3:
        {
            sc_uint<1> bit_one = 1;
            m1 = (bit_one, m1.read().range(22, 0));
            m2 = (bit_one, m2.read().range(22, 0));

            break;
        }
        case S_4:
        {
            sc_uint<1> bit_zero = 0;
            m1 = (bit_zero, m1.read().range(22, 0));

            break;
        }
        case S_5:
        {
            sc_uint<1> bit_zero = 0;
            m2 = (bit_zero, m1.read().range(22, 0));

            break;
        }
        case S_6:
        {
            sc_uint<1> bit_zero = 0;
            m1 = (bit_zero, m1.read().range(22, 0));
            m2 = (bit_zero, m2.read().range(22, 0));

            break;
        }
        case S_7:
        {
            tmp_e = in_op1.read().range(30, 23).to_uint() +
                    in_op2.read().range(30, 23).to_uint() - 127;
            tmp_m = m1.read().to_uint64() * m2.read().to_uint64();

            break;
        }
        case S_8:
        {
            tmp_m = tmp_m.read() >> 1;
            tmp_e = tmp_e.read().to_uint() + 1;

            break;
        }
        case S_9:
        {
            // NTD.
            break;
        }
        case S_10:
        {
            tmp_m = tmp_m.read() << 1;
            tmp_e = tmp_e.read().to_uint() - 1;

            break;
        }
        case S_11:
        {
            tmp_m = tmp_m.read() << 1;
            tmp_e = tmp_e.read().to_uint() - 1;

            break;
        }
        case S_12:
        {
            e = tmp_e.read().range(7, 0);

            break;
        }
        case S_13:
        {
            // NTD.
            break;
        }
        case S_14:
        {
            m = tmp_m.read().range(45, 23);
            s = (bool) in_op1.read().get_bit(31) ^
                (bool) in_op2.read().get_bit(31);

            break;
        }
        case S_15:
        {
            tmp_e = tmp_e.read().to_uint() + 1;

            break;
        }
        case S_NAN:
        {
            sc_lv<MANTISSA_SIZE> m_nan = 0;
            m_nan[22] = 1;
            e = 0xFF;
            m = m_nan;

            break;
        }
        case S_INF:
        {
            e = 0xFF;
            m = 0;
            s = (bool) in_op1.read().get_bit(31) ^
                (bool) in_op2.read().get_bit(31);

            break;
        }
        case S_ZERO:
        {
            e = 0x00;
            m = 0;
            s = (bool) in_op1.read().get_bit(31) ^
                (bool) in_op2.read().get_bit(31);

            break;
        }
        case S_ROUND:
        {
            sc_lv<22> all_zero = 0;
            tmp_m = (tmp_m.read().range(47, 22).to_uint() + 1, all_zero);

            break;
        }
        case S_NORM:
        {
            // NTD.
            break;
        }
        case S_DENORM:
        {
            e = 0;

            break;
        }
        case S_END:
        {
            out_rdy.write(SC_LOGIC_1);
            out_res.write((s.read(), e.read(), m.read()));

            break;
        }
        default:
        {
            // NTD.
            break;
        }
    }
}
//==============================================================================
