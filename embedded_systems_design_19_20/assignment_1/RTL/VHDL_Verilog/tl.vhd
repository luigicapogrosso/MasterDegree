--------------------------------------------------------------------------------
-- Company:     Univeristy of Verona
-- Engineer:    Luigi Capogrosso
--
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
-- Package definition.
PACKAGE tl_package IS
    -- Inputs and outputs size.
    CONSTANT SIZE       :   INTEGER := 32;

    -- FSM states definition.
    CONSTANT S_0        :   INTEGER := 0;
    CONSTANT S_1        :   INTEGER := 1;
    CONSTANT S_2        :   INTEGER := 2;
    CONSTANT S_3        :   INTEGER := 3;
    CONSTANT S_4        :   INTEGER := 4;
    CONSTANT S_5        :   INTEGER := 5;
    SUBTYPE STATE_T IS INTEGER RANGE S_0 TO S_5;
END tl_package;
--
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

USE WORK.tl_package.ALL;


-- Entity tl.
ENTITY tl IS
    PORT(
        -- Inputs.
        clk     :   IN std_logic;
        rst     :   IN std_logic;
        in_op1  :   IN std_logic_vector(SIZE - 1 DOWNTO 0);
        in_op2  :   IN std_logic_vector(SIZE - 1 DOWNTO 0);
        in_rdy  :   IN std_logic_vector(1 DOWNTO 0);
        -- Outputs.
        out_res :   OUT std_logic_vector(SIZE - 1 DOWNTO 0);
        out_rdy :   OUT std_logic_vector(1 DOWNTO 0)
    );
end tl;


-- Architecture behavioral of VHDL tl entity.
ARCHITECTURE a1 OF tl IS
    -- To describe the finite set of states.
    SIGNAL state        :   STATE_T := S_0;
    SIGNAL next_state   :   STATE_T := S_0;
    -- VHDL component.
    SIGNAL vhd_res      :   std_logic_vector(SIZE - 1 DOWNTO 0);
    SIGNAL vhd_res_rdy  :   std_logic;
    -- Verilog component.
    SIGNAL v_res        :   std_logic_vector(SIZE - 1 DOWNTO 0);
    SIGNAL v_res_rdy    :   std_logic;
    -- Temporary signals for calculation.
    SIGNAL tmp          :   std_logic_vector(SIZE - 1 DOWNTO 0);

    COMPONENT multiplier754_vhd
        PORT(
            -- Inputs.
            clk     :   IN std_logic;
            rst     :   IN std_logic;
            in_op1  :   IN std_logic_vector(SIZE - 1 DOWNTO 0);
            in_op2  :   IN std_logic_vector(SIZE - 1 DOWNTO 0);
            in_rdy  :   IN std_logic;
            -- Outputs.
            out_res :   OUT std_logic_vector(SIZE - 1 DOWNTO 0);
            out_rdy :   OUT std_logic
        );
    END COMPONENT multiplier754_vhd;

    COMPONENT multiplier754_v
        PORT(
            -- Inputs.
            clk     :   IN std_logic;
            rst     :   IN std_logic;
            in_op1  :   IN std_logic_vector(SIZE - 1 DOWNTO 0);
            in_op2  :   IN std_logic_vector(SIZE - 1 DOWNTO 0);
            in_rdy  :   IN std_logic;
            -- Outputs.
            out_res :   OUT std_logic_vector(SIZE - 1 DOWNTO 0);
            out_rdy :   OUT std_logic
        );
    END COMPONENT multiplier754_v;
BEGIN
-- Finite State Machine.
PROCESS(clk, rst) IS
BEGIN
    IF rst = '1' THEN
        next_state <= S_0;
    ELSIF clk'EVENT AND clk = '1' THEN
        CASE state IS
            WHEN S_0 =>
                -- S_0 to S_1.
                next_state <= S_1;
            WHEN S_1 =>
                -- S_1 to S_2.
                IF (vhd_res_rdy = '1' AND v_res_rdy = '0') THEN
                    next_state <= S_2;
                END IF;
                -- S_1 to S_3.
                IF (vhd_res_rdy = '0' AND v_res_rdy = '1') THEN
                    next_state <= S_3;
                END IF;
                -- S_1 to S_4.
                IF (vhd_res_rdy = '1' AND v_res_rdy = '1') THEN
                    next_state <= S_4;
                -- S_1 to S_1.
                ELSE
                    next_state <= S_1;
                END IF;
            WHEN S_2 =>
                -- S_2 to S_1.
                next_state <= S_1;
            WHEN S_3 =>
                -- S_3 to S_1.
                next_state <= S_1;
            WHEN S_4 =>
                -- S_4 to S_1.
                next_state <= S_5;
            WHEN S_5 =>
                -- S_5 to S_0.
                next_state <= S_0;
            WHEN OTHERS =>
                next_state <= S_0;
        END CASE;
    END IF;
END PROCESS;
-- Datapath.
PROCESS(next_state) IS
BEGIN
    state <= next_state;
    CASE next_state IS
        WHEN S_0 =>
            tmp     <= (OTHERS => '0');
            out_res <= (OTHERS => '0');
            out_rdy <= "00";
        WHEN S_1 =>
            -- NTD.
        WHEN S_2 =>
            out_res <= v_res;
            out_rdy <= "01";
        WHEN S_3 =>
            out_res <= vhd_res;
            out_rdy <= "10";
        WHEN S_4 =>
            out_res <= v_res;
            tmp     <= vhd_res;
            out_rdy <= "01";
        WHEN S_5 =>
            out_res <= tmp;
            out_rdy <= "10";
        WHEN OTHERS =>
            -- NTD.
    END CASE;
END PROCESS;

dut_1 : multiplier754_vhd PORT MAP(
    clk     => clk,
    rst     => rst,
    in_op1  => in_op1,
    in_op2  => in_op2,
    in_rdy  => in_rdy(1),
    out_res => vhd_res,
    out_rdy => vhd_res_rdy
);

dut_2 : multiplier754_v PORT MAP(
    clk     => clk,
    rst     => rst,
    in_op1  => in_op1,
    in_op2  => in_op2,
    in_rdy  => in_rdy(0),
    out_res => v_res,
    out_rdy => v_res_rdy
);
END a1;
--
--------------------------------------------------------------------------------
