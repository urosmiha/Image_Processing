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

ENTITY main_filter_vhd_tst IS
END main_filter_vhd_tst;
ARCHITECTURE main_filter_arch OF main_filter_vhd_tst IS
-- constants                                                 
-- signals                                                   
	SIGNAL clk					: std_logic;
	SIGNAL enable				: std_logic;
	SIGNAL window_in 			: std_logic_vector(199 downto 0);
	SIGNAL pixel_value		: std_logic_vector(7 downto 0);
	SIGNAL done					: std_logic;
COMPONENT main_filter
	PORT (
		clk				: in std_logic;
		enable			: in std_logic;
		window_in 		: in std_logic_vector(199 downto 0);
		pixel_value		: out std_logic_vector(7 downto 0);
		done				: out std_logic
	);
END COMPONENT;
BEGIN
	i1 : main_filter
	PORT MAP (
	clk 				=> clk,
	enable			=> enable,
	window_in 		=> window_in,
	pixel_value		=> pixel_value,
	done				=> done
	);

		enable <= '1'; 
		--						Random values (exprected 9C)										Random values 2																	Obvious black to white edge - expect FF																																				
		window_in <= X"C8323C64C846505A326464645A5AC85A5A5AC8C8FFFF3C3C64", X"123456789ABCDEFEDCBA9876543210123456789ABCDEFEDCBA" after 50 ns, X"FFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000000" after 100 ns, X"05ABCDAB10AE05A1548956315849651509AE00AB010509AE00" after 150 ns;
	
Process
	Begin
	 clk  <= '0'  ;
	wait for 5 ns ;
-- 5 ns, single loop till start period.
	 clk  <= '1'  ;
	 wait for 5 ns ;
End Process;
	
END main_filter_arch;
