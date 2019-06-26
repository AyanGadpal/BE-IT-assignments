.model small
.stack 64
.data

c       db      00

.code

main    proc    far
        mov     ax,@data
        mov     ds,ax
        mov     cx,5

        ath:
        mov     ah,01
        int     21h
        mov     al,c
        loop    ath


        mov     ax,4c00h
        int     21h
main    endp
        end     main
