---Expt No. 12 Simulation and implementation 4 bit bidirectional shift register using VHDL.

library ieee;
use ieee.std_logic_1164.all;

entity bishif is
	port(din,clk,dsr,rstbar:in bit;
	q:out bit_vector (3 downto 0));
end bishif;

architecture bishift1 of bishif is
signal sreg: bit_vector(3 downto 0);
begin
	process(clk,rstbar,dsr)
	begin
		if(rstbar='0') then
		sreg<="0000";
		elsif(clk'event and clk='1') then
			if (dsr='1') then
				sreg(3)<=din;
				sreg(2)<=sreg(3);
				sreg(1)<=sreg(2);	
				sreg(0)<=sreg(1);
			else
				sreg(0)<=din;
				sreg(1)<=sreg(0);
				sreg(2)<=sreg(1);	
				sreg(3)<=sreg(2);
			end if;
		end if;
	q<=sreg;
	end process;
end bishift1;
