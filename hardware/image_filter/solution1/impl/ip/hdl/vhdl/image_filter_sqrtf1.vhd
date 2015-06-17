-- ==============================================================
-- RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
-- Version: 2015.1
-- Copyright (C) 2015 Xilinx Inc. All rights reserved.
-- 
-- ===========================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity image_filter_sqrtf1 is
port (
    ap_clk : IN STD_LOGIC;
    ap_rst : IN STD_LOGIC;
    ap_start : IN STD_LOGIC;
    ap_done : OUT STD_LOGIC;
    ap_continue : IN STD_LOGIC;
    ap_idle : OUT STD_LOGIC;
    ap_ready : OUT STD_LOGIC;
    p_read : IN STD_LOGIC_VECTOR (31 downto 0);
    ap_return : OUT STD_LOGIC_VECTOR (31 downto 0) );
end;


architecture behav of image_filter_sqrtf1 is 
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_ST_st1_fsm_0 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000000000000001";
    constant ap_ST_st2_fsm_1 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000000000000010";
    constant ap_ST_st3_fsm_2 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000000000000100";
    constant ap_ST_st4_fsm_3 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000000000001000";
    constant ap_ST_st5_fsm_4 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000000000010000";
    constant ap_ST_st6_fsm_5 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000000000100000";
    constant ap_ST_st7_fsm_6 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000000001000000";
    constant ap_ST_st8_fsm_7 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000000010000000";
    constant ap_ST_st9_fsm_8 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000000100000000";
    constant ap_ST_st10_fsm_9 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000001000000000";
    constant ap_ST_st11_fsm_10 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000010000000000";
    constant ap_ST_st12_fsm_11 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000100000000000";
    constant ap_ST_st13_fsm_12 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000001000000000000";
    constant ap_ST_st14_fsm_13 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000010000000000000";
    constant ap_ST_st15_fsm_14 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000100000000000000";
    constant ap_ST_st16_fsm_15 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000001000000000000000";
    constant ap_ST_st17_fsm_16 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000010000000000000000";
    constant ap_ST_st18_fsm_17 : STD_LOGIC_VECTOR (27 downto 0) := "0000000000100000000000000000";
    constant ap_ST_st19_fsm_18 : STD_LOGIC_VECTOR (27 downto 0) := "0000000001000000000000000000";
    constant ap_ST_st20_fsm_19 : STD_LOGIC_VECTOR (27 downto 0) := "0000000010000000000000000000";
    constant ap_ST_st21_fsm_20 : STD_LOGIC_VECTOR (27 downto 0) := "0000000100000000000000000000";
    constant ap_ST_st22_fsm_21 : STD_LOGIC_VECTOR (27 downto 0) := "0000001000000000000000000000";
    constant ap_ST_st23_fsm_22 : STD_LOGIC_VECTOR (27 downto 0) := "0000010000000000000000000000";
    constant ap_ST_st24_fsm_23 : STD_LOGIC_VECTOR (27 downto 0) := "0000100000000000000000000000";
    constant ap_ST_st25_fsm_24 : STD_LOGIC_VECTOR (27 downto 0) := "0001000000000000000000000000";
    constant ap_ST_st26_fsm_25 : STD_LOGIC_VECTOR (27 downto 0) := "0010000000000000000000000000";
    constant ap_ST_st27_fsm_26 : STD_LOGIC_VECTOR (27 downto 0) := "0100000000000000000000000000";
    constant ap_ST_st28_fsm_27 : STD_LOGIC_VECTOR (27 downto 0) := "1000000000000000000000000000";
    constant ap_const_lv32_0 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    constant ap_const_lv1_1 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv32_1B : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011011";

    signal ap_done_reg : STD_LOGIC := '0';
    signal ap_CS_fsm : STD_LOGIC_VECTOR (27 downto 0) := "0000000000000000000000000001";
    attribute fsm_encoding : string;
    attribute fsm_encoding of ap_CS_fsm : signal is "none";
    signal ap_sig_cseq_ST_st1_fsm_0 : STD_LOGIC;
    signal ap_sig_bdd_47 : BOOLEAN;
    signal ap_sig_bdd_61 : BOOLEAN;
    signal grp_fu_13_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal grp_fu_13_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal grp_fu_13_p0 : STD_LOGIC_VECTOR (31 downto 0);
    signal grp_fu_13_ce : STD_LOGIC;
    signal ap_sig_cseq_ST_st28_fsm_27 : STD_LOGIC;
    signal ap_sig_bdd_258 : BOOLEAN;
    signal ap_return_preg : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    signal ap_NS_fsm : STD_LOGIC_VECTOR (27 downto 0);

    component image_filter_fsqrt_32ns_32ns_32_28 IS
    generic (
        ID : INTEGER;
        NUM_STAGE : INTEGER;
        din0_WIDTH : INTEGER;
        din1_WIDTH : INTEGER;
        dout_WIDTH : INTEGER );
    port (
        clk : IN STD_LOGIC;
        reset : IN STD_LOGIC;
        din0 : IN STD_LOGIC_VECTOR (31 downto 0);
        din1 : IN STD_LOGIC_VECTOR (31 downto 0);
        ce : IN STD_LOGIC;
        dout : OUT STD_LOGIC_VECTOR (31 downto 0) );
    end component;



begin
    image_filter_fsqrt_32ns_32ns_32_28_U60 : component image_filter_fsqrt_32ns_32ns_32_28
    generic map (
        ID => 1,
        NUM_STAGE => 28,
        din0_WIDTH => 32,
        din1_WIDTH => 32,
        dout_WIDTH => 32)
    port map (
        clk => ap_clk,
        reset => ap_rst,
        din0 => grp_fu_13_p0,
        din1 => grp_fu_13_p1,
        ce => grp_fu_13_ce,
        dout => grp_fu_13_p2);





    -- the current state (ap_CS_fsm) of the state machine. --
    ap_CS_fsm_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_CS_fsm <= ap_ST_st1_fsm_0;
            else
                ap_CS_fsm <= ap_NS_fsm;
            end if;
        end if;
    end process;


    -- ap_done_reg assign process. --
    ap_done_reg_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_done_reg <= ap_const_logic_0;
            else
                if ((ap_const_logic_1 = ap_continue)) then 
                    ap_done_reg <= ap_const_logic_0;
                elsif ((ap_const_logic_1 = ap_sig_cseq_ST_st28_fsm_27)) then 
                    ap_done_reg <= ap_const_logic_1;
                end if; 
            end if;
        end if;
    end process;


    -- ap_return_preg assign process. --
    ap_return_preg_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_return_preg <= ap_const_lv32_0;
            else
                if ((ap_const_logic_1 = ap_sig_cseq_ST_st28_fsm_27)) then 
                    ap_return_preg <= grp_fu_13_p2;
                end if; 
            end if;
        end if;
    end process;


    -- the next state (ap_NS_fsm) of the state machine. --
    ap_NS_fsm_assign_proc : process (ap_CS_fsm, ap_sig_bdd_61)
    begin
        case ap_CS_fsm is
            when ap_ST_st1_fsm_0 => 
                if (not(ap_sig_bdd_61)) then
                    ap_NS_fsm <= ap_ST_st2_fsm_1;
                else
                    ap_NS_fsm <= ap_ST_st1_fsm_0;
                end if;
            when ap_ST_st2_fsm_1 => 
                ap_NS_fsm <= ap_ST_st3_fsm_2;
            when ap_ST_st3_fsm_2 => 
                ap_NS_fsm <= ap_ST_st4_fsm_3;
            when ap_ST_st4_fsm_3 => 
                ap_NS_fsm <= ap_ST_st5_fsm_4;
            when ap_ST_st5_fsm_4 => 
                ap_NS_fsm <= ap_ST_st6_fsm_5;
            when ap_ST_st6_fsm_5 => 
                ap_NS_fsm <= ap_ST_st7_fsm_6;
            when ap_ST_st7_fsm_6 => 
                ap_NS_fsm <= ap_ST_st8_fsm_7;
            when ap_ST_st8_fsm_7 => 
                ap_NS_fsm <= ap_ST_st9_fsm_8;
            when ap_ST_st9_fsm_8 => 
                ap_NS_fsm <= ap_ST_st10_fsm_9;
            when ap_ST_st10_fsm_9 => 
                ap_NS_fsm <= ap_ST_st11_fsm_10;
            when ap_ST_st11_fsm_10 => 
                ap_NS_fsm <= ap_ST_st12_fsm_11;
            when ap_ST_st12_fsm_11 => 
                ap_NS_fsm <= ap_ST_st13_fsm_12;
            when ap_ST_st13_fsm_12 => 
                ap_NS_fsm <= ap_ST_st14_fsm_13;
            when ap_ST_st14_fsm_13 => 
                ap_NS_fsm <= ap_ST_st15_fsm_14;
            when ap_ST_st15_fsm_14 => 
                ap_NS_fsm <= ap_ST_st16_fsm_15;
            when ap_ST_st16_fsm_15 => 
                ap_NS_fsm <= ap_ST_st17_fsm_16;
            when ap_ST_st17_fsm_16 => 
                ap_NS_fsm <= ap_ST_st18_fsm_17;
            when ap_ST_st18_fsm_17 => 
                ap_NS_fsm <= ap_ST_st19_fsm_18;
            when ap_ST_st19_fsm_18 => 
                ap_NS_fsm <= ap_ST_st20_fsm_19;
            when ap_ST_st20_fsm_19 => 
                ap_NS_fsm <= ap_ST_st21_fsm_20;
            when ap_ST_st21_fsm_20 => 
                ap_NS_fsm <= ap_ST_st22_fsm_21;
            when ap_ST_st22_fsm_21 => 
                ap_NS_fsm <= ap_ST_st23_fsm_22;
            when ap_ST_st23_fsm_22 => 
                ap_NS_fsm <= ap_ST_st24_fsm_23;
            when ap_ST_st24_fsm_23 => 
                ap_NS_fsm <= ap_ST_st25_fsm_24;
            when ap_ST_st25_fsm_24 => 
                ap_NS_fsm <= ap_ST_st26_fsm_25;
            when ap_ST_st26_fsm_25 => 
                ap_NS_fsm <= ap_ST_st27_fsm_26;
            when ap_ST_st27_fsm_26 => 
                ap_NS_fsm <= ap_ST_st28_fsm_27;
            when ap_ST_st28_fsm_27 => 
                ap_NS_fsm <= ap_ST_st1_fsm_0;
            when others =>  
                ap_NS_fsm <= "XXXXXXXXXXXXXXXXXXXXXXXXXXXX";
        end case;
    end process;

    -- ap_done assign process. --
    ap_done_assign_proc : process(ap_done_reg, ap_sig_cseq_ST_st28_fsm_27)
    begin
        if (((ap_const_logic_1 = ap_done_reg) or (ap_const_logic_1 = ap_sig_cseq_ST_st28_fsm_27))) then 
            ap_done <= ap_const_logic_1;
        else 
            ap_done <= ap_const_logic_0;
        end if; 
    end process;


    -- ap_idle assign process. --
    ap_idle_assign_proc : process(ap_start, ap_sig_cseq_ST_st1_fsm_0)
    begin
        if ((not((ap_const_logic_1 = ap_start)) and (ap_const_logic_1 = ap_sig_cseq_ST_st1_fsm_0))) then 
            ap_idle <= ap_const_logic_1;
        else 
            ap_idle <= ap_const_logic_0;
        end if; 
    end process;


    -- ap_ready assign process. --
    ap_ready_assign_proc : process(ap_sig_cseq_ST_st28_fsm_27)
    begin
        if ((ap_const_logic_1 = ap_sig_cseq_ST_st28_fsm_27)) then 
            ap_ready <= ap_const_logic_1;
        else 
            ap_ready <= ap_const_logic_0;
        end if; 
    end process;


    -- ap_return assign process. --
    ap_return_assign_proc : process(grp_fu_13_p2, ap_sig_cseq_ST_st28_fsm_27, ap_return_preg)
    begin
        if ((ap_const_logic_1 = ap_sig_cseq_ST_st28_fsm_27)) then 
            ap_return <= grp_fu_13_p2;
        else 
            ap_return <= ap_return_preg;
        end if; 
    end process;


    -- ap_sig_bdd_258 assign process. --
    ap_sig_bdd_258_assign_proc : process(ap_CS_fsm)
    begin
                ap_sig_bdd_258 <= (ap_const_lv1_1 = ap_CS_fsm(27 downto 27));
    end process;


    -- ap_sig_bdd_47 assign process. --
    ap_sig_bdd_47_assign_proc : process(ap_CS_fsm)
    begin
                ap_sig_bdd_47 <= (ap_CS_fsm(0 downto 0) = ap_const_lv1_1);
    end process;


    -- ap_sig_bdd_61 assign process. --
    ap_sig_bdd_61_assign_proc : process(ap_start, ap_done_reg)
    begin
                ap_sig_bdd_61 <= ((ap_start = ap_const_logic_0) or (ap_done_reg = ap_const_logic_1));
    end process;


    -- ap_sig_cseq_ST_st1_fsm_0 assign process. --
    ap_sig_cseq_ST_st1_fsm_0_assign_proc : process(ap_sig_bdd_47)
    begin
        if (ap_sig_bdd_47) then 
            ap_sig_cseq_ST_st1_fsm_0 <= ap_const_logic_1;
        else 
            ap_sig_cseq_ST_st1_fsm_0 <= ap_const_logic_0;
        end if; 
    end process;


    -- ap_sig_cseq_ST_st28_fsm_27 assign process. --
    ap_sig_cseq_ST_st28_fsm_27_assign_proc : process(ap_sig_bdd_258)
    begin
        if (ap_sig_bdd_258) then 
            ap_sig_cseq_ST_st28_fsm_27 <= ap_const_logic_1;
        else 
            ap_sig_cseq_ST_st28_fsm_27 <= ap_const_logic_0;
        end if; 
    end process;


    -- grp_fu_13_ce assign process. --
    grp_fu_13_ce_assign_proc : process(ap_sig_cseq_ST_st1_fsm_0, ap_sig_bdd_61)
    begin
        if (((ap_const_logic_1 = ap_sig_cseq_ST_st1_fsm_0) and ap_sig_bdd_61)) then 
            grp_fu_13_ce <= ap_const_logic_0;
        else 
            grp_fu_13_ce <= ap_const_logic_1;
        end if; 
    end process;

    grp_fu_13_p0 <= ap_const_lv32_0;
    grp_fu_13_p1 <= p_read;
end behav;