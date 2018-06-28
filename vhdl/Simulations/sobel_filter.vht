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
-- Generated on "05/08/2018 21:00:23"
                                                            
-- Vhdl Test Bench template for design  :  sobel_filter
-- 
-- Simulation tool : ModelSim-Altera (VHDL)
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY sobel_filter_vhd_tst IS
END sobel_filter_vhd_tst;
ARCHITECTURE sobel_filter_arch OF sobel_filter_vhd_tst IS
-- constants                                                 
-- signals                                                   
	SIGNAL clk				: std_logic;
	SIGNAL enable			: std_logic;
	SIGNAL reset			: std_logic;
	SIGNAL so_win_in		: std_logic_vector(71 downto 0);
	SIGNAL sel_kernel_y	: std_logic_vector(3 downto 0);
	SIGNAL sel_kernel_x	: std_logic_vector(3 downto 0);
	SIGNAL done				: std_logic;
	SIGNAL pix_out			: std_logic_vector(7 downto 0);
COMPONENT sobel_filter
	PORT (
	clk				: in std_logic;
	enable			: in std_logic;
	reset				: in std_logic;
	so_win_in		: in std_logic_vector(71 downto 0);
	sel_kernel_y	: in std_logic_vector(3 downto 0);
	sel_kernel_x	: in std_logic_vector(3 downto 0);
	done				: out std_logic;
	pix_out			: out std_logic_vector(7 downto 0)
	);
END COMPONENT;
BEGIN
	i1 : sobel_filter
	PORT MAP (
-- list connections between master ports and signals
	clk				=> clk,
	enable			=> enable,
	reset				=> reset,
	so_win_in		=> so_win_in,
	sel_kernel_y  	=> sel_kernel_y,
	sel_kernel_x  	=> sel_kernel_x,
	done				=> done,
	pix_out			=> pix_out
	);
	
	enable 		<= '0','1' after 50 ns,'0' after 200 ns,'1' after 250 ns;
	sel_kernel_x <= "0010";
	sel_kernel_y <= "0011";					 
	so_win_in 	<= X"564E5E5B5F78786D85",X"FFFFFFFFFFFFFFFFFF" after 150 ns,X"123456789ABCDEFEDC" after 200 ns;
	
Process
	Begin
	 clk  <= '0'  ;
	wait for 5 ns ;
-- 5 ns, single loop till start period.
	 clk  <= '1'  ;
	 wait for 5 ns ;
End Process;                                           
END sobel_filter_arch;
