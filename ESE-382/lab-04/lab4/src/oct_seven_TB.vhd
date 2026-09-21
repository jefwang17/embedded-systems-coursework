-- Testbench for oct_seven (laboratory 3 task 1 s26)

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;	-- package needed for to_unsigned function
use work.all;
	
entity bcd_seven1a_tb is
end bcd_seven1a_tb;

architecture tb_architecture of bcd_seven1a_tb is

-- stimulus signals - signals mapped to the inputs UUT	
	signal bcd : std_logic_vector (3 downto 0);
	-- observed signals - signals mapped to the outputs of UUT
	signal segment : std_logic_vector (6 downto 0);
	
	constant period : time := 20 ns;	-- time between each stimulus

begin
	-- Unit Under Test port map
	UUT : entity bcd_seven1a
		port map (
		bcd => bcd,
		segment => segment
		
			
		);

    stim: process
    begin
        for i in 0 to 15 loop
            bcd <= std_logic_vector(to_unsigned(i,4));
            wait for period;
        end loop;
        std.env.finish;	--procedure to end simulation (preferred over wait;)
    end process;

end tb_architecture;



