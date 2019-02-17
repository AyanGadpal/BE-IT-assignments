--- Expt No. 9.2 Simulation and implementation of 4:1 multiplexer using stuctural modelling using VHDL.


library IEEE;
use IEEE.std_logic_1164.all;

entity and3 is
port (A,B,C : in bit ;
D : out bit);
end and3;

architecture and_stru of and3 is
begin
D <= A and B and C; end and_stru;

entity or4 is
port (E,F,G,H : in bit;
I : out bit);
end or4;

architecture or_stru of or4 is
begin
I <= E or F or G or H; end or_stru;

entity inv_1 is
port (J : in bit;
K : out bit);
end inv_1;

architecture inv_stru of inv_1 is
begin
K <= not J; end inv_stru;

entity MUX4X1 is
port(I0,I1,I2,I3,s1,s0 : in bit;
Y : out bit);
end MUX4X1;

architecture MUX_STRU of MUX4X1 is
	COMPONENT AND3
		PORT( A,B,C: IN bit; D: OUT bit);
	END COmponent;
	COMPONENT OR4
		PORT( E,F,G,H: IN bit; I: OUT bit);
	END COmponent;
	COMPONENT INV_1
		PORT( J: IN bit; K: OUT bit);
	END COmponent;	  
	
		
SIGNAL S0BAR,S1BAR,temp1,temp2,temp3,temp4: bit;
BEGIN
	U0: INV_1 PORT MAP (S1,S1BAR);
	U1: INV_1 PORT MAP (S0,S0BAR);
	V0: AND3 PORT MAP (I0,S1BAR,S0BAR,temp1); 
	V1: AND3 PORT MAP (I1,S1BAR,S0 ,temp2);
	V2: AND3 PORT MAP (I2,S1 ,S0BAR,temp3);
	V3: AND3 PORT MAP (I3,S1 ,S0 ,temp4);
	V4: OR4 PORT MAP ( temp1,temp2,temp3,temp4,Y);
	

end MUX_STRU;