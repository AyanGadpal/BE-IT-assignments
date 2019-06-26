INTIALIZE MACRO
   MOV AX,0000H
   MOV BX,AX
   MOV DX,AX
   MOV CX,AX
ENDM

INPUTSTR MACRO

	   INTIALIZE
           LEA DX,STR1
           MOV AH,0AH
           INT 21H

ENDM



.model small
.data
   
	STR1 DB 10 DUP('$')
	STR2 DB 10,13
	PUBLIC STR1,STR2
	
.code
       
       MOV AX,@data
       MOV DS,AX
       MOV ES,AX
   
          
       INPUTSTR 
       
       EXTRN DISP:FAR
       CALL DISP

        MOV AH,4CH
        INT 21H
end
