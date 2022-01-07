--------------------------------------------------------------------------------
-- Company:     Univeristy of Verona
-- Engineer:    Luigi Capogrosso
--
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
-- Package definition.
PACKAGE multiplier754_package IS
    -- Inputs and outputs size.
    CONSTANT SIZE           :   INTEGER := 32;
    CONSTANT EXPONENT_SIZE  :   INTEGER := 8;
    CONSTANT MANTISSA_SIZE  :   INTEGER := 23;
    -- FSM states definition.
    CONSTANT S_0        :   INTEGER := 0;
    CONSTANT S_1        :   INTEGER := 1;
    CONSTANT S_2        :   INTEGER := 2;
    CONSTANT S_3        :   INTEGER := 3;
    CONSTANT S_4        :   INTEGER := 4;
    CONSTANT S_5        :   INTEGER := 5;
    CONSTANT S_6        :   INTEGER := 6;
    CONSTANT S_7        :   INTEGER := 7;
    CONSTANT S_8        :   INTEGER := 8;
    CONSTANT S_9        :   INTEGER := 9;
    CONSTANT S_10       :   INTEGER := 10;
    CONSTANT S_11       :   INTEGER := 11;
    CONSTANT S_12       :   INTEGER := 12;
    CONSTANT S_13       :   INTEGER := 13;
    CONSTANT S_14       :   INTEGER := 14;
    CONSTANT S_15       :   INTEGER := 15;
    CONSTANT S_NAN      :   INTEGER := 16;
    CONSTANT S_INF      :   INTEGER := 17;
    CONSTANT S_ZERO     :   INTEGER := 18;
    CONSTANT S_ROUND    :   INTEGER := 19;
    CONSTANT S_NORM     :   INTEGER := 20;
    CONSTANT S_DENORM   :   INTEGER := 21;
    CONSTANT S_END      :   INTEGER := 22;
    SUBTYPE STATE_T IS INTEGER RANGE S_0 TO S_END;
END multiplier754_package;
--
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.std_logic_unsigned.ALL;
USE IEEE.numeric_std.ALL;

USE WORK.multiplier754_package.ALL;


-- Model multiplier754.
ENTITY multiplier754_vhd IS
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
END multiplier754_vhd;


-- Architecture behavioral of VHDL multiplier754 model.
ARCHITECTURE a1 OF multiplier754_vhd IS
    -- To describe the finite set of states.
    SIGNAL state        :   STATE_T := S_0;
    SIGNAL next_state   :   STATE_T := S_0;
    -- Floatig point 754 single precison rapresentation.
    SIGNAL e            :   std_logic_vector(EXPONENT_SIZE - 1 DOWNTO 0);
    SIGNAL m            :   std_logic_vector(MANTISSA_SIZE - 1 DOWNTO 0);
    SIGNAL s            :   std_logic;
    -- Temporary signals for calculation.
    SIGNAL m1       : std_logic_vector(MANTISSA_SIZE DOWNTO 0)
                    := (others => '0');
    SIGNAL m2       : std_logic_vector(MANTISSA_SIZE DOWNTO 0)
                    := (others => '0');
    SIGNAL tmp_m    : std_logic_vector(((MANTISSA_SIZE + 1) * 2) - 1 DOWNTO 0)
                    := (others => '0');
    SIGNAL e1       : std_logic_vector(EXPONENT_SIZE - 1 DOWNTO 0)
                    := (others => '0');
    SIGNAL e2       : std_logic_vector(EXPONENT_SIZE - 1 DOWNTO 0)
                    := (others => '0');
    SIGNAL tmp_e    : std_logic_vector(EXPONENT_SIZE DOWNTO 0)
                    := (others => '0');
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
                IF in_rdy = '1' THEN
                    next_state <= S_2;
                -- S_1 to S_1.
                ELSE
                    next_state <= S_1;
                END IF;
            WHEN S_2 =>
                -- S_2 to S_NAN (e1 & e2 are NaN).
                IF (e1 = 255 AND m1 /= 0) OR
                   (e2 = 255 AND m2 /= 0) THEN
                    next_state <= S_NAN;
                -- S_2 to S_NAN (e1 is inf. & e2 is 0 or vice-versa).
                ELSIF (e1 = 255 AND m1 = 0 AND e2 = 0 AND m2 = 0) OR
                      (e1 = 0 AND m1 = 0 AND e2 = 255 AND m2 = 0) THEN
                    next_state <= S_NAN;
                -- S_2 to S_INF (e1 & e2 are inf).
                ELSIF (e1 = 255 AND m1 = 0) OR
                      (e2 = 255 AND m2 = 0) THEN
                    next_state <= S_INF;
                -- S_2 to S_ZERO (e1 & e2 are 0).
                ELSIF (e1 = 0 AND m1 = 0) OR
                      (e2 = 0 AND m2 = 0) THEN
                    next_state <= S_ZERO;
                -- S_2 to S_3 (e1 & e2 are normalized or denormalized).
                ELSE
                    next_state <= S_3;
                END IF;
            WHEN S_3 =>
                -- S_3 to S_6 (e1 & e2 are denormalized).
                IF (e1 = 0 AND e2 = 0) THEN
                    next_state <= S_6;
                -- S_3 to S_4 (e1 is denormalized).
                ELSIF (e1 = 0) THEN
                    next_state <= S_4;
                -- S_3 to S_5 (e2 is denormalized).
                ELSIF (e2 = 0) THEN
                    next_state <= S_5;
                -- S_3 to S_7 (e1 & e2 are normalized)
                ELSE
                    next_state <= S_7;
                END IF;
            WHEN S_4 =>
                -- S_4 to S_7.
                next_state <= S_7;
            WHEN S_5 =>
                -- S_5 to S_7.
                next_state <= S_7;
            WHEN S_6 =>
                -- S_6 to S_7.
                next_state <= S_7;
            WHEN S_7 =>
                -- S_7 to S_8 (shift-right once).
                IF tmp_m(47 DOWNTO 46) = "10" OR
                   tmp_m(47 DOWNTO 46) = "11" THEN
                    next_state <= S_8;
                -- S_7 to S_9 (do shift-left).
                ELSIF tmp_m(47 DOWNTO 46) = "00" THEN
                    next_state <= S_9;
                -- S_7 to S_NORM (no right/left-shift is necessary).
                ELSIF tmp_m(47 DOWNTO 46) = "01" THEN
                    next_state <= S_NORM;
                END IF;
            WHEN S_8 =>
                -- S_8 to S_NORM.
                next_state <= S_NORM;
            WHEN S_9 =>
                -- S_9 to S_10 (overflow).
                IF tmp_e(8) = '1' THEN
                    next_state <= S_10;
                -- S_9 to S_11 (not in overflow, but risk underflow).
                ELSIF tmp_e(8) = '0' THEN
                    next_state <= S_11;
                END IF;
            WHEN S_10 =>
                -- S_10 to S_10 (still shif).
                IF tmp_m(47 DOWNTO 46) = "00" THEN
                    next_state <= S_10;
                -- S_10 to S_NORM (end shift).
                ELSIF tmp_m(47 DOWNTO 46) = "01" THEN
                    next_state <= S_NORM;
                END IF;
            WHEN S_11 =>
                -- S_11 to S_11 (still shif).
                IF tmp_m(47 DOWNTO 46) = "00" THEN
                    next_state <= S_11;
                -- S_11 to S_DENORM (underflow).
                ELSIF tmp_e(8 DOWNTO 0) = 0 THEN
                    next_state <= S_DENORM;
                -- S_11 to S_NORM (end shift).
                ELSE
                    next_state <= S_NORM;
                END IF;
            WHEN S_12 =>
                -- S_12 to S_13.
                next_state <= S_13;
            WHEN S_13 =>
                -- S_13 to S_ROUND.
                IF tmp_m(22) = '1' THEN
                    next_state <= S_ROUND;
                -- S_13 to S_14.
                ELSIF tmp_m(22) = '0' THEN
                    next_state <= S_14;
                END IF;
            WHEN S_14 =>
                -- S_14 to S_END.
                next_state <= S_END;
            WHEN S_15 =>
                -- S_15 to S_NORM.
                next_state <= S_NORM;
            WHEN S_NAN =>
                -- S_NAN to S_END.
                next_state <= S_END;
            WHEN S_INF =>
                -- S_INF to S_END.
                next_state <= S_END;
            WHEN S_ZERO =>
                -- S_ZERO to S_END.
                next_state <= S_END;
            WHEN S_ROUND =>
                IF tmp_m(47 DOWNTO 46) = "01" THEN
                    next_state <= S_14;
                ELSIF tmp_m(47 DOWNTO 46) = "10" THEN
                    next_state <= S_15;
                END IF;
            WHEN S_NORM =>
                -- S_NORM to S_12 (not in overflow).
                IF tmp_e(8) = '0' THEN
                    next_state <= S_12;
                -- S_NORM to S_INF (overflow).
                ELSIF tmp_e(8) = '1' THEN
                    next_state <= S_INF;
                END IF;
            WHEN S_DENORM =>
                -- S_DENORM to S_13.
                next_state <= S_13;
            WHEN S_END =>
                -- S_END to S_0.
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
            -- Floatig point 754 single precison rapresentation initialization.
            e <= (OTHERS => '0');
            m <= (OTHERS => '0');
            s <= '0';
            -- Temporary signals for calculation initialization.
            m1 <= (OTHERS => '0');
            m2 <= (OTHERS => '0');
            tmp_m <= (OTHERS => '0');
            e1 <= (OTHERS => '0');
            e1 <= (OTHERS => '0');
            tmp_e <= (OTHERS => '0');
            out_res <= (OTHERS => '0');
            out_rdy <= '0';
        WHEN S_1 =>
            -- NTD.
        WHEN S_2 =>
            -- Get the mantissa from the two input numbers.
            m1(22 DOWNTO 0) <= in_op1(22 DOWNTO 0);
            m2(22 DOWNTO 0) <= in_op2(22 DOWNTO 0);
            -- Get the exponent from the two input numbers.
            e1 <= in_op1(30 DOWNTO 23);
            e2 <= in_op2(30 DOWNTO 23);
        WHEN S_3 =>
            m1(23) <= '1';
            m2(23) <= '1';
        WHEN S_4 =>
            m1(23) <= '0';
        WHEN S_5 =>
            m2(23) <= '0';
        WHEN S_6 =>
            m1(23) <= '0';
            m2(23) <= '0';
        WHEN S_7 =>
            tmp_e <= '0' & e1 + e2 - 127;
            tmp_m <= m1 * m2;
        WHEN S_8 =>
            tmp_m <= std_logic_vector(unsigned(tmp_m) SRL 1);
            tmp_e <= tmp_e + 1;
        WHEN S_9 =>
            -- NTD.
        WHEN S_10 =>
            tmp_m <= std_logic_vector(unsigned(tmp_m) SLL 1);
            tmp_e <= tmp_e - 1;
        WHEN S_11 =>
            tmp_m <= std_logic_vector(unsigned(tmp_m) SLL 1);
            tmp_e <= tmp_e - 1;
        WHEN S_12 =>
            e <= tmp_e(7 DOWNTO 0);
        WHEN S_13 =>
            -- NTD.
        WHEN S_14 =>
            m <= tmp_m(45 DOWNTO 23);
            s <= in_op1(31) XOR in_op2(31);
        WHEN S_15 =>
            tmp_e <= tmp_e + 1;
        WHEN S_NAN =>
            e <= (OTHERS => '1');
            m <= (22 => '1', 21 DOWNTO 0 => '0');
        WHEN S_INF =>
            e <= (OTHERS => '1');
            m <= (OTHERS => '0');
            s <= in_op1(31) XOR in_op2(31);
        WHEN S_ZERO =>
            e <= (OTHERS => '0');
            m <= (OTHERS => '0');
            s <= in_op1(31) XOR in_op2(31);
        WHEN S_ROUND =>
            tmp_m(47 DOWNTO 22) <= tmp_m(47 DOWNTO 22) + 1;
        WHEN S_NORM =>
            -- NTD.
        WHEN S_DENORM =>
            e <= (OTHERS => '0');
        WHEN S_END =>
            out_res(31) <= s;
            out_res(30 DOWNTO 23) <= e;
            out_res(22 DOWNTO 0)  <= m;
            out_rdy <= '1';
        WHEN OTHERS =>
            -- NTD.
    END CASE;
END PROCESS;
END a1;
--
--------------------------------------------------------------------------------
