-------------------------------------------------------------------------------
--
-- Title       : hex_seven
-- Design      : hex_seven
-- Author      : jeffery
-- Company     : stony brook
--
-------------------------------------------------------------------------------
--
-- File        : C:/Users/jeffe/OneDrive/Desktop/SBU/ese 382/lab 3/hex_seven/hex_seven/src/hex_seven.vhd
-- Generated   : Tue Feb 17 20:24:37 2026
-- From        : Interface description file
-- By          : ItfToHdl ver. 1.0
--
-------------------------------------------------------------------------------
--
-- Description : 
--
-------------------------------------------------------------------------------

--{{ Section below this comment is automatically maintained
--    and may be overwritten
--{entity {hex_seven} architecture {hex_seven}}

library IEEE;
use IEEE.std_logic_1164.all;

entity hex_seven is
	port(
		a : in STD_LOGIC;
		b : in STD_LOGIC;
		c : in STD_LOGIC;
		d : in STD_LOGIC;
		seg_a : out STD_LOGIC;
		seg_b : out STD_LOGIC;
		seg_c : out STD_LOGIC;
		seg_d : out STD_LOGIC;
		seg_e : out STD_LOGIC;
		seg_f : out STD_LOGIC;
		seg_g : out STD_LOGIC
	);
end hex_seven;

--}} End of automatically maintained section

architecture hex_seven of hex_seven is
begin
		 seg_a <= (not a or b or c or d) and (a or b or not c or d) and (a or not b or not c or d) and (not a or not b or c or not d) and (not a or b or not c or not d);
		 seg_b <= (not a or b or not c or d) and (a or not b or not c or d) and (not a or not b or c or not d) and (a or b or not c or not d) and (a or not b or not c or not d) and (not a or not b or not c or not d);
		 seg_c <= (a or not b or c or d) and (a or b or not c or not d) and (a or not b or not c or not d) and (not a or not b or not c or not d); 
		 seg_d <= (not a or b or c or d) and (a or b or not c or d) and (not a or not b or not c or d) and (not a or b or c or not d) and (a or not b or c or not d) and (not a or not b or not c or not d);
		 seg_e <= (not a or b or c or d) and (not a or not b or c or d) and (a or b or not c or d) and (not a or b or not c or d) and (a or b or c or not d) and (not a or b or c or not d);	  
		 seg_f <= (not a or b or c or d) and (a or not b or c or d) and (not a or not b or c or d) and (not a or not b or not c or d) and (not a or b or not c or not d);
		 seg_g <= (a or b or c or d) and (not a or b or c or d) and (not a or not b or not c or d) and (a or b or not c or not d);
		 
end hex_seven;
