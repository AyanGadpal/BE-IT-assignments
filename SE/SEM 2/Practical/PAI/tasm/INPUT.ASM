.model small

.data
A DB 20h
B DB 90H
SUM DB ?

.code
MOV AX,@data
MOV DS,AX

MOV Al,A
ADD Al,B
MOV SUM,Al

;Terminating
MOV AH,4CH
INT 21H

end
