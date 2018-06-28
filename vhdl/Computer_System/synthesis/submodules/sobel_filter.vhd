library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity sobel_filter is
port (
	clk				: in std_logic;
	enable			: in std_logic;
	reset				: in std_logic;
	so_win_in		: in std_logic_vector(71 downto 0);
	sel_kernel_y	: in std_logic_vector(3 downto 0);
	sel_kernel_x	: in std_logic_vector(3 downto 0);
	done				: out std_logic;
	pix_out			: out std_logic_vector(7 downto 0)
);
end entity;

architecture beh of sobel_filter is

--------- COMPONENTS ---------------
	component filter
		port (
			clk			: in std_logic;
			enable		: in std_logic;
			reset			: in std_logic;
			kernel		: in signed(35 downto 0);
			denominator	: in signed(4 downto 0);
			window		: in std_logic_vector(71 downto 0);
			done			: out std_logic;
			avg_out		: out std_logic_vector(7 downto 0)
		);
	end component;

	component kernel_select
		port (
			clk		: in std_logic;
			kernel	: out signed(36 downto 1);
			sel		: in std_logic_vector(3 downto 0);
			denom		: out signed(4 downto 0)
		);
	end component;
	
	component sobel_math is
		port(
			clk 	 	: IN std_logic;
			enable	: IN std_logic;
			x		 	: IN std_logic_vector(7 downto 0);
			y		 	: IN std_logic_vector(7 downto 0);
			sqrt	 	: OUT std_logic_vector(7 downto 0);
			done		: OUT std_logic
		);
	end component;
	
--------- COMPONENTS END ---------------

--------- SIGNALS ----------------

	signal s_gauss_filter: unsigned(7 downto 0);
	signal s_gauss_kernel: signed(35 downto 0); 
	signal s_gauss_denom : signed(4 downto 0);
	signal s_kernel_x    : signed(35 downto 0); 
	signal s_kernel_y    : signed(35 downto 0);
	signal s_sobel_denom : signed(4 downto 0);
	
	signal sX_done : std_logic := '0';
	signal sY_done : std_logic := '0';
	signal s_done	: std_logic := '0';
	
	signal sX_val	: std_logic_vector(7 downto 0);
	signal sY_val	: std_logic_vector(7 downto 0);
	
	signal s_filterX_kernel: signed(35 downto 0); 
	signal s_filterX_denom : signed(4 downto 0);
	
	signal s_filterY_kernel: signed(35 downto 0); 
	signal s_filterY_denom : signed(4 downto 0);

--------- SIGNALS END -----------

begin
	
	sobelX_kernel: kernel_select port map(
		clk 		   => clk,
		kernel	   => s_filterX_kernel,
		sel		   => sel_kernel_x,
		denom		   => s_filterX_denom
	);
	
	sobelY_kernel: kernel_select port map(
		clk 		   => clk,
		kernel	   => s_filterY_kernel,
		sel		   => sel_kernel_y,
		denom		   => s_filterY_denom
	);
	
	sobel_X: filter port map(
		clk 			=> clk,
		enable 		=> enable,
		reset 		=> reset,
		kernel 		=> s_filterX_kernel,
		denominator => s_filterX_denom,
		window 		=> so_win_in,
		done 			=> sX_done,
		avg_out 		=> sX_val
	);
	
	sobel_Y: filter port map(
		clk 			=> clk,
		enable 		=> enable,
		reset 		=> reset,
		kernel 		=> s_filterY_kernel,
		denominator => s_filterY_denom,
		window 		=> so_win_in,
		done 			=> sY_done,
		avg_out		=> sY_val
	);
	
	s_done <= sX_done and sY_done;
	
	sqrt_maths: sobel_math port map (
		clk 	 	=> clk,
		enable 	=> s_done,
		x		  	=> sX_val,
		y		  	=> sY_val,
		sqrt	  	=> pix_out,
		done	 	=> done
	);
	
end architecture;