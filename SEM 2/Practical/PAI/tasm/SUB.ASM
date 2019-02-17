.model small
.stack 64
.data

d        dw     215
e        dw     125
f        dw     ?
.code
main    proc    far
        mov     ax,@data
        mov     ds,ax
        mov     ax,d
        sub     ax,e
        mov     f,ax

        mov     ax,4c00h
        int     21h
main    endp
        end     main

