`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////
// Company:     University of Verona
// Engineer:    Luigi Capogrosso
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Mudule tb.
module tb();
    parameter SIZE = 32;
    parameter CLK_PERIOD = 2;
    // Inputs.
    reg clk;
    reg rst;
    reg [SIZE - 1:0] in_op1;
    reg [SIZE - 1:0] in_op2;
    reg [1:0] in_rdy;
    // Outputs.
    wire [SIZE-1:0] out_res;
    wire [1:0] out_rdy;
    // tl connection.
    tl dut(
        .clk(clk),
        .rst(rst),
        .in_op1(in_op1),
        .in_op2(in_op2),
        .in_rdy(in_rdy),
        .out_res(out_res),
        .out_rdy(out_rdy)
        );
    // clk update.
    always #(CLK_PERIOD / 2) clk <= !clk;
    ////////////////////////////////////////////////////////////////////////////
    // Test n.1
    initial
    begin
        clk     = 1'b0;
        rst     = #(CLK_PERIOD * 2) 1'b1;
        rst     = #(CLK_PERIOD)     1'b0;
        in_rdy  = 2'b00;

        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end

        in_rdy = 2'b00;
    ////////////////////////////////////////////////////////////////////////////
    // Test n.2
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.3
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.4
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.5
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.6
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.7
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.8
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.9
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.10
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.11
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.12
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.13
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.14
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.15
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.16
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.17
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.18
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.19
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.20
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.21
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    // Test n.22
        in_op1 <= 32'b00111111000000000000000000000000;
        in_op2 <= 32'b01000000000000000000000000000000;

        in_rdy = #(CLK_PERIOD) 2'b11;
        in_rdy = #(CLK_PERIOD) 2'b00;

        while (out_rdy == 2'b00)
            #(CLK_PERIOD);

        if (out_rdy == 2'b01)
        begin
            $display("v_res: %x", out_res);
            while (out_rdy == 2'b01)
                #(CLK_PERIOD);
            $display("vhd_res: %x", out_res);
        end

        else if (out_rdy == 2'b10)
        begin
            $display("vhd_res: %x", out_res);
            while (out_rdy == 2'b10)
                #(CLK_PERIOD);
            $display("v_res: %x", out_res);
        end
    ////////////////////////////////////////////////////////////////////////////
    end
endmodule
