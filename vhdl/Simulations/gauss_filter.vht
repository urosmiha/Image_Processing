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
-- Generated on "05/07/2018 21:03:00"
                                                            
-- Vhdl Test Bench template for design  :  gauss_filter
-- 
-- Simulation tool : ModelSim-Altera (VHDL)
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all; 
use ieee.numeric_std.all;                               

ENTITY gauss_filter_vhd_tst IS
END gauss_filter_vhd_tst;
ARCHITECTURE gauss_filter_arch OF gauss_filter_vhd_tst IS
-- constants                                                 
-- signals                                                   
SIGNAL clk : STD_LOGIC;
SIGNAL done : std_logic;
SIGNAL enable : std_logic;
SIGNAL g_window : STD_LOGIC_VECTOR(71 DOWNTO 0);
SIGNAL reset : STD_LOGIC;
SIGNAL g_window_in : STD_LOGIC_VECTOR(199 DOWNTO 0);
SIGNAL sel_kernel	: std_logic_vector(3 downto 0);
COMPONENT gauss_filter
	PORT (
	clk			: in std_logic;
	enable		: in std_logic;
	reset			: in std_logic;
	g_window_in	: in std_logic_vector(199 downto 0);
	sel_kernel	: in std_logic_vector(3 downto 0);
	done			: out std_logic;
	g_window		: out std_logic_vector(71 downto 0)
	);
END COMPONENT;
BEGIN
	i1 : gauss_filter
	PORT MAP (
-- list connections between master ports and signals
	clk => clk,
	done => done,
	enable => enable,
	g_window => g_window,
	reset => reset,
	g_window_in => g_window_in,
	sel_kernel	=> sel_kernel
	);
	
-- Do: 				Gauss, Identity, 				Inversion, 				Scalling, 				Sharpen, 				Box Blur, 				Default.
	sel_kernel <= "0001", "0100" after 100 ns, "0101" after 200 ns, "0110" after 300 ns, "0111" after 400 ns, "1000" after 500 ns, "1111" after 600 ns;
	enable <= '0','1' after 50 ns;
	g_window_in <= X"C8323C64C846505A326464645A5AC85A5A5AC8C8FFFF3C3C64";
	
	
Process
	Begin
	 clk  <= '0'  ;
	wait for 5 ns ;
-- 5 ns, single loop till start period.
	 clk  <= '1'  ;
	 wait for 5 ns ;
End Process;                                         
END gauss_filter_arch;
