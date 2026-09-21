library ieee;
use ieee.std_logic_1164.all;

entity signature_system_tb is
end signature_system_tb;

architecture testbench of signature_system_tb is

    signal clk     : std_logic := '0';
    signal rst_bar : std_logic := '0';

    signal start   : std_logic := '0';
    signal stop    : std_logic := '0';
    signal data_in : std_logic := '0';

    signal starte  : std_logic := '1';
    signal stope   : std_logic := '1';
    signal clocke  : std_logic := '1';

    signal gate    : std_logic;
    signal sig_out : std_logic_vector(15 downto 0);
    signal buffer  : std_logic_vector(15 downto 0);

    constant period : time := 20 ns;

begin

    -- gate generator
    u_gate: entity work.gate_gen
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

    -- LFSR (your existing one)
    u_lfsr: entity work.hp5004a_lfsr
        port map (
            clk     => clk,
            rst_bar => rst_bar,
            gate    => gate,
            data_in => data_in,
            sig_out => sig_out
        );

    -- buffer
    u_buffer: entity work.buffer_reg
        port map (
            clk      => clk,
            rst_bar  => rst_bar,
            gate     => gate,
            sig_out  => sig_out,
            data_out => buffer
        );

    -- clock
    process
    begin
        while true loop
            clk <= '0';
            wait for period/2;
            clk <= '1';
            wait for period/2;
        end loop;
    end process;

    -- stimulus (simulated DUT behavior)
    process
    begin
        -- reset
        rst_bar <= '0';
        wait for 100 ns;
        rst_bar <= '1';

        -- START pulse (turn gate ON)
        wait for 50 ns;
        start <= '1';
        wait for 20 ns;
        start <= '0';

        -- simulate clock activity
        for i in 0 to 50 loop
            data_in <= not data_in;
            wait for 20 ns;
        end loop;

        -- STOP pulse (turn gate OFF → buffer captures)
        stop <= '1';
        wait for 20 ns;
        stop <= '0';

        wait for 200 ns;

        -- second cycle
        start <= '1';
        wait for 20 ns;
        start <= '0';

        for i in 0 to 50 loop
            data_in <= not data_in;
            wait for 20 ns;
        end loop;

        stop <= '1';
        wait for 20 ns;
        stop <= '0';

        wait;

    end process;

end testbench;