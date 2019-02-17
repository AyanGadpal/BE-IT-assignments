.model small
.stack 64h
.data
n1 dw 215
n2 dw 125
n3 dw ?
.code
        mov ax,@data
        mov ds,ax

        mov ax,n1
        add ax,n2
        mov n3,ax
    
        mov ah,4ch
        int 21H
end
