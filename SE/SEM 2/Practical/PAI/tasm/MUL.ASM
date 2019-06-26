.model small
.stack 64
.data
d       dw      22
e       dw      2
f       dw      ?
.code

main    proc    far
        mov     ax,@data
        mov     ds,ax
        mov     ax,d
        mul     e
        mov     f,ax
        mov     ax,4c00h
        int     21h
main    endp
        end     main
