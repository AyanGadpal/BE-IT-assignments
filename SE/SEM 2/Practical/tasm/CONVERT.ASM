
DISP MACRO MSG
                LEA DX,MSG
                MOV AH,09H
                INT 21H
ENDM
INPUT MACRO
        MOV AH,01H
        INT 21H
ENDM
INTIA MACRO
        MOV AX,0000H
        MOV BX,AX
        MOV DX,AX
        MOV CX,AX
      

ENDM

.model small
.data
        MENU DB 10,'1) BCD TO HEX',10,'2) HEX TO BCD',10,'3) EXIT',10,'$'
        NL DB 10,'HEX : ','$'
        INVALID DB 10,'Invalid',10,'$'
        ARRAY DW 2710H,03E8H,0064H,000AH,0001H
        MSG1 DB 10,'ENTER THE VALUE $'
        RES DW 0H
.code
        MOV AX,@DATA
        MOV DS,AX
        INTIA
        MOV RES,AX
        
        ;--------------MAIN-----------------
    IN1:
        DISP MENU
        INPUT
        CMP AL,31H
        JNE NEXT
        CALL BCDP
        JMP IN1
   NEXT:CMP AL,32H
        JNE END2
        CALL HEXP
        JMP IN1
   END2:CMP AL,33H
        JNE DEFAULT
        JMP MOUT1
DEFAULT:DISP INVALID
        JMP IN1
  MOUT1:

        ;-------------END MAIN--------------
        MOV AH,4CH
        INT 21H


        ;------------PROCEDURES--------------
        BCDP PROC
       
                INTIA
                MOV SI,OFFSET ARRAY
                MOV CH,05H
                MOV RES,0000H                

          LOOP1:
                DISP MSG1
                INPUT
                MOV DX,[SI]
                MOV AH,00H
                SUB AL,30H
                MUL DX
                ADD RES,AX
                INC SI
                INC SI
                DEC CH
                JNZ LOOP1
        
                INTIA
                MOV CX,0404H
                MOV BX,RES
        
                DISP NL
        
         @start:
                ROL BX,CL
                MOV DL,BL
                AND DL,0FH
                CMP DL,09H
                JBE @down
                ADD DL,07H
                
                @down:
                ADD DL,30H
                       
                MOV AH,02H
                INT 21H
        
                DEC CH
                JNZ @start
                MOV DX,BX     
        
                RET
                ENDP BCDP
        
        HEXP PROC
       
                INTIA
                MOV SI,OFFSET ARRAY
                MOV CH,05H
                MOV RES,0000H                

                



        RET
        ENDP HEXP

end
