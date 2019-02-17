.model small
.data
msg DB 'Hello World',10,13,'$'

.code
mov ax,@data
mov ds,ax

mov dx,offset msg
mov ah,09h
Int 21H   

mov ah,4ch
Int 21H

end
