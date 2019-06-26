;#2 HEX TO BCD , BCD TO HEX , STACK , MENU
;NAME : AYAN N.GADPAL
;BATCH : H11 (201-18)
;ROLL NO. : 23370


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
.stack 4096
.data
        MENU DB 10,'1) BCD TO HEX',10,'2) HEX TO BCD',10,'3) EXIT',10,'$'
        NL DB 10,'HEX : ','$'
        INVALID DB 10,'Invalid',10,'$'
        ARRAY DW 10000,03E8H,0064H,000AH,0001H
        MSG1 DB 10,'ENTER THE VALUE $'
        MSG2 DB 10,'HEX : $'
        RES DW 0H
        COUNT DB 0
       
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
       
                INTIA ; intialize all register to 0
                MOV SI,OFFSET ARRAY 
                MOV CH,05H
                MOV RES,0000H                

          LOOP1:
                DISP MSG1
                INPUT
                MOV DX,[SI] ;10000,1000...10 loaded into dx with index 0 at first iteration
                MOV AH,00H  
                SUB AL,30H
                MUL DX      ;result stored in AX
                ADD RES,AX  
                INC SI
                INC SI ;as array is dw +2 si
                DEC CH
                JNZ LOOP1 ;5 times
        
                INTIA
                MOV CX,0404H
                MOV BX,RES
        
                DISP NL
        
         @start:
                ROL BX,CL ;left by 4
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
              ;  MOV DX,BX     
        
                RET
                ENDP BCDP
        
        HEXP PROC


        RESTART:
               INTIA
               MOV CH,04H
               MOV CL,04H

        INPUT1:
               DISP MSG1
               INPUT
               MOV AH,00H

            H1:CMP AL,30H
               JB INVALID1
               CMP AL,39H
               JG H2
               SUB AL,30H
               JMP NEXT1
               

            H2:CMP AL,41H
               JB INVALID1
               CMP AL,46H
               JG H3
               SUB AL,37H
               JMP NEXT1

            H3:CMP AL,61H
               JB INVALID1
               CMP AL,66H
               JG INVALID1                            
               SUB AL,57H
               JMP NEXT1

         INVALID1:
                DISP INVALID
                JMP RESTART

         NEXT1:
                ROL BX,CL
                ADD BX,AX
                DEC CH
                JNZ INPUT1

       ;----------------STACK PUSH---------------
        MOV CX,0404H
        MOV AX,BX
hloop:

        MOV DX,0000H
        MOV BX,0010        
        DIV BX
        PUSH DX
        INC COUNT
        CMP AX,0000H
        JNE hloop


        DISP MSG2
dispp:
        
        POP DX
       
        ADD DL,30H
        MOV AH,02H
        INT 21H
        DEC COUNT
        JNZ dispp


        RET
        ENDP HEXP



end
