--------------------------------------------------------------------------------
-- Company:     Univeristy of Verona
-- Engineer:    Luigi Capogrosso
--
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
-- Package definition
PACKAGE multiplier745_vhd_apb_wrapper_pkg IS
	-- Inputs and outputs size.
    CONSTANT SIZE       : INTEGER := 32;
    -- FSM states definition.
    CONSTANT S_0       : INTEGER := 0;
    CONSTANT S_1       : INTEGER := 1;
    CONSTANT S_2       : INTEGER := 2;
    CONSTANT S_3       : INTEGER := 3;
    CONSTANT ST_4       : INTEGER := 4;
    SUBTYPE TYPE_STATE IS INTEGER RANGE S_0 TO ST_4;
END multiplier745_vhd_apb_wrapper_pkg;
--
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.NUMERIC_STD.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

USE WORK.multiplier745_vhd_apb_wrapper_pkg.ALL;

--------------------------------------------------------------------------------
-- Model multiplierIEEE745_vhd_apb_wrapper
ENTITY multiplier745_vhd_apb_wrapper IS
	PORT (
        -- Inputs.
		pclk	: IN  std_logic;
		presetn : IN  std_logic;
		paddr 	: IN  std_logic_vector(31 downto 0);
		psel 	: IN  std_logic;
		penable : IN  std_logic;
		pwrite 	: IN  std_logic;
		pwdata 	: IN  std_logic_vector(31 downto 0);
        -- Outputs.
		pready 	: OUT std_logic;
		prdata 	: OUT std_logic_vector(31 downto 0)
	);
END multiplier745_vhd_apb_wrapper;

--------------------------------------------------------------------------------
ARCHITECTURE a1 OF multiplier745_vhd_apb_wrapper IS
	-- Components.
	COMPONENT multiplier754_vhd
		PORT (
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
	-- Signals.
    signal clk		    : std_logic;
    signal rst		    : std_logic;
	signal in_op1		: std_logic_vector(SIZE - 1 DOWNTO 0);
	signal in_op2		: std_logic_vector(SIZE - 1 DOWNTO 0);
	signal in_rdy       : std_logic;
    signal out_res      : std_logic_vector(SIZE - 1 DOWNTO 0);
	signal out_rdy      : std_logic;
	signal tmp   	    : std_logic_vector(SIZE - 1 DOWNTO 0);
	signal next_state   : TYPE_STATE := S_0;
BEGIN
clk <= pclk;
rst <= presetn;
-- Finite State Machine.
PROCESS (clk, rst) IS
BEGIN
	IF rst = '1' THEN
		next_state <= S_0;
	ELSIF clk'EVENT AND clk = '1' THEN
		CASE next_state IS
			WHEN S_0 =>
				IF penable = '1' THEN
					next_state <= S_1;
				ELSE
					next_state <= S_0;
				END IF;
			WHEN S_1 =>
				IF penable = '0' THEN
					next_state <= S_2;
				ELSE
					next_state <= S_1;
				END IF;
			WHEN S_2 =>
				IF penable = '1' THEN
					next_state <= S_3;
				ELSE
					next_state <= S_2;
				END IF;
			WHEN S_3 =>
				IF out_rdy = '1' THEN
					next_state <= ST_4;
				ELSE
					next_state <= S_3;
				END IF;
			WHEN ST_4 =>
				IF penable = '0' THEN
					next_state <= S_0;
				ELSE
					next_state <= ST_4;
				END IF;
			WHEN others =>
				next_state <= S_0;
		END CASE;
	END IF;
END PROCESS;
-- Datapath.
PROCESS (next_state) IS
BEGIN
	CASE next_state IS
		WHEN S_0 =>
			pready <= '0';
			prdata <= (others => '0');
			in_rdy <= '1';
			in_op1 <= (others => '0');
			in_op2 <= (others => '0');
			tmp <= (others => '0');
		WHEN S_1 =>
			tmp <= pwdata;
		WHEN S_2 =>
			-- NTD.
		WHEN S_3 =>
			in_op1 <= tmp;
			in_op2 <= pwdata;
			in_rdy <= '1';
		WHEN ST_4 =>
			prdata <= out_res;
			pready <= '1';
		WHEN others =>
			-- NTD.
	END CASE;
END PROCESS;
-- Components mapping.
multiplier754_0 : multiplier754_vhd
	PORT MAP(
        in_op1 	=> in_op1,
        in_op2 	=> in_op2,
        in_rdy 	=> in_rdy,
        out_res => out_res,
        out_rdy => out_rdy,
        clk 	=> clk,
        rst 	=> rst
	);
END a1;
--
--------------------------------------------------------------------------------
