`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////
// Company:     University of Verona
// Engineer:    Luigi Capogrosso
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// FSM states definition.
`define S_0         0
`define S_1         1
`define S_2         2
`define S_3         3
`define S_4         4
`define S_5         5
`define S_6         6
`define S_7         7
`define S_8         8
`define S_9         9
`define S_10        10
`define S_11        11
`define S_12        12
`define S_13        13
`define S_14        14
`define S_15        15
`define S_NAN       16
`define S_INF       17
`define S_ZERO      18
`define S_ROUND     19
`define S_NORM      20
`define S_DENORM    21
`define S_END       22
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Mudule multiplier754.
module multiplier754_v (
    input clk,
    input rst,
    input in_op1,
    input in_op2,
    input in_rdy,
    output out_res,
    output out_rdy
    );
    // Inputs and outputs size.
    parameter SIZE           = 32;
    parameter EXPONENT_SIZE  = 8;
    parameter MANTISSA_SIZE  = 23;
    // Inputs.
    wire clk;
    wire rst;
    wire [SIZE - 1:0] in_op1;
    wire [SIZE - 1:0] in_op2;
    wire in_rdy;
    // Outputs.
    reg [SIZE - 1:0] out_res;
    reg out_rdy;
    // To describe the finite set of states.
    reg [5:0] state = `S_0;
    reg [5:0] next_state = `S_0;
    // Floatig point 754 single precison rapresentation.
    reg [EXPONENT_SIZE - 1:0] e;
    reg [MANTISSA_SIZE - 1:0] m;
    reg s;
    // Temporary signals for calculation.
    reg [MANTISSA_SIZE:0] m1;
    reg [MANTISSA_SIZE:0] m2;
    reg [(((MANTISSA_SIZE + 1) * 2) - 1):0] tmp_m;
    reg [EXPONENT_SIZE - 1:0] e1;
    reg [EXPONENT_SIZE - 1:0] e2;
    reg [EXPONENT_SIZE:0] tmp_e;
    // Finite State Machine.
    always @(posedge clk, posedge rst)
    begin
        if (rst == 1'b1)
        begin
            next_state <= `S_0;
        end
        else
        begin
            case (state)
                `S_0:
                begin
                    // S_0 to S_1.
                    next_state <= `S_1;
                end
                `S_1:
                begin
                    // S_1 to S_2.
                    if (in_rdy == 1'b1)
                        next_state <= `S_2;
                    // S_1 to S_1.
                    else
                        next_state <= `S_1;
                end
                `S_2:
                begin
                    // S_2 to S_NAN (e1 & e2 are NaN).
                    if ((e1 == 8'hFF && m1 != 0) ||
                       (e2 == 8'hFF && m2 != 0))
                    begin
                        next_state <= `S_NAN;
                    end
                    // S_2 to S_NAN (e1 is inf. & e2 is 0 or vice-versa).
                    else if ((e1 == 8'hFF && m1 == 0 && e2 == 0 && m2 == 0) ||
                            (e1 == 0 && m1 == 0 && e2 == 8'hFF && m2 == 0))
                    begin
                        next_state <= `S_NAN;
                    end
                    // S_2 to S_INF (e1 & e2 are inf).
                    else if ((e1 == 8'hFF && m1 == 0) ||
                            (e2 == 8'hFF && m2 == 0))
                    begin
                        next_state <= `S_INF;
                    end
                    // S_2 to S_ZERO (e1 & e2 are 0).
                    else if ((e1 == 0 && m1 == 0) ||
                            (e2 == 0 && m2 == 0))
                    begin
                        next_state <= `S_ZERO;
                    end
                    // S_2 to S_3 (e1 & e2 are normalized or denormalized).
                    else
                    begin
                        next_state <= `S_3;
                    end
                end
                `S_3:
                begin
                    // S_3 to S_6 (e1 & e2 are denormalized).
                    if (e1 == 0 && e2 == 0)
                    begin
                        next_state <= `S_6;
                    end
                    // S_3 to S_4 (e1 is denormalized).
                    if (e1 == 0)
                    begin
                        next_state <= `S_4;
                    end
                    // S_3 to S_5 (e2 is denormalized).
                    if (e2 == 0)
                    begin
                        next_state <= `S_5;
                    end
                    // S_3 to S_7 (e1 & e2 are normalized).
                    else
                    begin
                        next_state <= `S_7;
                    end
                end
                `S_4:
                begin
                    // S_4 to S_7.
                    next_state <= `S_7;
                end
                `S_5:
                begin
                    // S_5 to S_7.
                    next_state <= `S_7;
                end
                `S_6:
                begin
                    // S_6 to S_7.
                    next_state <= `S_7;
                end
                `S_7:
                begin
                    // S_7 to S_8 (shift-right once).
                    if (tmp_m[47:46] == 2'b10 || tmp_m[47:46] == 2'b11)
                    begin
                        next_state <= `S_8;
                    end
                    // S_7 to S_9 (do shift-left).
                    else if (tmp_m[47:46] == 2'b00)
                    begin
                        next_state <= `S_9;
                    end
                    // S_7 to S_NORM (no right/left-shift is necessary).
                    else if (tmp_m[47:46] == 2'b01)
                    begin
                        next_state <= `S_NORM;
                    end
                end
                `S_8:
                begin
                    // S_8 to S_NORM.
                    next_state <= `S_NORM;
                end
                `S_9:
                begin
                    // S_9 to S_10 (overflow).
                    if (tmp_e[8] == 1'b1)
                    begin
                        next_state <= `S_10;
                    end
                    // S_9 to S_11 (not in overflow, but risk underflow).
                    else if (tmp_e[8] == 1'b0)
                    begin
                        next_state <= `S_11;
                    end
                end
                `S_10:
                begin
                    // S_10 to S_10 (still shif).
                    if (tmp_m[47:46] == 2'b00)
                    begin
                        next_state <= `S_10;
                    end
                    // S_10 to S_NORM (end shift).
                    else if (tmp_m[47:46] == 2'b01)
                    begin
                        next_state <= `S_NORM;
                    end
                end
                `S_11:
                begin
                    // S_11 to S_11 (still shif).
                    if (tmp_m[47:46] == 2'b00)
                    begin
                        next_state <= `S_11;
                    end
                    // S_11 to S_DENORM (underflow).
                    else if (tmp_e == 0)
                    begin
                        next_state <= `S_DENORM;
                    end
                    // S_11 to S_NORM (end shift).
                    else
                    begin
                        next_state <= `S_NORM;
                    end
                end
                `S_12:
                begin
                    // S_12 to S_13.
                    next_state <= `S_13;
                end
                `S_13:
                begin
                    // S_13 to S_ROUND.
                    if (tmp_m[22] == 1'b1)
                    begin
                        next_state <= `S_ROUND;
                    end
                    // S_13 to S_14.
                    else if (tmp_m[22] == 1'b0)
                    begin
                        next_state <= `S_14;
                    end
                end
                `S_14:
                begin
                    // S_14 to S_END.
                    next_state <= `S_END;
                end
                `S_15:
                begin
                    // S_15 to S_NORM.
                    next_state <= `S_NORM;
                end
                `S_NAN:
                begin
                    // S_NAN to S_END.
                    next_state <= `S_END;
                end
                `S_INF:
                begin
                    // S_INF to S_END.
                    next_state <= `S_END;
                end
                `S_ZERO:
                begin
                    // S_ZERO to S_END.
                    next_state <= `S_END;
                end
                `S_ROUND:
                begin
                    if (tmp_m[47:46] == 2'b01)
                    begin
                        next_state <= `S_14;
                    end
                    else if (tmp_m[47:46] == 2'b10)
                    begin
                        next_state <= `S_15;
                    end
                end
                `S_NORM:
                begin
                    // S_NORM to S_12 (not in overflow).
                    if (tmp_e[8] == 1'b0)
                    begin
                        next_state <= `S_12;
                    end
                    // S_NORM to S_INF (overflow).
                    else if (tmp_e[8] == 1'b1)
                    begin
                        next_state <= `S_INF;
                    end
                end
                `S_DENORM:
                begin
                    // S_DENORM to S_13.
                    next_state <= `S_13;
                end
                `S_END:
                begin
                    next_state <= `S_0;
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
        state <= next_state;
        case(next_state)
            `S_0:
            begin
                // Floatig point 754 single precison rapresent. initialization.
                e       <= 0;
                m       <= 0;
                s       <= 0;
                // Temporary signals for calculation initialization.
                m1      <= 0;
                m2      <= 0;
                tmp_m   <= 0;
                e1      <= 0;
                e2      <= 0;
                tmp_e   <= 0;
                out_res <= 0;
                out_rdy <= 0;
            end
            `S_1:
            begin
                // NTD.
            end
            `S_2:
            begin
                // Get the mantissa from the two input numbers.
                m1[22:0] <= in_op1[22:0];
                m2[22:0] <= in_op2[22:0];
                // Get the exponent from the two input numbers.
                e1 <= in_op1[30:23];
                e2 <= in_op2[30:23];
            end
            `S_3:
            begin
                m1[23] <= 1'b1;
                m2[23] <= 1'b1;
            end
            `S_4:
            begin
                m1[23] <= 1'b0;
            end
            `S_5:
            begin
                m2[23] <= 1'b0;
            end
            `S_6:
            begin
                m1[23] <= 1'b0;
                m2[23] <= 1'b0;
            end
            `S_7:
            begin
                tmp_e <= e1 + e2 - 8'd127;
                tmp_m <= m1 * m2;
            end
            `S_8:
            begin
                tmp_m <= tmp_m >> 1;
                tmp_e <= tmp_e + 9'd1;
            end
            `S_9:
            begin
                // NTD.
            end
            `S_10:
            begin
                tmp_m <= tmp_m << 1;
                tmp_e <= tmp_e - 9'd1;
            end
            `S_11:
            begin
                tmp_m <= tmp_m << 1;
                tmp_e <= tmp_e - 9'd1;
            end
            `S_12:
            begin
                e <= tmp_e[7:0];
            end
            `S_13:
            begin
                // NTD.
            end
            `S_14:
            begin
                m <= tmp_m[45:23];
                s <= in_op1[31] ^ in_op2[31];
            end
            `S_15:
            begin
                tmp_e <= tmp_e + 9'd1;
            end
            `S_NAN:
            begin
                e <= 8'hFF;
                m <= {1'b1, 22'b0};
            end
            `S_INF:
            begin
                e <= 8'hFF;
                m <= 23'd0;
                s <= in_op1[31] ^ in_op2[31];
            end
            `S_ZERO:
            begin
                e <= 8'h00;
                m <= 23'd0;
                s <= in_op1[31] ^ in_op2[31];
            end
            `S_ROUND:
            begin
                tmp_m[47:22] <= tmp_m[47:22] + 26'd1;
            end
            `S_NORM:
            begin
                // NTD.
            end
            `S_DENORM:
            begin
                e <= 8'd0;
            end
            `S_END:
            begin
                out_res[31]    <= s;
                out_res[30:23] <= e;
                out_res[22:0]  <= m;
                out_rdy        <= 1'b1;
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
