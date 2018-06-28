LIBRARY ieee;
USE ieee.std_logic_1164.all;

entity keystream_generator is
port (
	clk		 		: IN std_logic;
	key_iv			: IN std_logic_vector(79 downto 0);
	sw2hw				: IN std_logic_vector(2 downto 0);
	state				: IN std_logic_vector(1 downto 0);
	hw2sw				: OUT std_logic_vector(2 downto 0);
	value_out		: OUT std_logic_vector(95 downto 0)
);
end entity;

architecture beh of keystream_generator is
	type state_type is (s0, s1, s2, s3);
	signal states   : state_type;

	signal reset : std_logic := '0';
	
	signal cipher_block : std_logic_vector(288 downto 1) := (others => '0');
	--signal s_key, s_iv : std_logic_vector(80 downto 0);
	
	signal load_done : std_logic := '0';
	signal setup_done : std_logic := '0';
	
	signal s_value_out : std_logic_vector(95 downto 0); 
	signal waiting_for_zero : std_logic := '0';
	signal cipher_block_initialise :std_logic :='0';
	signal key_signal : std_logic_vector(79 downto 0);
	signal iv_signal : std_logic_vector(79 downto 0);

	
begin
	process (clk, reset)
	begin
		if reset = '1' then
			states <= s0;
		elsif (rising_edge(clk)) then
			case states is
				when s0=>	-- IDLE
				
					if((sw2hw = "001") or (sw2hw = "010")) then
						states <= s1;
					end if;		
					
				when s1=>	-- LOAD Key and IV	
					if(state = "10") then
						states <= s2;
					end if;
				when s2=>
					if(setup_done = '1') then
						states <= s3;
					end if;
				when s3 =>	-- STREAM Bits
					if(sw2hw = "101") then	-- 5 = go to idle and stop streaming (i.e. reset).
						states <= s0;
					end if;
				when others =>
					states <= s0;
					
			end case;
		end if;
	end process;
	
	process(clk)
		variable setup_count : integer := 0;
		variable reg_count : integer := 95;
		variable t1, t2, t3 : std_logic := '0';
		variable k1, k2, k3 : std_logic := '0';
		variable turn_check : std_logic := '0';
		variable loadKey : std_logic := '0';
		variable loadIV  : std_logic := '0';
		
		--variable flagShit   : std_logic := '0';
	begin
		if(rising_edge(clk)) then
			case states is
				when s0=>
					cipher_block_initialise <= '0';
					waiting_for_zero <='0';
					setup_count := 0;
					reg_count := 95;
					loadIV :='0';
					setup_done<='0';
					loadKey :='0';
				when s1=>	-- Load key or iv based on the sel signal
					if((sw2hw = "001") and (loadKey = '0')) then
						--if(flagShit = '0') then
						key_signal <=key_iv;
						loadKey := '1';
						hw2sw <= "001";
					elsif((sw2hw = "010") and (loadIV = '0')) then
						iv_signal <= key_iv; 
						loadIV := '1';
						hw2sw <= "010";
					end if;
					
				when s2=>	-- Setup Cipher_block
					if(cipher_block_initialise = '0')then
						cipher_block(80 downto 1) <= key_signal;
						cipher_block(93 downto 81) <= (others => '0');
						cipher_block(173 downto 94) <= iv_signal;
						cipher_block(177 downto 174) <= (others => '0');
						cipher_block(285 downto 178) <= (others => '0');
						cipher_block(288 downto 286) <= "111";
						cipher_block_initialise <= '1';
					elsif(setup_count < 1152) then
						-- for i 1 to 4 * 288 do
						t3 := cipher_block(243) XOR (cipher_block(286) AND cipher_block(287)) XOR cipher_block(288) XOR cipher_block(69);   
						t1 := cipher_block(66) XOR (cipher_block(91) AND cipher_block(92)) XOR cipher_block(93) XOR cipher_block(171); 
						t2 := cipher_block(162) XOR (cipher_block(175) AND cipher_block(176)) XOR cipher_block(177) XOR cipher_block(264); 
						
						-- ROTATE
						cipher_block(93 downto 2) <= cipher_block(92 downto 1); 
						cipher_block(1) <= t3;
						cipher_block(177 downto 95) <= cipher_block(176 downto 94); 
						cipher_block(94) <= t1;
						cipher_block(288 downto 179) <= cipher_block(287 downto 178); 
						cipher_block(178) <= t2;				
						
						setup_count := setup_count + 1;
						
					else 
					
						--value_out <= cipher_block(96 downto 1);  --cipher_block(96 downto 1);
						setup_done <= '1';
						
						--if(cipher_block(96 downto 1) = X"4317E3049A0354FAE769E1E0") then
						--hw2sw <= "11";	
						--end if;
					end if;
					
				when s3 =>
					-- waiting for software to clear the read done signal
					if(waiting_for_zero = '1')then
						if(sw2hw = "000")then
							waiting_for_zero <= '0';
						end if;
						
				   elsif(reg_count >= 0) then
							k1 := cipher_block(66) xor cipher_block(93);
							k2 := cipher_block(162) xor cipher_block(177);
							k3 := cipher_block(243) xor cipher_block(288);
							
							-- Stream bit
							s_value_out(reg_count) <= k1 xor k2 xor k3;
							
							reg_count := reg_count - 1;
							
							t1 := k1 xor (cipher_block(91) and cipher_block(92)) xor cipher_block(171);
							t2 := k2 xor (cipher_block(175) and cipher_block(176)) xor cipher_block(264); 
							t3 := k3 xor (cipher_block(286) and cipher_block(287)) xor cipher_block(69);				
							
							-- ROTATE
							cipher_block(93 downto 2) <= cipher_block(92 downto 1); 
							cipher_block(1) <= t3;
							cipher_block(177 downto 95) <= cipher_block(176 downto 94); 
							cipher_block(94) <= t1;
							cipher_block(288 downto 179) <= cipher_block(287 downto 178); 
							cipher_block(178) <= t2;
						
					else
						--value_out <=  cipher_block(96 downto 1);--X"7b9d443097f099476b3617cc";--s_value_out;
						
						value_out <= s_value_out;
						hw2sw <= "011";
						
--						if(sw2hw = "11") then
--							reg_count := 0;
--						end if;
						
						
						if(sw2hw = "011") then
							hw2sw <= "000";
							waiting_for_zero <= '1'; --want the hardware to wait for the software the clear the read done signal
							reg_count := 95;
						end if;
					end if;
	
						
						
						
--						if(turn_check = '0') then
--							--turn_check := '1';
--							ack <= "011";
--						elsif(turn_check = '1') then
--							--turn_check := '0';
--							ack <= "100";
--						end if;
--					
--						if((sel = "011") and (turn_check = '0')) then
--							reg_count := 0;
--							turn_check := '1';
--						elsif((sel = "100") and (turn_check = '1')) then
--							reg_count := 0;
--							turn_check := '0';
--						end if;
				
				when others =>
					-- Do nothing
					
			end case;
		end if;
	end process;
	
end architecture;