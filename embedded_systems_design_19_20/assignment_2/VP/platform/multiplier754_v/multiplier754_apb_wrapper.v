`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////
// Company:     University of Verona
// Engineer:    Luigi Capogrosso
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FSM states definition.
`define S_0        0
`define S_1        1
`define S_2        2
`define S_3        3
`define S_4        4
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Mudule multiplierIEEE745_verilog_apb_wrapper
module multiplier745_v_apb_wrapper (
    input  pclk,
    input  presetn,
    input  paddr,
    input  psel,
    input  penable,
    input  pwrite,
    input  pwdata,
    output pready,
    output prdata
    );
    // Inputs and outputs size.
    parameter SIZE           = 32;
    // Inputs.
    wire pclk;
    wire psel;
    wire pwrite;
    wire presetn;
    wire penable;
    wire [SIZE - 1:0] paddr;
    wire [SIZE - 1:0] pwdata;
    // Outputs.
    reg pready;
    reg [SIZE - 1:0] prdata;
    // Signals.
    reg [SIZE - 1:0] tmp;
    // To describe the finite set of states.
    reg [5:0] next_state = `S_0;
    // Component of multiplier754_v
    reg [SIZE - 1:0] in_op1;
    reg [SIZE - 1:0] in_op2;
    reg in_rdy;
    wire [SIZE - 1:0] out_res;
    wire res_rdy;
    multiplier754_v multiplier754_0(
        .in_op1(in_op1),
        .in_op2(in_op2),
        .in_rdy(in_rdy),
        .out_res(out_res),
        .out_rdy(res_rdy),
        .clk(pclk),
        .rst(presetn)
    );
    // Finite State Machine.
    always @(posedge pclk, posedge presetn)
    begin
        if (presetn == 1'b1)
            next_state <= `S_0;
        else begin
            case (next_state)
                `S_0:
                begin
                    if (penable == 1'b1)
                        next_state <= `S_1;
                    else
                        next_state <= `S_0;
                end
                `S_1:
                begin
                    if (penable == 1'b0)
                        next_state <= `S_2;
                    else
                        next_state <= `S_1;
                end
                `S_2:
                begin
                    if (penable == 1'b1)
                        next_state <= `S_3;
                    else
                        next_state <= `S_2;
                end
                `S_3:
                begin
                    if (res_rdy == 1'b1)
                        next_state <= `S_4;
                    else
                        next_state <= `S_3;
                end
                `S_4:
                begin
                    if (penable == 1'b0)
                        next_state <= `S_0;
                    else
                        next_state <= `S_4;
                end
                default:
                begin
                    next_state <= `S_0;
                end
            endcase
        end
    end
    // Datapath.
    always @(next_state)
    begin
        case (next_state)
            `S_0:
            begin
                pready <= 1'b0;
                prdata <= 0;
                in_op1 <= 0;
                in_op2 <= 0;
                in_rdy <= 1'b0;
                tmp <= 0;
            end
            `S_1:
            begin
                tmp <= pwdata;
            end
            `S_2:
            begin
                // NTD.
            end
            `S_3:
            begin
                in_op1 <= tmp;
                in_op2 <= pwdata;
                in_rdy <= 1'b1;
            end
            `S_4:
            begin
                prdata <= out_res;
                pready <= 1'b1;
            end
            default:
            begin
                // NTD.
            end
        endcase
    end
endmodule
//
////////////////////////////////////////////////////////////////////////////////
