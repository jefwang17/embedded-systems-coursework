library ieee;
use ieee.std_logic_1164.all;

entity buffer_reg is
    port (
        clk      : in  std_logic;
        rst_bar  : in  std_logic;
        gate     : in  std_logic;
        sig_out  : in  std_logic_vector(15 downto 0);
        data_out : out std_logic_vector(15 downto 0)
    );
end buffer_reg;

architecture behavioral of buffer_reg is
    signal gate_d : std_logic;
    signal buffer_data : std_logic_vector(15 downto 0);
begin

    process(clk)
    begin
        if rising_edge(clk) then
            if rst_bar = '0' then
                gate_d      <= '0';
                buffer_data <= (others => '0');

            else
                gate_d <= gate;

                if gate_d = '1' and gate = '0' then
                    buffer_data <= sig_out;
                end if;
            end if;
        end if;
    end process;

    data_out <= buffer_data;

end behavioral;