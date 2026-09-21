library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity prescalar is
    port (
        clk     : in  std_logic;
        rst_bar : in  std_logic;
        enable  : out std_logic
    );
end prescalar;

architecture behavioral of prescalar is
    signal count : unsigned(13 downto 0);
begin

    process(clk)
    begin
        if rising_edge(clk) then
            if rst_bar = '0' then
                count  <= (others => '0');
                enable <= '0';

            elsif count = 9999 then
                count  <= (others => '0');
                enable <= '1';

            else
                count  <= count + 1;
                enable <= '0';
            end if;
        end if;
    end process;

end behavioral;