; 4 FAR PROCEDURES

;--------MACROS----------
DISP MACRO M 
    LEA DX,M
    MOV AH,09H
    INT 21H
ENDM 
INPUTSTR MACRO S
    LEA DX,S
    MOV AH,0AH
    INT 21H
ENDM

INTIALIZE MACRO; INTIALIZE ALL REGISTORS CONTAIN TO 0
    XOR AX,AX
    XOR BX,BX
    XOR CX,CX
    XOR DX,DX
ENDM

.MODEL SMALL
.DATA
    EXTRN STR1:BYTE
    EXTRN STR2:BYTE
    STR3 DB 30 DUP("$")

    ENTSTR DB 10,13,"ENTER THE STRING :$"

    NOTEQ DB 10,13,"STRING ARE NOT ENQUAL $"
    EQL DB 10,13,"STRINGS ARE EQUAL $"
    NSS DB 10,13,"SUBSTRING NOT FOUND !$"

    B1 DB 10,13,"EQUAL$"
    B2 DB 10,13,"RESET $"
    B3 DB 10,13,"HOGA $"
 
    FOUND DB 10,13,"found $"
    COUNT DB 0
    TEMP DW ?
    LEN DB ?

.CODE
    MOV AX,@DATA
    MOV DS,AX
    MOV ES,AX
    
    PUBLIC INPUTSTR1
    INPUTSTR1 PROC FAR
        DISP ENTSTR
        INPUTSTR STR1
    RET
    ENDP

    ; CHOICE 4
    PUBLIC REVSTR
    REVSTR PROC FAR
        
        INTIALIZE
        
        MOV CL,STR1+1 ; LENGTH 
        LEA SI,STR1+2 
        @LOOP1:
            INC SI
            DEC CL
        JNZ @LOOP1 ; SI POINTING TO LAST 
        
        MOV CL,STR1+1
        LEA DI,STR2+2
        MOV STR2+1,CL
        @LOOP2:
            MOV AX,[SI]
            MOV [DI],AX
            INC DI
            DEC SI
            DEC CL
        JNZ @LOOP2

    RET
    ENDP

    ; CHOICE 3
    PUBLIC CMPSTR
    CMPSTR PROC FAR   
        INTIALIZE
        DISP ENTSTR
        INPUTSTR STR2
        MOV AL,STR1+1
        MOV BL,STR2+1
        CMP AL,BL
        JNE _NOTEQ
        
        LEA SI,STR1+2
        LEA DI,STR2+2
        MOV CL,STR1+1
        REPE CMPSB

        CMP CL,00H
        JNE _NOTEQ
        DISP EQL
        JMP _END
        
        
        _NOTEQ:
            DISP NOTEQ    
    _END:
    RET
    ENDP

     ; CHOICE 5
    PUBLIC CONCAT
    CONCAT PROC FAR   
        INTIALIZE
        DISP ENTSTR
        INPUTSTR STR2

        MOV CL,STR1+1 ;LENGTH
        LEA SI,STR1+2 ;
        LEA DI,STR3+2 

        REP MOVSB

        MOV CL,STR2+1
        LEA SI,STR2+2

        REP MOVSB

        DISP STR3+2


    RET
    ENDP

    ; CHOICE 6
    PUBLIC SUBSTRING
    SUBSTRING PROC FAR   
        INTIALIZE
        DISP ENTSTR
        INPUTSTR STR2
        ; START
        MOV COUNT,00H
        MOV AL,STR1+1 
        MOV LEN,AL ; LENGHT OF STRING 
        MOV CL,STR2+1 
        CMP CL,LEN ; LENGHT OF SUB-STRING 
        JNB _NSS   ; CLEARLY NOT A SUB STRING

        LEA SI,STR1+2
        LEA DI,STR2+2

        @UP:
        MOV AL,[SI]
        MOV BL,[DI]
        CMP AL,BL
        JE NEXT
    CON:INC SI
        DEC LEN
        JNZ @UP
        CMP COUNT,00H
        JNE _FOUND
        JMP _NSS
      
      NEXT:
        MOV TEMP,SI
        MOV CH,STR2+1     
        @COMPA:
            MOV AL,[SI]
            MOV BL,[DI]
            INC SI
            INC DI
            CMP AL,24H ; $
            JE @RESET
            CMP AL,BL
            JNE @RESET
            DEC CH
            JNZ @COMPA
            INC COUNT
        @RESET:
            MOV SI,TEMP
            LEA DI,STR2+2
            JMP CON
        
        _FOUND:
            DISP FOUND
            MOV DL,COUNT
            ADD DL,30h
            MOV AH,02H;
            INT 21H
            JMP @ENDSUBSTRING

        _NSS:
            DISP NSS

    @ENDSUBSTRING:
    RET
    ENDP

    


  




    MOV AH,4CH
    INT 21H
END
