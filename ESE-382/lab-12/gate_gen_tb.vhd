library ieee;
use ieee.std_logic_1164.all;

entity gate_gen_tb is
end gate_gen_tb;

architecture testbench of gate_gen_tb is

    signal clk     : std_logic := '0';
    signal rst_bar : std_logic := '0';

    signal start   : std_logic := '0';
    signal stop    : std_logic := '0';

    signal clocke  : std_logic := '1';
    signal starte  : std_logic := '1';
    signal stope   : std_logic := '1';

    signal gate    : std_logic;

    constant period : time := 20 ns;

begin

    uut: entity work.gate_gen
        port map (
            clk     => clk,
            rst_bar => rst_bar,
            start   => start,
            stop    => stop,
            clocke  => clocke,
            starte  => starte,
            stope   => stope,
            gate    => gate
        );

    -- Clock generation
    clk_process: process
    begin
        while true loop
            clk <= '0';
            wait for period / 2;
            clk <= '1';
            wait for period / 2;
        end loop;
    end process;

    -- Stimulus
    stim_process: process
    begin

        -- Reset
        rst_bar <= '0';
        wait for 40 ns;

        rst_bar <= '1';
        wait for 40 ns;

        -- Test 1: positive start edge, positive stop edge
        starte <= '1';
        stope  <= '1';

        start <= '0';
        stop  <= '0';
        wait for 40 ns;

        start <= '1';      -- gate should turn ON
        wait for 40 ns;

        start <= '0';
        wait for 60 ns;

        stop <= '1';       -- gate should turn OFF
        wait for 40 ns;

        stop <= '0';
        wait for 60 ns;

        -- Test 2: negative start edge, negative stop edge
        starte <= '0';
        stope  <= '0';

        start <= '1';
        stop  <= '1';
        wait for 40 ns;

        start <= '0';      -- gate should turn ON
        wait for 60 ns;

        stop <= '0';       -- gate should turn OFF
        wait for 60 ns;

        wait;

    end process;

end testbench;