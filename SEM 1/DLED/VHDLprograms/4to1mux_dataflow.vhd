--- Expt No. 9.1 Simulation and implementation of 4:1 multiplexer using Dataflow modelling using VHDL.


library ieee;
use ieee.std_logic_1164.all;

entity mux1 is
	port(I0,I1,I2,I3: in bit;
	s : in bit_vector (1 downto 0);
	y : out bit);
end mux1;

architecture muxx of mux1 is
begin
	y<=((not s(1) and not s(0) and I0) or 
		  (not s(1) and s(0) and I1) or 
		  (s(1) and not s(0) and I2) or 
		  (s(1) and s(0) and I3));
end muxx; 
		