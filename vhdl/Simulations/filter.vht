-- Copyright (C) 1991-2013 Altera Corporation
-- Your use of Altera Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Altera Program License 
-- Subscription Agreement, Altera MegaCore Function License 
-- Agreement, or other applicable license agreement, including, 
-- without limitation, that your use is for the sole purpose of 
-- programming logic devices manufactured by Altera and sold by 
-- Altera or its authorized distributors.  Please refer to the 
-- applicable agreement for further details.

-- ***************************************************************************
-- This file contains a Vhdl test bench template that is freely editable to   
-- suit user's needs .Comments are provided in each section to help the user  
-- fill out necessary details.                                                
-- ***************************************************************************
-- Generated on "05/03/2018 14:43:03"
                                                            
-- Vhdl Test Bench template for design  :  filter
-- 
-- Simulation tool : ModelSim-Altera (VHDL)
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all; 
use ieee.numeric_std.all;                               

ENTITY filter_vhd_tst IS
END filter_vhd_tst;
ARCHITECTURE filter_arch OF filter_vhd_tst IS
-- constants                                                 
-- signals                                                   
	SIGNAL clk				:  std_logic;
	SIGNAL enable			:  std_logic;
	SIGNAL reset			:  std_logic;
	SIGNAL kernel			:  signed(35 downto 0);
	SIGNAL denominator	:  signed(4 downto 0);
	SIGNAL window			:  std_logic_vector(71 downto 0);
	SIGNAL done				:  std_logic;
	SIGNAL avg_out			:  std_logic_vector(7 downto 0);
COMPONENT filter
	PORT (
	clk			: in std_logic;
	enable		: in std_logic;
	reset			: in std_logic;
	kernel		: in signed(35 downto 0);
	denominator	: in signed(4 downto 0);
	window		: in std_logic_vector(71 downto 0);
	done			: out std_logic;
	avg_out		: out std_logic_vector(7 downto 0)
	);
END COMPONENT;
BEGIN
	i1 : filter
	PORT MAP (
	clk => clk,
	enable => enable,
	reset => reset,
	kernel => kernel,
	denominator => denominator,
	window => window,
	done => done,
	avg_out => avg_out
	);

		enable <= '1','0' after 20 ns,'1' after 30 ns,'0' after 45 ns,'1' after 65 ns,'0' after 75 ns,'1' after 105 ns,'0' after 115 ns;
--		kernel <= X"121242121";	-- [1,2,1,2,4,2,1,2,1] Gaussian Blur
		kernel <= X"10F20E10F", X"121000FEF" after 25 ns, X"121242121" after 45 ns ;	-- [1,0,-1,2,0,-2,1,0,-1] Sobel X
		--kernel <= X"121000FEF";	-- [1,2,1,0,0,0,-1,-2,-1] Sobel Y
--		denominator <= "10000";
		denominator <= "00001";
		
		window <= X"323C323232321E320A", X"563CA30A0AF4C8C801" after 85 ns,X"FFFFFFFFFFFFFFFFFF" after 100 ns,X"000000000000000000" after 115 ns;
	
Process
	Begin
	 clk  <= '0'  ;
	wait for 5 ns ;
-- 5 ns, single loop till start period.
	 clk  <= '1'  ;
	 wait for 5 ns ;
End Process;
	
END filter_arch;
