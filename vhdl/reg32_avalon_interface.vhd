LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.numeric_std.all;

ENTITY reg32_avalon_interface IS
PORT ( clock, resetn : IN STD_LOGIC;
	read, write, chipselect : IN STD_LOGIC;
	writedata : IN STD_LOGIC_VECTOR(63 DOWNTO 0);
	byteenable : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
	readdata : OUT STD_LOGIC_VECTOR(63 DOWNTO 0);
	Q_export : OUT STD_LOGIC_VECTOR(63 DOWNTO 0) );
END reg32_avalon_interface;

-- PACKET STRUCTURES:
-- writedata(63 downto 0)
--  _______________________________________________________________________________
-- |63       DATA       24|23  WR_ADDR  16|15  RD_ADDR  8|7  SEL_SRAM  3|2  CTRL  0|
-- |______________________|_______________|______________|______________|__________|
-- 
-- readdata(63 downto 0)
--  _______________________________________________________________________________
-- |63  DATA  56|                           _                           |2  CTRL  0|
-- |____________|_______________________________________________________|__________|

ARCHITECTURE Structure OF reg32_avalon_interface IS

	component Main_Contoller is
	port (
		clk 				: IN std_logic;
		sram_1			: IN std_logic_vector(39 downto 0);
		sram_2			: IN std_logic_vector(39 downto 0);
		sram_3 			: IN std_logic_vector(39 downto 0);
		sram_4			: IN std_logic_vector(39 downto 0);
		sram_5			: IN std_logic_vector(39 downto 0);
		main_ctrl_in	: IN std_logic_vector(2 downto 0);
		sram_addr 		: OUT std_logic_vector(7 downto 0);
		window_out 		: OUT std_logic_vector(199 downto 0);
		main_ctrl_out 	: OUT std_logic_vector(1 downto 0); 
		enable_filter	: OUT std_logic
	);
	end component;
	
	component main_filter is
	port (
		clk			: in std_logic;
		enable		: in std_logic;
		window_in	: in std_logic_vector(199 downto 0);
		pixel_value	: out std_logic_vector(7 downto 0);
		wr_addr		: out std_logic_vector(7 downto 0);
		done			: out std_logic	
	);
	end component;
	
	component sram_2_port is
	port (
		clock		 : IN STD_LOGIC  := '1';
		data		 : IN STD_LOGIC_VECTOR (39 DOWNTO 0);
		rdaddress : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
		wraddress : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
		wren		 : IN STD_LOGIC  := '0';
		q			 : OUT STD_LOGIC_VECTOR (39 DOWNTO 0)
	);
	end component;
	
	component sram_pixel_port is
	PORT
	(
		clock		 : IN STD_LOGIC  := '1';
		data		 : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
		rdaddress : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
		wraddress : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
		wren		 : IN STD_LOGIC  := '0';
		q			 : OUT STD_LOGIC_VECTOR (7 DOWNTO 0)
	);
	end component;

	signal s_sram1_out : std_logic_vector(39 downto 0) := (others => '0');	-- Go from SRAM blocks to Main Controller
	signal s_sram2_out : std_logic_vector(39 downto 0) := (others => '0');
	signal s_sram3_out : std_logic_vector(39 downto 0) := (others => '0');
	signal s_sram4_out : std_logic_vector(39 downto 0) := (others => '0');
	signal s_sram5_out : std_logic_vector(39 downto 0) := (others => '0');
	signal s_sram_addr : std_logic_vector(7 downto 0) := (others => '0');	-- Common address for sram 1-5
	
	signal s_writedata_in : STD_LOGIC_VECTOR(63 DOWNTO 0) := (others => '0');
	
	signal s_pixel_value : std_logic_vector(7 downto 0) := (others => '0'); 	-- Filtered pixel value, goes to pixel sram
	signal s_pixel_out   : std_logic_vector(7 downto 0) := (others => '0'); 	-- Output of pixel sram
	
	signal s_main_ctrl_out	: std_logic_vector(1 downto 0) := (others => '0');		-- Control from Main, needs to be concantinated with main_filterdone signal
	signal s_window			: std_logic_vector(199 downto 0) := (others => '0'); 	-- window that goes from the Main to the filter_select_sig
	signal s_window_hard		: std_logic_vector(199 downto 0) := X"C8323C64C846505A326464645A5AC85A5A5AC8C8FFFF3C3C64"; 	-- window that goes from the Main to the filter_select_sig

	signal s_enable_filter  : std_logic := '0'; 									-- goes from Main to filter - enables filter
	signal s_filter_done		: std_logic := '0'; 									-- indicats the filter has finished - add to the control to indicate to HPS to read the value.
	signal s_pixel_wr_addr  : std_logic_vector(7 downto 0) := (others => '0'); 		-- Indicates where in pixel SRAM to write the value.

	BEGIN
	s_writedata_in <= writedata;

	row1: component sram_2_port port map(
		clock 	 => clock,
		data		 => writedata(63 downto 24),
		rdaddress => s_sram_addr,
		wraddress => writedata(23 downto 16),
		wren	    => writedata(7),
		q			 => s_sram1_out	
	);
		
	row2: component sram_2_port port map(
		clock 	 => clock,
		data		 => writedata(63 downto 24),
		rdaddress => s_sram_addr,
		wraddress => writedata(23 downto 16),
		wren		 => writedata(6),
		q			 => s_sram2_out	
	);
		
	row3: component sram_2_port port map(
		clock 	 => clock,
		data		 => writedata(63 downto 24),
		rdaddress => s_sram_addr,
		wraddress => writedata(23 downto 16),
		wren		 => writedata(5),
		q			 => s_sram3_out	
	);
		
	row4: component sram_2_port port map(
		clock 	 => clock,
		data		 => writedata(63 downto 24),
		rdaddress => s_sram_addr,
		wraddress => writedata(23 downto 16),
		wren		 => writedata(4),
		q			 => s_sram4_out	
	);
		
	row5: component sram_2_port port map(
		clock 	 => clock,
		data		 => writedata(63 downto 24),
		rdaddress => s_sram_addr,
		wraddress => writedata(23 downto 16),
		wren		 => writedata(3),
		q			 => s_sram5_out
	);

	main: component Main_Contoller port map(
		clk 			  => clock,
		sram_1		  => s_sram1_out,
		sram_2		  => s_sram2_out,
		sram_3 		  => s_sram3_out,
		sram_4		  => s_sram4_out,
		sram_5		  => s_sram5_out,
		main_ctrl_in  => writedata(2 downto 0),
		sram_addr 	  => s_sram_addr,
		window_out 	  => s_window,
		main_ctrl_out => s_main_ctrl_out,
		enable_filter => s_enable_filter			
	);
	
	filter: component main_filter port map(
		clk 			=> clock,
		enable		=> s_enable_filter,
		window_in	=> s_window, --put hardcoded window here
		pixel_value => s_pixel_value,
		wr_addr		=> s_pixel_wr_addr,
		done			=> s_filter_done	
	);
	
		
	filtered_pixel: component sram_pixel_port port map(
		clock		 => clock,
		data		 => s_pixel_value,
		rdaddress => writedata(15 downto 8),
		wraddress => s_pixel_wr_addr,
		wren		 => s_filter_done,
		q			 => s_pixel_out
	);
	
	--readdata <= s_pixel_out & "00000000000000000000000000000000000000000000000000000" & s_main_ctrl_out & s_filter_done; -- 53 zeros
	process(clock)
	begin
		if(rising_edge(clock)) then
			if(read = '1') then
				readdata <= s_pixel_out & "00000000000000000000000000000000000000000000000000000" & s_main_ctrl_out & s_filter_done; -- 53 zeros	
			end if;
		end if;
	end process;
	
END Structure;

