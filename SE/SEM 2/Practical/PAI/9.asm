ORG 0000H
	
	
	MOV A,#38H
	ACALL COMMAND
	ACALL DELAY

	MOV A,#0FH
	ACALL COMMAND
	ACALL DELAY

	MOV A,#01H
	ACALL COMMAND
	ACALL DELAY


	
	MOV A,#8bH
	ACALL COMMAND
	ACALL DELAY

	MOV A,#'A'
	ACALL DATAWORD
	ACALL DELAY
	MOV A,#'B'
	ACALL DATAWORD
	ACALL DELAY
	MOV A,#'C'
	ACALL DATAWORD
	ACALL DELAY
	MOV A,#'D'
	ACALL DATAWORD
	ACALL DELAY
HERE:SJMP HERE


COMMAND: 
	MOV P1,A
	CLR P2.0	 ;RS 0 FOR CMD
	CLR P2.1	 ;R/W = 0 FOR WRITE
	SETB P2.2
	ACALL DELAY
	CLR P2.2
	RET

DATAWORD: 
MOV P1,A
	SETB P2.0	;RS 1 FOR DATA
	CLR P2.1
	SETB P2.2
	ACALL DELAY
	CLR P2.2
	RET
	RET

DELAY: 
	MOV R0,#50
	LOOP1:MOV R1,#255
	LOOP2:DJNZ R1,LOOP2
	DJNZ R0,LOOP1 
	RET
END
