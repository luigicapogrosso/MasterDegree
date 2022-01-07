/**
 * @file tl.cc
 * @author Luigi Capogrosso
 * @date 11 Dec 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#include "tb.hh"

//==============================================================================
void tb::clk_gen()
{
    cout << "Start tb::clk_gen()." << endl;
    while(true)
    {
        clk.write(sc_dt::SC_LOGIC_1);
        wait(10000000 / 2, sc_core::SC_NS);

        clk.write(sc_dt::SC_LOGIC_0);
        wait(10000000 / 2, sc_core::SC_NS);
    }
}
//==============================================================================
void tb :: run()
{
    cout << "Start tb::run().\n";

    wait();
    rst.write(sc_dt::SC_LOGIC_1);
    wait();
    rst.write(sc_dt::SC_LOGIC_0);

    // Init values.
    cout << "resetted\n";
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);
//==============================================================================
    // Test n.1
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.2
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.3
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.4
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.5
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.6
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.7
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.8
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.9
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.10
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.11
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.12
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.13
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.14
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.15
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.16
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.17
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.18
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.19
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.20
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.21
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    // Test n.22
    cout << "writed op1, op2\n";
    in_op1.write("01000000000000000000000000000000");
    in_op2.write("01000000000000000000000000000000");

    wait();

    vhd_in_rdy.write(sc_dt::SC_LOGIC_1);
    v_in_rdy.write(sc_dt::SC_LOGIC_1);
    cout << "vhd_in_rdy, v_in_rdy = 1.\n";

    wait();
    vhd_in_rdy.write(sc_dt::SC_LOGIC_0);
    v_in_rdy.write(sc_dt::SC_LOGIC_0);

    // Wait out_response.
    while(out_rdy.read() == "00") wait();
    cout << "After waiting out_result \n";
    cout << "After waiting out_result " << out_rdy.read();

    if (out_rdy.read() == "01")
    {
        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "01" || out_rdy.read() == "00") wait();

        cout << "Display FSMD Multiplier result: \n"
        << out_res.read().to_string()
        << "\n";
    }
    else if (out_rdy.read() == "10")
    {
        cout << "Display FSMD Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";

        while(out_rdy.read() == "10" || out_rdy.read() == "00") wait();

        cout << "Display Float Multiplier out_result: \n"
        << out_res.read().to_string()
        << "\n";
    }
//==============================================================================
    cout << "End tb::run()." << endl;
    sc_stop();
}
//==============================================================================
