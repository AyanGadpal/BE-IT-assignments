.model small

.data
A DB 00H
B DB 00H
SUM1 DB ?

sum_msg DB 'SUM : ',10,13,'$'


.code
MOV AX,@data
MOV DS,AX

MOV AL,A
ADD AL,B
DAA

mov cx,0204h
mov bl,al

loop2:
     
        rol bl,cl
        mov dl,bl
        and dl,0fh
        cmp dl,09h
        jbe @loop1
        add dl,07h
@loop1:
        add dl,30h
        dec cl
        



;------------------TERMINATION-----------------
MOV AH,4CH
INT 21H
end


