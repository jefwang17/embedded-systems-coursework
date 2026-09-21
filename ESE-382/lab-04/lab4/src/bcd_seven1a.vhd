-------------------------------------------------------------------------------
--
-- Title       : bcd_seven1a
-- Design      : bcd_seven1
-- Author      : jeffery
-- Company     : stony brook
--
-------------------------------------------------------------------------------
--
-- File        : C:/Users/jeffe/OneDrive/Desktop/SBU/ese 382/lab4/lab4/src/bcd_seven1a.vhd
-- Generated   : Sun Feb 22 16:47:23 2026
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
--{entity {bcd_seven1a} architecture {bcd_seven1a}}



Library ieee;
use ieee.std_logic_1164.all;


entity bcd_seven1a is
	port(	
		bcd     : in  std_logic_vector(3 downto 0);
        segment : out std_logic_vector(6 downto 0)
		);
	
end bcd_seven1a;

--}} End of automatically maintained section

architecture bcd_seven1a of bcd_seven1a is
begin
	with bcd select
	segment <= 
	"0111111" when "0000",
	"0000110" when "0001",
	"1011011" when "0010",
	"1001111" when "0011",
	"1100110" when "0100",
	"1101101" when "0101",
	"1111100" when "0110",
	"0000111" when "0111",
	"1111111" when "1001",
	"1100111" when "1010",
	"0000000" when others;

end bcd_seven1a;
