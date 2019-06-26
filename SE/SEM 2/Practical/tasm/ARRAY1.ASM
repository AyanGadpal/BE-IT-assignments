DISP MACRO
        MOV CH,CL 
    L2:
        SPACEE
        MOV AH,02H
        MOV DL,[SI]
        INC SI
        INT 21H           
        DEC CH
        JNZ L2                

ENDM

INPUT MACRO 
     MOV CH,CL
     L1:
        SPACEE
        MOV AH,01H
        INT 21H
        MOV [SI],AL
        INC SI
        DEC CH
        JNZ L1                 ;LOOP END
ENDM

SPACEE MACRO
        MOV AH,02H
        MOV DL,20H
        INT 21H

ENDM

ADDARRAY
       ADD DL,0H
       MOV CH,CL

      L3: ADD DL,[SI]
          INC SI
          DEC CH
          JNZ L3

      MOV AH,02H
      INT 21H


ENDM
.MODEL SMALL

.DATA
        ARR DB 40 DUP(0)
        A DB ?       
.CODE
        MOV AX,@DATA
        MOV DX,AX
        MOV AX,0H
        MOV CX,0H
  
        LEA SI,ARR
        MOV AH,01H
        INT 21H
        SUB AL,30H
        MOV CL,AL

        INPUT 

        LEA SI,ARR

        DISP

        LEA SI,ARR

        ADDARRAY
        

        MOV AH,4CH
        INT 21H
END
