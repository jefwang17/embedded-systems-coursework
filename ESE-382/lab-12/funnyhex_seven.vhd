library ieee;
use ieee.std_logic_1164.all;

entity funnyhex_seven is
    port (
        hex  : in  std_logic_vector(3 downto 0);
        segs : out std_logic_vector(6 downto 0)
    );
end funnyhex_seven;

architecture behavioral of funnyhex_seven is
begin

    process(hex)
    begin
        case hex is
            when "0000" => segs <= "1111110"; -- 0
            when "0001" => segs <= "0110000"; -- 1
            when "0010" => segs <= "1101101"; -- 2
            when "0011" => segs <= "1111001"; -- 3
            when "0100" => segs <= "0110011"; -- 4
            when "0101" => segs <= "1011011"; -- 5
            when "0110" => segs <= "1011111"; -- 6
            when "0111" => segs <= "1110000"; -- 7
            when "1000" => segs <= "1111111"; -- 8
            when "1001" => segs <= "1111011"; -- 9
            when "1010" => segs <= "1110111"; -- A
            when "1011" => segs <= "1001110"; -- C
            when "1100" => segs <= "1000111"; -- F
            when "1101" => segs <= "0110111"; -- H
            when "1110" => segs <= "1100111"; -- P
            when "1111" => segs <= "0111110"; -- U
            when others => segs <= "0000000";
        end case;
    end process;

end behavioral;