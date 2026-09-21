library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity digit_counter is
    port (
        clk     : in  std_logic;
        rst_bar : in  std_logic;
        enable  : in  std_logic;
        digit   : out std_logic_vector(1 downto 0)
    );
end digit_counter;

architecture behavioral of digit_counter is
    signal count : unsigned(1 downto 0);
begin

    process(clk)
    begin
        if rising_edge(clk) then
            if rst_bar = '0' then
                count <= (others => '0');

            elsif enable = '1' then
                count <= count + 1;
            end if;
        end if;
    end process;

    digit <= std_logic_vector(count);

end behavioral;