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
-- Generated on "05/04/2018 11:46:14"
                                                            
-- Vhdl Test Bench template for design  :  sobel_math
-- 
-- Simulation tool : ModelSim-Altera (VHDL)
-- 

LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.numeric_std.all;                                

ENTITY sobel_math_vhd_tst IS
END sobel_math_vhd_tst;
ARCHITECTURE sobel_math_arch OF sobel_math_vhd_tst IS
-- constants                                                 
-- signals 
SIGNAL clk : std_logic; 
 SIGNAL     enable	: std_logic; 
SIGNAL done		:  std_logic ;
SIGNAL sqrt : std_logic_vector(8 downto 1);
SIGNAL x : std_logic_vector(7 downto 0);
SIGNAL y : std_logic_vector(7 downto 0);
COMPONENT sobel_math
	PORT (
	clk 	 	: IN std_logic;
	enable	: IN std_logic;
	x		 	: IN std_logic_vector(7 downto 0);
	y		 	: IN std_logic_vector(7 downto 0);
	sqrt	 	: OUT std_logic_vector(8 downto 1);
	done		: OUT std_logic
	);
END COMPONENT;
BEGIN
	i1 : sobel_math
	PORT MAP (
-- list connections between master ports and signals
	clk => clk,
	sqrt => sqrt,
	x => x,
	y => y,
	done => done,
	enable => enable
	);
-- Result: 5	  222				246s
	x <= X"04", X"7A" after 20 ns, X"F5" after 40 ns;
	y <= X"03", X"BA" after 20 ns, X"1A" after 40 ns;
	enable <= '1';
	Process
	Begin
	 clk  <= '0'  ;
	wait for 5 ns ;
-- 5 ns, single loop till start period.
	 clk  <= '1'  ;
	 wait for 5 ns ;
End Process;
	
END sobel_math_arch;
