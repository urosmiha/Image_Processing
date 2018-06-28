library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity filter is
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
end entity;

architecture beh of filter is

	signal lower_limit : signed(17 downto 0) := (others => '0');		-- 0
	signal upper_limit : signed(17 downto 0) := "000000000011111111";	-- 255

begin

	process(clk)

		variable m1 : signed(17 downto 0) := (others => '0');
		variable m2 : signed(17 downto 0) := (others => '0');
		variable m3 : signed(17 downto 0) := (others => '0');
		variable m4 : signed(17 downto 0) := (others => '0');
		variable m5 : signed(17 downto 0) := (others => '0');
		variable m6 : signed(17 downto 0) := (others => '0');
		variable m7 : signed(17 downto 0) := (others => '0');
		variable m8 : signed(17 downto 0) := (others => '0');
		variable m9 : signed(17 downto 0) := (others => '0');
		
		variable w1 : signed(8 downto 0);
		variable w2 : signed(8 downto 0);
		variable w3 : signed(8 downto 0);
		variable w4 : signed(8 downto 0);
		variable w5 : signed(8 downto 0);
		variable w6 : signed(8 downto 0);
		variable w7 : signed(8 downto 0);
		variable w8 : signed(8 downto 0);
		variable w9 : signed(8 downto 0);
		
		variable k1 : signed(8 downto 0);
		variable k2 : signed(8 downto 0);
		variable k3 : signed(8 downto 0);
		variable k4 : signed(8 downto 0);
		variable k5 : signed(8 downto 0);
		variable k6 : signed(8 downto 0);
		variable k7 : signed(8 downto 0);
		variable k8 : signed(8 downto 0);
		variable k9 : signed(8 downto 0);
		
		variable sum : signed(17 downto 0) := (others => '0');
		variable avg : signed(17 downto 0) := (others => '0');

	begin

		if(rising_edge(clk)) then
			if(enable = '1') then
				w1 := '0' & signed(window(71 downto 64));
				w2 := '0' & signed(window(63 downto 56));
				w3 := '0' & signed(window(55 downto 48));
				w4 := '0' & signed(window(47 downto 40));
				w5 := '0' & signed(window(39 downto 32));
				w6 := '0' & signed(window(31 downto 24));
				w7 := '0' & signed(window(23 downto 16));
				w8 := '0' & signed(window(15 downto 8));
				w9 := '0' & signed(window(7 downto 0));
				
				k1 := kernel(35) & kernel(35) & kernel(35) & kernel(35) & kernel(35) & kernel(35 downto 32);
				k2 := kernel(31) & kernel(31) & kernel(31) & kernel(31) & kernel(31) & kernel(31 downto 28);
				k3 := kernel(27) & kernel(27) & kernel(27) & kernel(27) & kernel(27) & kernel(27 downto 24);
				k4 := kernel(23) & kernel(23) & kernel(23) & kernel(23) & kernel(23) & kernel(23 downto 20);
				k5 := kernel(19) & kernel(19) & kernel(19) & kernel(19) & kernel(19) & kernel(19 downto 16);
				k6 := kernel(15) & kernel(15) & kernel(15) & kernel(15) & kernel(15) & kernel(15 downto 12);
				k7 := kernel(11) & kernel(11) & kernel(11) & kernel(11) & kernel(11) & kernel(11 downto 8);
				k8 := kernel(7) & kernel(7) & kernel(7) & kernel(7) & kernel(7) & kernel(7 downto 4);
				k9 := kernel(3) & kernel(3) & kernel(3) & kernel(3) & kernel(3) & kernel(3 downto 0);		

				m1 := k1 * w1;
				m2 := k2 * w2;
				m3 := k3 * w3;
				m4 := k4 * w4;
				m5 := k5 * w5;
				m6 := k6 * w6;
				m7 := k7 * w7;
				m8 := k8 * w8;
				m9 := k9 * w9;
			
				sum := m1 + m2 + m3 + m4 + m5 + m6 + m7 + m8 + m9;				
				
				avg := abs(sum / ("0000000000000" & denominator));
				
				if(avg > upper_limit) then	
					avg := upper_limit;
				end if;
				
				avg_out <= std_logic_vector(avg(7 downto 0));
				
				done <= '1';
			else
				done <= '0';
			end if;
		end if;
	end process;
end architecture;