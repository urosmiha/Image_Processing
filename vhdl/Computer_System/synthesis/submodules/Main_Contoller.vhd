LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Main_Contoller is
port (
	clk 				: IN std_logic;
	sram_1			: IN std_logic_vector(39 downto 0);
	sram_2			: IN std_logic_vector(39 downto 0);
	sram_3 			: IN std_logic_vector(39 downto 0);
	sram_4			: IN std_logic_vector(39 downto 0);
	sram_5			: IN std_logic_vector(39 downto 0);
	main_ctrl_in	: IN std_logic_vector(2 downto 0);
	sram_addr 		: OUT std_logic_vector(7 downto 0) := (others => '0');
	window_out 		: OUT std_logic_vector(199 downto 0);
	main_ctrl_out 	: OUT std_logic_vector(1 downto 0); 
	enable_filter	: OUT std_logic
);
end entity;


architecture beh of Main_Contoller is
	
	TYPE State_type IS (init, start, run);  -- Define the states
	SIGNAL state : State_Type := init;    -- Create a signal that uses 

	
begin

	process(clk)
	
		variable img_row_1 : std_logic_vector(39 downto 0) := (others => '0');
		variable img_row_2 : std_logic_vector(39 downto 0) := (others => '0');
		variable img_row_3 : std_logic_vector(39 downto 0) := (others => '0');
		variable img_row_4 : std_logic_vector(39 downto 0) := (others => '0');
		variable img_row_5 : std_logic_vector(39 downto 0) := (others => '0');
	
		variable win_row_1 : std_logic_vector(39 downto 0) := (others => '0');
		variable win_row_2 : std_logic_vector(39 downto 0) := (others => '0');
		variable win_row_3 : std_logic_vector(39 downto 0) := (others => '0');
		variable win_row_4 : std_logic_vector(39 downto 0) := (others => '0');
		variable win_row_5 : std_logic_vector(39 downto 0) := (others => '0');
		
		variable s_window : std_logic_vector(199 downto 0) := (others => '0');
	
		variable sram_pixel_count : integer := 1;
		variable global_count : integer := 0;
		variable map_ratio	 : integer := 1;
		
		variable v_sram_addr  : unsigned(7 downto 0) := (others => '0');
		
		variable v_enable_filter : std_logic := '0';
		
		variable enable : std_logic := '0';
	
	begin
		if(rising_edge(clk)) then
			if(main_ctrl_in = "011") then
				enable := '1';
--				main_ctrl_out <= "11";
			end if;
			
							
			if(global_count > 632) then			-- 2 itterations before the end of the row
			
				main_ctrl_out <= "10"; 			-- 2 = Tell HPS to start sending new row
			
			end if;
			
			if(enable = '1') then
				
				if(global_count > 635) then		-- End of the row
					
					state <= init;							-- Start from the intial state
					
--					v_enable_filter := '0';
					
					global_count := 0;					
					
					v_sram_addr := (others => '0');	-- Reset address to we do not read the wrong value
					
					main_ctrl_out 	<= "00"; 			-- Set contol out to 0 so HPS does not send new row until FPGA is ready.
					
					if(map_ratio > 4) then				-- Map ratio should update only when we reach the end of the row.
						map_ratio := 1;			
					else
						map_ratio := map_ratio + 1;	
					end if;
					
				end if;

			
			------- ROW ASSIGNMENT -------
			
			-- Maps the right row to the right SRAM memory --
			
				case map_ratio is
					when 1 =>
						img_row_1 := sram_1;
						img_row_2 := sram_2;
						img_row_3 := sram_3;
						img_row_4 := sram_4;
						img_row_5 := sram_5;
					when 2 =>
						img_row_1 := sram_2;
						img_row_2 := sram_3;
						img_row_3 := sram_4;
						img_row_4 := sram_5;
						img_row_5 := sram_1;
					when 3 =>
						img_row_1 := sram_3;
						img_row_2 := sram_4;
						img_row_3 := sram_5;
						img_row_4 := sram_1;
						img_row_5 := sram_2;
					when 4 =>
						img_row_1 := sram_4;
						img_row_2 := sram_5;
						img_row_3 := sram_1;
						img_row_4 := sram_2;
						img_row_5 := sram_3;
					when 5 =>
						img_row_1 := sram_5;
						img_row_2 := sram_1;
						img_row_3 := sram_2;
						img_row_4 := sram_3;
						img_row_5 := sram_4;
					when others =>
				end case;
				
			-------- END ROW ASSIGNMENT -------------
			
			-------- MAIN FSM --------
			
			-- Defines what outputed window looks like --
			
				case state is
					when init =>
						win_row_1(39 downto 0) := img_row_1;
						win_row_2(39 downto 0) := img_row_2;
						win_row_3(39 downto 0) := img_row_3;
						win_row_4(39 downto 0) := img_row_4;
						win_row_5(39 downto 0) := img_row_5;
						
						state <= run;
						
						sram_pixel_count := sram_pixel_count + 1;			-- Increment the pixel count so we access the next pixel in the memory address.
						v_enable_filter := '1';									-- Start the filtering
						v_sram_addr := v_sram_addr + "00000001";	-- Add 32 to address so we access the next row
						sram_addr <= std_logic_vector(v_sram_addr);
						
					when start =>
					
--						win_row_1(7 downto 0) := img_row_1(31 downto 24);
--						win_row_2(7 downto 0) := img_row_2(31 downto 24);
--						win_row_3(7 downto 0) := img_row_3(31 downto 24);
--						win_row_4(7 downto 0) := img_row_4(31 downto 24);
--						win_row_5(7 downto 0) := img_row_5(31 downto 24);
						
--						sram_pixel_count := sram_pixel_count + 1;		-- Increment the pixel count so we access the next pixel in the memory address.
--						v_enable_filter := '1';								-- Start the filtering
--						
--						state <= run;	-- Go to running state
					
				----- Column tranversal ------
					
					when run =>
					
						------ SHIFT ALL THE PIXELS TO THE RIGHT BEFORE INSERTING THE NEW PIXEL ----
						win_row_1(39 downto 32) := win_row_1(31 downto 24);
						win_row_1(31 downto 24) := win_row_1(23 downto 16);
						win_row_1(23 downto 16) := win_row_1(15 downto 8);
						win_row_1(15 downto 8) := win_row_1(7 downto 0);
						
						win_row_2(39 downto 32) := win_row_2(31 downto 24);
						win_row_2(31 downto 24) := win_row_2(23 downto 16);
						win_row_2(23 downto 16) := win_row_2(15 downto 8);
						win_row_2(15 downto 8) := win_row_2(7 downto 0);
						
						win_row_3(39 downto 32) := win_row_3(31 downto 24);
						win_row_3(31 downto 24) := win_row_3(23 downto 16);
						win_row_3(23 downto 16) := win_row_3(15 downto 8);
						win_row_3(15 downto 8) := win_row_3(7 downto 0);
						
						win_row_4(39 downto 32) := win_row_4(31 downto 24);
						win_row_4(31 downto 24) := win_row_4(23 downto 16);
						win_row_4(23 downto 16) := win_row_4(15 downto 8);
						win_row_5(15 downto 8) := win_row_4(7 downto 0);
						
						win_row_5(39 downto 32) := win_row_5(31 downto 24);
						win_row_5(31 downto 24) := win_row_5(23 downto 16);
						win_row_5(23 downto 16) := win_row_5(15 downto 8);
						win_row_5(15 downto 8) := win_row_5(7 downto 0);
						
						------------------------------------------------------------
						
						------ INSERT NEW PIXEL AT THE END OF THE ROW ------
					
						-- SRAM Row -> | 	   1    |     2    |    3    	|  	 4  |    5   |
						-- SRAM Row -> | (40..32) | (31..24) | (23..16) | (15..8) | (7..0) |
					
						case sram_pixel_count is  		
							when 1 =>
								win_row_1(7 downto 0) := img_row_1(39 downto 32);
								win_row_2(7 downto 0) := img_row_2(39 downto 32);
								win_row_3(7 downto 0) := img_row_3(39 downto 32);
								win_row_4(7 downto 0) := img_row_4(39 downto 32);
								win_row_5(7 downto 0) := img_row_5(39 downto 32);
							when 2 =>															-- SRAM pixel Row -> | (31..24) | X | X | X |
								win_row_1(7 downto 0) := img_row_1(31 downto 24);
								win_row_2(7 downto 0) := img_row_2(31 downto 24);
								win_row_3(7 downto 0) := img_row_3(31 downto 24);
								win_row_4(7 downto 0) := img_row_4(31 downto 24);
								win_row_5(7 downto 0) := img_row_5(31 downto 24);
							when 3 =>															-- SRAM pixel Row -> | X | (23..16) | X | X |
								win_row_1(7 downto 0) := img_row_1(23 downto 16);
								win_row_2(7 downto 0) := img_row_2(23 downto 16);
								win_row_3(7 downto 0) := img_row_3(23 downto 16);
								win_row_4(7 downto 0) := img_row_4(23 downto 16);
								win_row_5(7 downto 0) := img_row_5(23 downto 16);
							when 4 =>															-- SRAM pixel Row -> | X | X | (15..8) | X |
								win_row_1(7 downto 0) := img_row_1(15 downto 8);
								win_row_2(7 downto 0) := img_row_2(15 downto 8);
								win_row_3(7 downto 0) := img_row_3(15 downto 8);
								win_row_4(7 downto 0) := img_row_4(15 downto 8);
								win_row_5(7 downto 0) := img_row_5(15 downto 8);
							when 5 =>															-- SRAM pixel Row -> | X | X | X | (7..0) |
								win_row_1(7 downto 0) := img_row_1(7 downto 0);
								win_row_2(7 downto 0) := img_row_2(7 downto 0);
								win_row_3(7 downto 0) := img_row_3(7 downto 0);
								win_row_4(7 downto 0) := img_row_4(7 downto 0);
								win_row_5(7 downto 0) := img_row_5(7 downto 0);
								
							when others =>						
						end case;
					
						------------------------------------------------------------
						
						------ Count Manager ------
						
						if(sram_pixel_count > 4) then								-- If we get to the end of the sram column set it to 1 again and go to the next row of the sram memory.
							sram_pixel_count := 1;
							v_sram_addr := v_sram_addr + "00000001";	-- Add 32 to address so we access the next row
							sram_addr <= std_logic_vector(v_sram_addr);
						else
							sram_pixel_count := sram_pixel_count + 1;
						end if;
						
						--------------------------
					
					when others =>
				end case;			
			
				if(v_enable_filter = '1') then
					
					window_out <= win_row_1 & win_row_2 & win_row_3 & win_row_4 & win_row_5;	-- Assamble the final 5x5 window 
					global_count := global_count + 1;
				end if;
				
				enable_filter <= v_enable_filter;
			
			end if;
		end if;
	end process;
end architecture;



