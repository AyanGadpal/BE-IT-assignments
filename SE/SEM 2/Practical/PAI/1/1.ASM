; 1 
; add array of numbers

; Macros

DISP MACRO MSG ; DISPLAY
    LEA DX,MSG
    MOV AH,09H
    INT 21H
ENDM

INPUT MACRO 
    MOV AH,01H
    INT 21H
    SUB AL,30H
    MOV AH,00H
ENDM

SCAN MACRO X; INPUT 

    
    DISP ENTVAL

    INPUT
    MUL HUN
    MOV N1,AX

    INPUT
    MUL TEN
    MOV N2,AX

    INPUT
    MOV N3,AX

    XOR AX,AX
    ADD AX,N1
    ADD AX,N2
    ADD AX,N3
    MOV X,AX
ENDM 

INTIA MACRO   ; INITIALIZTION
    XOR AX,AX
    XOR BX,BX
    XOR CX,CX
    XOR DX,DX
ENDM

.model small ; SINCE OUR PROGRAM DONT NEED MUCH MEMORY 
.stack 64
.data
    NEWLINE DB 10,13
    ENTVAL DB 10,13,"ENTER THE VALUE $"
    RESULT DB 10,13,"SUM : $"
  
    TEN DB 10
    HUN DB 100
    
    VAL DW 100 DUP(0)

    SUM DW 0
    N1 DW 0
    N2 DW 0
    N3 DW 0
    COUNT DW 0



.code
    MOV AX,@data
    MOV DS,AX

    ;Menu 
    SCAN COUNT
    ;MOV BX, COUNT

    MOV CX,COUNT
    MOV DI,0
    @LOOP1:
        SCAN VAL[DI]
        MOV AX,VAL[DI]
        ADD SUM,AX
        INC DI
        DEC CX
        JNZ @LOOP1

    INTIA

    MOV BX,SUM
    MOV CX,0010
    DISP RESULT
    MOV COUNT ,0000H

    @UP:
        XOR DX,DX
        MOV AX,BX
        DIV CX
        MOV BX,AX
        ADD DL,30H
        PUSH DX
        INC COUNT
        CMP BX,0000H
    JNE @UP

    @LOOP3:
        POP DX
        MOV AH,02H
        INT 21H
        DEC COUNT
    JNZ @LOOP3

    ;proc
    



    MOV AH,4CH
    INT 21H
end