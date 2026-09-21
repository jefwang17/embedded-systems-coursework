-------------------------------------------------------------------------------
--
-- Title       : bcd_seven
-- Design      : bcd_seven
-- Author      : jeffery
-- Company     : stony brook
--
-------------------------------------------------------------------------------
--
-- File        : C:/Users/jeffe/OneDrive/Desktop/SBU/ese 382/lab 3/prelab_3/bcd_seven/bcd_seven/src/bcd_seven.vhd
-- Generated   : Tue Feb 17 19:42:10 2026
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
--{entity {bcd_seven} architecture {bcd_seven}}

library IEEE;
use IEEE.std_logic_1164.all;

entity bcd_seven is
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
end bcd_seven;

--}} End of automatically maintained section

architecture bcd_seven of bcd_seven is
begin

	
	seg_a <= (not a or b or c or d) and (not c or b or a or d);
	seg_b <= (not a or b or not c or d) and (a or not b or not c or d);
	seg_c <= (a or not b or c or d);
	seg_d <= (not a or b or c or d) and ( a or  b or not c or d) and (not a or not b or not c or d); 	
	seg_e <= (not a and not b and not c and not d) or (not a and b and not c and not d) or (not a and b and c and not d) or (a and not b and not c and d);
	seg_f <= (not a or b or c or d) and (a or not b or c or d) and (not a or not b or c or d) and (not a or not b or not c or d);
	seg_g <= (a or b or c or d) and (not a or b or c or d) and (not a or not b or not c or d);
	


end bcd_seven;
