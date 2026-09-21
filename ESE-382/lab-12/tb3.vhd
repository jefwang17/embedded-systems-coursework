library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity funnyhex_tb is
end funnyhex_tb;

architecture testbench of funnyhex_tb is

    signal hex  : std_logic_vector(3 downto 0);
    signal segs : std_logic_vector(6 downto 0);

begin

    uut: entity work.funnyhex_seven
        port map (
            hex  => hex,
            segs => segs
        );

    process
    begin
        for i in 0 to 15 loop
            hex <= std_logic_vector(to_unsigned(i, 4));
            wait for 20 ns;
        end loop;

        wait;
    end process;

end testbench;