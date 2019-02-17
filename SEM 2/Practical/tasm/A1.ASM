.model small
.stack 100h
.data
msg db 'Hello World',13,10,'$'
.code
        mov ax,@data
        mov ds,ax
        mov ah,9
        mov dx, OFFSET msg
        int 21h
        mov ah,4ch
        int 21h
end
