library ieee;
use ieee.std_logic_1164.all;

entity prescalar_system_tb is
end prescalar_system_tb;

architecture testbench of prescalar_system_tb is

    signal clk     : std_logic := '0';
    signal rst_bar : std_logic := '0';
    signal enable  : std_logic;
    signal digit   : std_logic_vector(1 downto 0);

    constant period : time := 250 ns; -- 4 MHz

begin

    uut_prescalar: entity work.prescalar
        port map (
            clk     => clk,
            rst_bar => rst_bar,
            enable  => enable
        );

    uut_counter: entity work.digit_counter
        port map (
            clk     => clk,
            rst_bar => rst_bar,
            enable  => enable,
            digit   => digit
        );

    -- Clock
    process
    begin
        while true loop
            clk <= '0';
            wait for period/2;
            clk <= '1';
            wait for period/2;
        end loop;
    end process;

    -- Stimulus
    process
    begin
        rst_bar <= '0';
        wait for 1 us;

        rst_bar <= '1';

        -- Run long enough to see multiple enable pulses
        wait for 10 ms;

        wait;
    end process;

end testbench;