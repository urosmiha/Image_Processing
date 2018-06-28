library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity main_filter is
port (
	clk				: in std_logic;
	enable			: in std_logic;
	window_in		: in std_logic_vector(199 downto 0);
	pixel_value		: out std_logic_vector(7 downto 0);
	wr_addr			: out std_logic_vector(7 downto 0);
	done				: out std_logic			-- Connect this to SRAM to indicate as write enable
														-- Also connect it to 7th (MSB) bit of control register to tell HPS that it can read stuff. 
);
end entity;

architecture beh of main_filter is
	
	---------- COMPONENTS ---------------------
	
	component sobel_filter is
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
	end component;
	
	component gauss_filter is
		port (
			clk			: in std_logic;
			enable		: in std_logic;
			reset			: in std_logic;
			g_window_in	: in std_logic_vector(199 downto 0);
			sel_kernel	: in std_logic_vector(3 downto 0);
			done			: out std_logic;
			g_window		: out std_logic_vector(71 downto 0)
		);
	end component;
	
	component address_generator is
		port (
			clk		: in std_logic;
			enable	: in std_logic;
			addr		: out std_logic_vector(7 downto 0)
		);
	end component;
	---------- COMPONENTS END ----------------------
	
	---------- SIGNALS -----------------
	
	-------- GAUSS / SOBEL relationship ---------
	signal gauss2sobel_enable : std_logic;
	signal gauss2sobel_window : std_logic_vector(71 downto 0);
	
	signal s_done : std_logic;
	
	-------- SOBEL / MAIN relationship ---------
	signal sobel_out_pixel : std_logic_vector(7 downto 0);
	
	---------- SIGNALS END -----------------
	
begin
	
	gauss: gauss_filter port map(
		clk			=> clk,
		enable		=> enable,
		reset			=> '0',						-- Keep resets OFF (for now)
		g_window_in	=> window_in,
		done			=> gauss2sobel_enable,
		sel_kernel 	=> "0001",					-- Use Gaussian Filter
		g_window		=> gauss2sobel_window
	);
	
	sobel: sobel_filter port map (
		clk				=> clk,
		enable			=> gauss2sobel_enable,
		reset				=> '0',						-- Keep resets OFF (for now)
		so_win_in		=> gauss2sobel_window,
		done				=> s_done,
		sel_kernel_x  	=> "0010",					-- Sel Sobel X
		sel_kernel_y 	=> "0011",					-- Sel Sobel Y
		pix_out			=> sobel_out_pixel
	);
	
	address_gen : address_generator port map (
		clk 	 => clk,
		enable => s_done,
		addr 	 => wr_addr
	);
	
	done <= s_done;
	
	pixel_value <= sobel_out_pixel;
	
end architecture;






