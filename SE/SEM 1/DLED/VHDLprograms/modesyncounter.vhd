
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity syn is
    Port ( clk : in std_logic;
           clr : in std_logic;
					pr : in std_logic;
		     m : in std_logic;
             q : out std_logic_vector(2 downto 0));
end syn;

architecture Behavioral of syn is
	 signal tmp: std_logic_vector (2 downto 0);
begin

  process (clk,clr,pr)
  begin
  if (clr = '0' and pr ='1')  then
  tmp <= "000" ;
 
  elsif (clr = '1' and pr ='0')  then
  tmp <= "111" ;

	elsif (clr = '0' and pr ='0')  then
  tmp <= "111" ;

  elsif ( m='0')   then
  if (clk'event and clk ='1')  then
  tmp <= tmp+1;

  end if;
    elsif ( m='1')   then
  if (clk'event and clk ='1')  then
  tmp <= tmp-1;

  end if;
  end if;

  end process;
  q<= tmp;
  
end Behavioral;

