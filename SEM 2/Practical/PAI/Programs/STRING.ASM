;#3
;NAME: AYAN N GADPAL

DISP MACRO MSG
   LEA DX,MSG
   MOV AH,09H
   INT 21H
ENDM

INPUT MACRO
   MOV AH,01H
   INT 21H;
ENDM

INTIALIZE MACRO
   MOV AX,0000H
   MOV BX,AX
   MOV DX,AX
   MOV CX,AX
ENDM


.model small

.data
       ;-----------------STRING DECLARETION-------------------
       STR1 DB 15 dup('$') 
       STR2 DB 15 dup('$') 
       invalid DB 10,'INVALID $'
       menu DB 10,'1) String Input ',10,'2) Display ',10,'3) Length',10,'4) Reverse',10,'5) Palimdrome ',10,'6) EXIT ',10,'Your Choice : $'
       INPMSG DB 10,'Enter the String : $'
       LENMSG DB 10,'LENGTH : $'
       REVMSG DB 10,'REVERSE : $'
       PALIMSG DB 10,'PALIDROME : $'
       YES DB  'YES$'
       NO DB 'NO$'
       DISPMSG DB 10,'DISPLAY	 :$'
       BYE DB 10,'BYE BYE$'
       DLINE DB 10,'=========================================',10,'$'
       SLINE DB 10,'-----------------------------------------',10,'$'
       INPT DB 10,'INPUT REQUIRED$'
      
       ;------------------VARIABLE--------------------
       TEMP DB 0H
       FLAG DB 0H

.code

       MOV AX,@data
       MOV DS,AX

      ;=============MAIN==============


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
        DISP INPMSG
        CALL INPUTSTR
        JMP menuD

  F3:   
  	DISP SLINE
  	CALL LENPROC
        JMP menuD
  F4:   
  	DISP SLINE
  	CALL STRCPY
  	CALL STRREV
        JMP menuD
  
  F5:   
  	DISP SLINE
  	DISP PALIMSG
    	CALL PALICMP
        JMP menuD
  
  F2:  
  	DISP SLINE
  	CALL STRCPY
  	DISP DISPMSG
        DISP STR2+2
        
        JMP menuD
  
  F6:   DISP DLINE
  	DISP BYE
	DISP DLINE
        ;================END MAIN==============

       MOV AH,4CH
       INT 21H

       INPUTSTR PROC
           INTIALIZE
           
           LEA DX,STR1
           MOV AH,0AH
           INT 21H
           MOV AL,STR1+1
           DAA
           MOV TEMP,AL
           MOV FLAG,01H
       RET
       ENDP INPUTSTR

       ;--------------------------LENGTH------------------------------
       LENPROC PROC
         
          DISP LENMSG
          INTIALIZE
          MOV BL,TEMP
       
          MOV CX,0204H
	

	S1:
		ROL BL,CL
		MOV DL,BL
		AND DL,0FH
		CMP DL,09H
		JBE S2
		ADD DL,07H

		S2:
		ADD DL,30H
		

		MOV AH,02H
		INT 21H
		DEC CH
		JNZ S1
        
  
         
       RET
       ENDP LENPROC
       
       STRREV PROC
         
         
	         
	  INTIALIZE
	  
          MOV CL,STR1+1
          SUB CL,1H
          LEA SI,STR1+2
          
          L1:
          	INC SI
          	DEC CL
          	CMP CL,0
          	JNE L1
          	
          LEA DI,STR1+2
          MOV AL,STR1+1
          MOV BL,02H
          DIV BL
          MOV CL,AL
          L2:
          	MOV DL,[DI]
          	MOV AL,[SI]
          	MOV [SI],DL
          	MOV [DI],AL
          	INC DI
          	DEC SI
          	DEC CL
          	CMP CL,0
          	JNE L2
          DISP STR1+2
       RET
       ENDP STRREV
       
       
       PALICMP PROC
       
       INTIALIZE
         MOV AL,FLAG
         CMP AL,0
         JZ K5
         
         
          MOV CL,STR1+1
          SUB CL,1H
          LEA SI,STR1+2
          
          K1:
          	INC SI
          	DEC CL
          	CMP CL,0
          	JNE K1
          	
          LEA DI,STR1+2
          MOV AL,STR1+1
          MOV BL,02H
          DIV BL
          MOV CL,AL
          K2:
          	MOV DL,[DI]
          	MOV AL,[SI]
          	CMP DL,AL
          	JNE K3
          	INC DI
          	DEC SI
          	DEC CL
          	CMP CL,0
          	JNE K2
          DISP YES
          JMP K4
          
       K5:
         DISP INPT  
         JMP K4 
       
       K3:
          DISP NO 
       K4:
       
       RET
       ENDP PALICMP
       
       STRCPY PROC
       		INTIALIZE
       		MOV CL,STR1+1          	
          	LEA SI,STR1+2
          	LEA DI,STR2+2
          	;REP MOVSB 
          	
          	J1:
          	  
          	    MOV DL,[SI]
          	    MOV [DI],DL
          	    INC SI
          	    INC DI
          	    DEC CL
          	    CMP CL,0H
          	    JNE J1
       		
         
       RET 
       ENDP STRCPY
       
       

end
