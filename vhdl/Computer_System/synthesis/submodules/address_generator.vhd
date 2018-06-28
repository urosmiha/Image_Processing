library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity address_generator is
port (
	clk		: in std_logic;
	enable	: in std_logic;
	addr		: out std_logic_vector(7 downto 0)
);
end entity;

architecture beh of address_generator is

	signal s_addr : unsigned(7 downto 0) := (others => '0');
begin
	process(clk)
	begin
		if(rising_edge(clk)) then
			if(enable = '1') then
			
				addr <= std_logic_vector(s_addr);
				
				if(s_addr > "11111110") then 	-- Check if it is over 4000-ish since max we can represent with 12 bits.
					s_addr <= (others => '0');			-- Start from the 0, assuming that HPS will read values well before we load new ones.
				else				
					s_addr <= s_addr + "00000001";		-- Add 1 since we are storing 8 bit values
				end if;
			end if;
		end if;
	end process;
end architecture;