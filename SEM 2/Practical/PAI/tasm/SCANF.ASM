.model small
.stack 64
.data
charname        db      0

.code
main    proc    far

        mov     ax,@data
        mov     ds,ax

        mov     ah,01h
        int     21h
        mov     charname,al


        mov     ah,2
        mov     dl,charname
        mov     dl,'*'
        int     21h

        mov     ax,4c00h
        int     21h
main    endp
        end     main
