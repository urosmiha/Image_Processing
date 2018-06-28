LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- *** CURRENTLY, THIS IS ONLY CONNECTING THE SOBEL FILTER FOR TESTING PURPOSES. REMAINING SIGNALS AND COMPONENTS HAVE BEEN LEFT FOR LATER ***

-- Top level enitity to connect Sobel and Gaussian filters (3 filter blocks)
-- One kernel selector, which holds all supported kernels
-- Sobel math block for the two Sobel filter blocks (x and y)

entity filter_map is
	port (
		clk		  : in std_logic;
		control_in : in std_logic_vector(7 downto 0);
		img_window : in signed(72 downto 1);
		pixel_out  : out unsigned(8 downto 1);
		control_out: out std_logic_vector(7 downto 0)
	);
end entity;

-- Components
architecture structure of filter_map is
	component filter
		port (
			clk			: in std_logic;
			filter_en	: in std_logic;
			math_done_in: in std_logic_vector(1 downto 0);
			kernel		: in signed(36 downto 1);
			denominator	: in signed(5 downto 0);
			window		: in signed(72 downto 1);
			filter_done	: out std_logic;
			avg_out		: out unsigned(8 downto 1)
		);
	end component;

	component kernel_select
		port (
			clk			: in std_logic;
			sobel_x_out	: out signed(36 downto 1);
			sobel_y_out	: out signed(36 downto 1);
			sobel_denom	: out signed(5 downto 0);
			gauss_out	: out signed(36 downto 1);
			gauss_denom	: out signed(5 downto 0)
		);
	end component;

	component sobel_math
		port (
			clk 	 	: IN std_logic;
			math_en	: IN std_logic;
			x		 	: IN unsigned(8 downto 1);
			y		 	: IN unsigned(8 downto 1);
			sqrt	 	: OUT unsigned(8 downto 1);
			math_done: OUT std_logic_vector(7 downto 0)
		);
	end component;

-- Internal connections
signal s_clk         : std_logic;

-- For Gaussian filter
signal s_gauss_filter: unsigned(8 downto 1);
signal s_gauss_kernel: signed(36 downto 1); 
signal s_gauss_denom : signed(5 downto 0);

-- For Sobel filter
signal s_filter_x    : unsigned(8 downto 1);
signal s_filter_y    : unsigned(8 downto 1);
signal s_kernel_x    : signed(36 downto 1); 
signal s_kernel_y    : signed(36 downto 1);
signal s_sobel_denom : signed(5 downto 0);
signal s_math_x		: unsigned(8 downto 1);
signal s_math_y		: unsigned(8 downto 1);
signal s_sobel_done_x: std_logic;
signal s_sobel_done_y: std_logic;
signal s_math_done	: std_logic_vector(7 downto 0);
signal math_enable_signal:std_logic;

begin
	-- Kernel selector connections *** GAUSSIAN CURRENTLY UNUSED ***
	kernel: kernel_select port map(
		clk 		   => clk,
		sobel_x_out => s_kernel_x,
		sobel_y_out => s_kernel_y,
		sobel_denom => s_sobel_denom,
		gauss_out	=> s_gauss_kernel,
		gauss_denom => s_gauss_denom
	);
	
	-- Gaussian filter connections
--	gauss_filter: filter port map(
--		clk			=> s_clk,
--		kernel		=> s_gauss_kernel,
--		denominator	=> s_gauss_denom,
--		window		=> img_window,
--		avg_out		=> ...
--	);
	
	-- Sobel x filter connections
	sobel_x: filter  port map(
		clk			 => clk,
		kernel		 => s_kernel_x,
		filter_en	 => control_in(0),
		math_done_in => s_math_done(1 downto 0),
		denominator	 => s_sobel_denom,
		window		 => img_window, -- *** LATER THIS WILL COME FROM THE GAUSSIAN FILTER ***
		avg_out		 => s_math_x,
		filter_done  => s_sobel_done_x
	);
	
	-- Sobel y filter connections
	sobel_y: filter  port map(
		clk			 => clk,
		kernel		 => s_kernel_y,
		filter_en	 => '1',
		math_done_in => s_math_done(1 downto 0),
		denominator	 => s_sobel_denom,
		window		 => img_window, -- *** LATER THIS WILL COME FROM THE GAUSSIAN FILTER ***
		avg_out		 => s_math_y,
		filter_done  => s_sobel_done_y
	);
	
	-- Sobel math block connections
	math_map: sobel_math port map(
		math_en	 => math_enable_signal,
		clk 		 => clk,
		x			 => s_math_x,
		y			 => s_math_y,
		sqrt		 => pixel_out,
		math_done => s_math_done
	);
	
	control_out <= s_math_done;
	math_enable_signal <= s_sobel_done_x and s_sobel_done_y;

end architecture;