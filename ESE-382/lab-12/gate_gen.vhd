library ieee;
use ieee.std_logic_1164.all;

entity gate_gen is
    port (
        clk    : in  std_logic;
        rst_bar : in std_logic;

        start  : in  std_logic;
        stop   : in  std_logic;

        clocke : in  std_logic;
        starte : in  std_logic;
        stope  : in  std_logic;

        gate   : out std_logic
    );
end gate_gen;

architecture behavioral of gate_gen is

    type state_type is (closed, open_gate);
    signal present_state, next_state : state_type;

    signal start_d, stop_d : std_logic;
    signal start_event, stop_event : std_logic;

begin

    -- Store previous values of start and stop for edge detection
    process(clk)
    begin
        if rising_edge(clk) then
            if rst_bar = '0' then
                start_d <= '0';
                stop_d  <= '0';
            else
                start_d <= start;
                stop_d  <= stop;
            end if;
        end if;
    end process;

    -- Edge select logic
    start_event <= '1' when (starte = '1' and start_d = '0' and start = '1') or
                            (starte = '0' and start_d = '1' and start = '0')
                   else '0';

    stop_event <= '1' when (stope = '1' and stop_d = '0' and stop = '1') or
                           (stope = '0' and stop_d = '1' and stop = '0')
                  else '0';

    -- Process 1: State register with synchronous reset
    process(clk)
    begin
        if rising_edge(clk) then
            if rst_bar = '0' then
                present_state <= closed;
            else
                present_state <= next_state;
            end if;
        end if;
    end process;

    -- Process 2: Next-state logic
    process(present_state, start_event, stop_event)
    begin
        next_state <= present_state;

        case present_state is

            when closed =>
                if start_event = '1' then
                    next_state <= open_gate;
                end if;

            when open_gate =>
                if stop_event = '1' then
                    next_state <= closed;
                end if;

        end case;
    end process;

    -- Process 3: Output logic
    process(present_state)
    begin
        case present_state is
            when closed =>
                gate <= '0';

            when open_gate =>
                gate <= '1';
        end case;
    end process;

end behavioral;