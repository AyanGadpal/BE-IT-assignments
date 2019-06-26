; 1 
; add array of numbers

.model small
.data

.code
    MOV AX,@data
    MOV DS,AX




    MOV AH,4CH
    INT 21H
end