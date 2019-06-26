-- Expt No. 10.1 Simulation and Implementation of Full-adder using Behavioral style model using VHDL.

library IEEE;
use IEEE.STD_LOGIC_1164.all;


entity fa is
	port( a,b,cin: in STD_LOGIC; cout: out STD_LOGIC; sum: out STD_LOGIC);
end fa;
architecture fa1 of fa is
begin
	process (a,b,cin)
	begin
	if (a ='0' and b='0'and cin ='0') then
		sum <= '0';
		cout <='0';
	elsif(a ='0' and b='1'and cin ='0') then
		sum <= '1';
		cout <='0';
	elsif( a='1' and b='0'and cin = '0')then
		sum <= '1';
		cout <='0';
		elsif( a='1' and b='1'and cin = '0')then
		sum <= '0';
		cout <='1';
		elsif( a='0' and b='0'and cin = '1')then
		sum <= '1';
		cout <='0';
		elsif( a='0' and b='1'and cin = '1')then
		sum <= '0';
		cout <='1';	
		elsif( a='1' and b='0'and cin = '1')then
		sum <= '0';
		cout <='1';	
		elsif( a='1' and b='1'and cin = '1')then
		sum <= '1';
		cout <='1';	
		
		end if;
	end process;
	end fa1;

