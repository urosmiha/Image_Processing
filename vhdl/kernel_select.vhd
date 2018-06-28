LIBRARY ieee;
USE ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- This kernel selector will support two filters; Sobel and Gaussian.
entity kernel_select is
port (
		clk		: in std_logic;
		kernel	: out signed(36 downto 1);
		sel		: in std_logic_vector(3 downto 0);
		denom		: out signed(4 downto 0)

);
end entity;

architecture beh of kernel_select is

	signal gauss_kernel 	 	: signed(36 downto 1) := X"121242121";	-- [1,2,1,2,4,2,1,2,1] Gaussian Blur;
	signal sobel_x_kernel 	: signed(36 downto 1) := X"10F20E10F";	-- [1,0,-1,2,0,-2,1,0,-1] Sobel X
	signal sobel_y_kernel 	: signed(36 downto 1) := X"121000FEF";	-- [1,2,1,0,0,0,-1,-2,-1] Sobel Y
	signal identity_kernel	: signed(36 downto 1) := X"000010000";	-- [0,0,0,0,1,0,0,0,0] Identity
	signal inversion_kernel	: signed(36 downto 1) := X"0000F0000";	-- [0,0,0,0,-1,0,0,0,0] inversion
	signal scalling_kernel	: signed(36 downto 1) := X"000020000";	-- [0,0,0,0,2,0,0,0,0] Scalling
	signal sharpen_kernel	: signed(36 downto 1) := X"0F0F5F0F0";	-- [0,-1,0,-1,5,-1,0,-1,0] Sharpen
	signal box_blur_kernel	: signed(36 downto 1) := X"111111111";	-- [1,1,1,1,1,1,1,1,1] Box Blur
	signal edge_de1_kernel	: signed(36 downto 1) := X"10F000F01";	-- [1,0,-1,0,0,0,-1,0,1] Edge 
	signal edge_de2_kernel	: signed(36 downto 1) := X"0101C1010";	-- [0,1,0,1,-4,1,0,1,0] Edge
	signal default_kernel	: signed(36 downto 1) := X"111111111";	-- [1,1,1,1,1,1,1,1,1] Default
	
	signal box_blur_denom 	: signed(4 downto 0) := "01001";	-- 9
	signal single_denom 		: signed(4 downto 0) := "00001";	-- 1
	signal gauss_denom  		: signed(4 downto 0) := "10000";	-- 16

begin

	process(clk)
	begin
		if(rising_edge(clk)) then
		
			case sel is
				when "0001" =>					-- Gauss
					kernel <= gauss_kernel;
					denom  <= gauss_denom;
				when "0010" =>					-- Sobel X
					kernel <= sobel_x_kernel;
					denom  <= single_denom;
				when "0011" =>					-- Sobel Y
					kernel <= sobel_y_kernel;
					denom  <= single_denom;
				when "0100" =>					-- Identity
					kernel <= identity_kernel;
					denom  <= single_denom;
				when "0101" => 				-- Inversion
					kernel <= inversion_kernel;
					denom  <= single_denom;
				when "0110" => 				-- Scalling
					kernel <= scalling_kernel;
					denom  <= single_denom;
				when "0111" =>					-- Sharpen
					kernel <= sharpen_kernel;
					denom  <= single_denom;	
				when "1000" =>					-- Box Blur
					kernel <= box_blur_kernel;
					denom  <= box_blur_denom; 
				when "1001" =>					-- Edge 1
					kernel <= edge_de1_kernel;
					denom  <= single_denom;
				when "1010" =>					-- Edge 2
					kernel <= edge_de2_kernel;
					denom  <= single_denom;
				when others =>					-- Default
					kernel <= gauss_kernel;
					denom  <= single_denom;
			end case;
		end if;
		
	end process;
end architecture;