-- Testbench for oct_seven (laboratory 3 task 1 s26)

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;	-- package needed for to_unsigned function
use work.all;
	
entity hex_seven_tb is
end hex_seven_tb;

architecture tb_architecture of hex_seven_tb is

-- stimulus signals - signals mapped to the inputs UUT	
	signal d : std_logic;
	signal c : std_logic;
	signal b : std_logic;
	signal a : std_logic;
	-- observed signals - signals mapped to the outputs of UUT
	signal seg_a : std_logic;
	signal seg_b : std_logic;
	signal seg_c : std_logic;
	signal seg_d : std_logic;
	signal seg_e : std_logic;
	signal seg_f : std_logic;
	signal seg_g : std_logic;
	
	constant period : time := 20 ns;	-- time between each stimulus

begin
	-- Unit Under Test port map
	UUT : entity hex_seven
		port map ( 
			d => d,
			c => c,
			b => b,
			a => a,
			seg_a => seg_a,
			seg_b => seg_b,
			seg_c => seg_c,
			seg_d => seg_d,
			seg_e => seg_e,
			seg_f => seg_f,
			seg_g => seg_g
		);

    stim: process
    begin
        for i in 0 to 7 loop
            (d, c, b, a) <= (to_unsigned(i,4));
            wait for period;
        end loop;
        std.env.finish;	--procedure to end simulation (preferred over wait;)
    end process;

end tb_architecture;



