INTIALIZE MACRO
   MOV AX,0000H
   MOV BX,AX
   MOV DX,AX
   MOV CX,AX
ENDM

INPUT MACRO
   MOV AH,01H
   INT 21H;
ENDM

DISP MACRO MSG
   LEA DX,MSG
   MOV AH,09H
   INT 21H
ENDM

.model small
.data
   
	STR1 DB 10 DUP('$')
	STR2 DB 10 DUP('$')
	BYE DB 10,'BYE BYE$'
	DLINE DB 10,'=========================================',10,'$'
       SLINE DB 10,'-----------------------------------------',10,'$'
	menu DB 10,'1) String Input ',10,'2) Display ',10,'3) Concat',10,'4) Substring',10,'5) Compare String',10,'6) EXIT ',10,'Your Choice : $'
	PUBLIC STR1,STR2
	
.code
       
       MOV AX,@data
       MOV DS,AX
       MOV ES,AX
   EXTRN INPUTSTR2:FAR
   
   menuD:
       DISP DLINE
       DISP menu
       INPUT
       CMP AL,31H
       JE F1

       CMP AL,32H
       JE F2

       CMP AL,33H
       JE F3

       CMP AL,34H
       JE F4

       CMP AL,35H
       JE F5

       CMP AL,36H
       JE F6

  F1:   
  	DISP SLINE
      	EXTRN INPUTSTR:FAR
      	CALL INPUTSTR
      	
      	
        JMP menuD

  F5:  ;CAMPARE
  	DISP SLINE
  	
      	CALL INPUTSTR2
      	EXTRN STRCMP:FAR
      	CALL STRCMP
  	EXTRN 
  
       JMP menuD
 
  F4:  ;SUBSTRING
  	DISP SLINE
  	CALL INPUTSTR2
       EXTRN SUBSTRING:FAR
      	CALL SUBSTRING
       
       JMP menuD
  
  F3:   ;CONCAT
  	DISP SLINE
  	CALL INPUTSTR2
  	EXTRN CONCAT:FAR
      	CALL CONCAT
  	
  	
        JMP menuD
  
  F2:  ;DISPLAY
  	DISP SLINE
  	EXTRN DISPFAR:FAR
  	CALL DISPFAR
        JMP menuD
  
  F6: 
       DISP DLINE
  	DISP BYE
	DISP DLINE

       MOV AH,4CH
       INT 21H
end
