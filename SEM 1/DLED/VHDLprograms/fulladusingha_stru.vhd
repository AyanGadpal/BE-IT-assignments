--Expt No. 10.2 Simulation and Implementation of Full-adder using Strucural style model using VHDL.


library ieee;
use ieee.std_logic_1164.all;

entity HA is
port(A,B: in bit;
s, c: out bit);
end HA;

architecture HA_struct of HA is
begin
	s <= A xor B;
	c <= A and B;
end HA_struct;

entity FA is
port(X,Y,cin: in bit;
sum, cout: out bit);
end FA;

architecture FA_struct of FA is
component HA 
port (A,B : in bit;
s,c: out bit);
end component;

signal temp1, temp2, temp3: bit;
begin
	HA1 : HA port map(A=>X, B=>Y, S=>temp2, C=>temp1);
	HA2 : HA port map(A=>temp2, B=>cin, c=>temp3, s=>sum);

cout <= temp1 or temp3;

end FA_struct;