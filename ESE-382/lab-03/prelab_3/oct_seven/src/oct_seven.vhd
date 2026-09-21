-------------------------------------------------------------------------------
--
-- Title       : oct_seven
-- Design      : oct_seven
-- Author      : jeffery
-- Company     : stony brook
--
-------------------------------------------------------------------------------
--
-- File        : C:/Users/jeffe/OneDrive/Desktop/SBU/ese 382/lab 3/prelab_3/oct_seven/src/oct_seven.vhd
-- Generated   : Tue Feb 17 18:56:52 2026
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
--{entity {oct_seven} architecture {oct_seven}}

library IEEE;
use IEEE.std_logic_1164.all;

entity oct_seven is
	port(
		c : in STD_LOGIC;
		b : in STD_LOGIC;
		a : in STD_LOGIC;
		seg_a : out STD_LOGIC;
		seg_b : out STD_LOGIC;
		seg_c : out STD_LOGIC;
		seg_d : out STD_LOGIC;
		seg_e : out STD_LOGIC;
		seg_f : out STD_LOGIC;
		seg_g : out STD_LOGIC
	);
end oct_seven;

--}} End of automatically maintained section

architecture oct_seven of oct_seven is
begin

	seg_a <= (not a or b or c) and (not c or b or a);
	seg_b <= (not a or b or not c) and (a or not b or not c);
	seg_c <= (a or not b or c);
	seg_d <= (not a or b or c) and ( a or  b or not c) and (not a or not b or not c);
	seg_e <= (not a and not b and not c) or (not a and b and not c) or (not a and b and c);
	seg_f <= (not a and  not b and not c) or (not a and not b and c) or (a and not b and c) or (not a and b and c);
	seg_g <= (a or b or c) and (not a or b or c) and (not a or not b or not c);
	
end oct_seven;
