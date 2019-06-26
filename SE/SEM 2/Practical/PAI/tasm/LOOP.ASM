.model small
.stack 64
.data

d       dw      10

.code

main    proc    far
        mov     ax,@data
        mov     ds,ax

        mov     ax,01
        mov     cx,10
atharva:
        inc     ax
        
        loop    atharva

        mov     ax,4c00h
        int     21h
main    endp
        end     main
