library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity gauss_filter is
port (
	clk			: in std_logic;
	enable		: in std_logic;
	reset			: in std_logic;
	g_window_in	: in std_logic_vector(199 downto 0);
	sel_kernel	: in std_logic_vector(3 downto 0);
	done			: out std_logic;
	g_window		: out std_logic_vector(71 downto 0)
);
end entity;

architecture beh of gauss_filter is

---------------- SIGNALS ------------------------
	signal s_gauss_filter: unsigned(7 downto 0);
	
	signal s_filter_kernel: signed(35 downto 0); 
	signal s_filter_denom : signed(4 downto 0);
	
	signal s_window_0 : std_logic_vector(71 downto 0) := (others => '0');
	signal s_window_1 : std_logic_vector(71 downto 0) := (others => '0');
	signal s_window_2 : std_logic_vector(71 downto 0) := (others => '0');
	signal s_window_3 : std_logic_vector(71 downto 0) := (others => '0');
	signal s_window_4 : std_logic_vector(71 downto 0) := (others => '0');
	signal s_window_5 : std_logic_vector(71 downto 0) := (others => '0');
	signal s_window_6 : std_logic_vector(71 downto 0) := (others => '0');
	signal s_window_7 : std_logic_vector(71 downto 0) := (others => '0');
	signal s_window_8 : std_logic_vector(71 downto 0) := (others => '0');
	
	signal sg_win_0 : std_logic_vector(7 downto 0) := (others => '0');
	signal sg_win_1 : std_logic_vector(7 downto 0) := (others => '0');
	signal sg_win_2 : std_logic_vector(7 downto 0) := (others => '0');
	signal sg_win_3 : std_logic_vector(7 downto 0) := (others => '0');
	signal sg_win_4 : std_logic_vector(7 downto 0) := (others => '0');
	signal sg_win_5 : std_logic_vector(7 downto 0) := (others => '0');
	signal sg_win_6 : std_logic_vector(7 downto 0) := (others => '0');
	signal sg_win_7 : std_logic_vector(7 downto 0) := (others => '0');
	signal sg_win_8 : std_logic_vector(7 downto 0) := (others => '0');

	signal sDone_1 : std_logic;
	signal sDone_2 : std_logic;
	signal sDone_3 : std_logic;
	signal sDone_4 : std_logic;
	signal sDone_5 : std_logic;
	signal sDone_6 : std_logic;
	signal sDone_7 : std_logic;
	signal sDone_8 : std_logic;
	signal sDone_9 : std_logic;
	
	signal sDone : std_logic := '0';
	
------------- SIGNALS END ---------------
	
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
--------- COMPONENTS END ---------------
begin

	s_window_0 <= g_window_in(199 downto 176) & g_window_in(159 downto 136) & g_window_in(119 downto 96);
	s_window_1 <= g_window_in(191 downto 168) & g_window_in(151 downto 128) & g_window_in(111 downto 88);
	s_window_2 <= g_window_in(183 downto 160) & g_window_in(143 downto 120) & g_window_in(103 downto 80);
	s_window_3 <= g_window_in(159 downto 136) & g_window_in(119 downto 96) & g_window_in(79 downto 56);
	s_window_4 <= g_window_in(151 downto 128) & g_window_in(111 downto 88) & g_window_in(71 downto 48);
	s_window_5 <= g_window_in(143 downto 120) & g_window_in(103 downto 80) & g_window_in(63 downto 40);
	s_window_6 <= g_window_in(119 downto 96) & g_window_in(79 downto 56) & g_window_in(39 downto 16);
	s_window_7 <= g_window_in(111 downto 88) & g_window_in(71 downto 48) & g_window_in(31 downto 8);
	s_window_8 <= g_window_in(103 downto 80) & g_window_in(63 downto 40) & g_window_in(23 downto 0);

	gauss_kernel: kernel_select port map(
		clk 		   => clk,
		kernel	   => s_filter_kernel,
		sel		   => sel_kernel,
		denom		   => s_filter_denom
	);

	-- Gaussian 1
	gauss_1: filter port map(
		clk => clk,
		enable => enable,
		reset => reset,
		kernel => s_filter_kernel,
		denominator => s_filter_denom,
		window => s_window_0, --(s_window(199 downto 176) & s_window(159 downto 136) & s_window(119 downto 96)),
		done => sDone_1,
		avg_out => sg_win_0 --g_window(71 downto 64)	-- index 0
	);
	
		-- Gaussian 2
	gauss_2: filter port map(
		clk => clk,
		enable => enable,
		reset => reset,
		kernel => s_filter_kernel,
		denominator => s_filter_denom,
		window => s_window_1, --(g_window_in(191 downto 168) & g_window_in(151 downto 128) & g_window_in(111 downto 88)),
		done => sDone_2,
		avg_out => sg_win_1 --g_window(63 downto 56)	-- index 1
	);
	
		-- Gaussian 3
	gauss_3: filter port map(
		clk => clk,
		enable => enable,
		reset => reset,
		kernel => s_filter_kernel,
		denominator => s_filter_denom,
		window => s_window_2, --(g_window_in(183 downto 160) & g_window_in(143 downto 120) & g_window_in(103 downto 80)),
		done => sDone_3,
		avg_out => sg_win_2 --g_window(55 downto 48)	-- index 2
	);
	
		-- Gaussian 4
	gauss_4: filter port map(
		clk => clk,
		enable => enable,
		reset => reset,
		kernel => s_filter_kernel,
		denominator => s_filter_denom,
		window => s_window_3, --(g_window_in(159 downto 136) & g_window_in(119 downto 96) & g_window_in(79 downto 56)),
		done => sDone_4,
		avg_out => sg_win_3 --g_window(47 downto 40)	-- index 3
	);
	
		-- Gaussian 5
	gauss_5: filter port map(
		clk => clk,
		enable => enable,
		reset => reset,
		kernel => s_filter_kernel,
		denominator => s_filter_denom,
		window => s_window_4, --(g_window_in(151 downto 128) & g_window_in(111 downto 88) & g_window_in(71 downto 48)),
		done => sDone_5,
		avg_out => sg_win_4 --g_window(39 downto 32)	-- index 4
	);
	
		-- Gaussian 6
	gauss_6: filter port map(
		clk => clk,
		enable => enable,
		reset => reset,
		kernel => s_filter_kernel,
		denominator => s_filter_denom,
		window => s_window_5, --(g_window_in(143 downto 120) & g_window_in(103 downto 80) & g_window_in(63 downto 40)),
		done => sDone_6,
		avg_out => sg_win_5 --g_window(31 downto 24)	-- index 5
	);
	
		-- Gaussian 7
	gauss_7: filter port map(
		clk => clk,
		enable => enable,
		reset => reset,
		kernel => s_filter_kernel,
		denominator => s_filter_denom,
		window => s_window_6, --(g_window_in(119 downto 96) & g_window_in(79 downto 56) & g_window_in(39 downto 16)),
		done => sDone_7,
		avg_out => sg_win_6 --g_window(23 downto 16)	-- index 6
	);
	
		-- Gaussian 8
	gauss_8: filter port map(
		clk => clk,
		enable => enable,
		reset => reset,
		kernel => s_filter_kernel,
		denominator => s_filter_denom,
		window => s_window_7, --(g_window_in(111 downto 88) & g_window_in(71 downto 48) & g_window_in(31 downto 8)),
		done => sDone_8,
		avg_out => sg_win_7 --g_window(15 downto 8)	-- index 7
	);
	
		-- Gaussian 9
	gauss_9: filter port map(
		clk => clk,
		enable => enable,
		reset => reset,
		kernel => s_filter_kernel,
		denominator => s_filter_denom,
		window => s_window_8, --(g_window_in(103 downto 80) & g_window_in(63 downto 40) & g_window_in(23 downto 0)),
		done => sDone_9,
		avg_out => sg_win_8 --g_window(7 downto 0)	-- index 8
	);
	
	g_window <= sg_win_0 & sg_win_1 & sg_win_2 & sg_win_3 & sg_win_4 & sg_win_5 & sg_win_6 & sg_win_7 & sg_win_8;
	sDone <= sDone_1 AND sDone_2 AND sDone_3 AND sDone_4 AND sDone_5 AND sDone_6 AND sDone_7 AND sDone_8 AND sDone_9;
	done <= sDone;
end architecture;