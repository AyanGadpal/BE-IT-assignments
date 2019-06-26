.model small
.stack 64
.data

a       db      0
b       db      0
c       db      0

.code
print   MACRO   msg
        mov     ax,@data
        mov     ds,ax
        mov     ah,02h
        lea     dl,msg
        int     21h
        ENDM

input   MACRO   var
        mov     ax,@data
        mov     ds,ax
        mov     ah,01h
        int     21h
        mov     var,al
        sub     var,30h
        ENDM

addno   MACRO   x,y,z
        mov     ax,@data
        mov     ds,ax
        mov     al,x
        add     al,y
        mov     z,al
        add     z,30h
        ENDM


main    proc    far
        mov     ax,@data
        mov     ds,ax
        input   a
        input   b
        addno   a,b,c
        print   c
        mov     ah,4ch
        int     21h
        main    endp
end     main
