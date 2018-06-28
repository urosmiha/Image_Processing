LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity sobel_math is
port(
	clk 	 	: IN std_logic;
	enable	: IN std_logic;
	x		 	: IN std_logic_vector(7 downto 0);
	y		 	: IN std_logic_vector(7 downto 0);
	sqrt	 	: OUT std_logic_vector(8 downto 1);
	done		: OUT std_logic
);
end entity;

architecture beh of sobel_math is	

--	TYPE State_type IS (S1, S2);  -- Define the states
--	SIGNAL state : State_Type := S1;    -- Create a signal that uses 

begin 

	process(clk)
		variable	sqr_x : unsigned(15 downto 0) := (others=>'0');
		variable sqr_y : unsigned(15 downto 0) := (others=>'0');
		variable check : integer := 0;
	
		variable a : unsigned(15 downto 0):= (others => '0');   				  --original input.
		variable q : unsigned(7 downto 0):= (others => '0');  				  --result.
		variable vleft,vright,r : unsigned(9 downto 0) := (others => '0');  --input to adder/sub.r-remainder.
		variable i : integer := 0;
		
	begin

		if(rising_edge(clk)) then
			if(enable = '1') then
				sqr_x := unsigned(x) * unsigned(x);
				sqr_y := unsigned(y) * unsigned(y);
				
				-- Check if the value if more than 65025 - so we do not go above 255.
				check := to_integer(sqr_x) + to_integer(sqr_y);
				
				if(check > 65025) then -- sqrt(65025) = 255 so we cannot have number larger than 65025
					a := "1111111000000001";
				else 
					a := sqr_x + sqr_y;
				end if;
				
				-------- SQUARE ROOT OPERATION ---------
				vleft := (others => '0');
				vright := (others => '0');
				r := (others => '0');
				q := (others => '0');
				i := 0;

				for i in 0 to 7 loop
					vright(0) := '1';
					vright(1) := r(9);
					vright(9 downto 2) := q;
					vleft(1 downto 0) := a(15 downto 14);
					vleft(9 downto 2) := r(7 downto 0);
					a(15 downto 2) := a(13 downto 0);  --shifting by 2 bit.
					
					if ( r(9) = '1') then
						r := vleft + vright;
					else
						r := vleft - vright;
					end if;
					
					q(7 downto 1) := q(6 downto 0);
					q(0) := not r(9);
				end loop; 
				-----------------------
				done <= '1';
			else
				done <= '0';
			end if;
		end if;			
		
		sqrt <= std_logic_vector(q);
			
	end process;		
end architecture;  
