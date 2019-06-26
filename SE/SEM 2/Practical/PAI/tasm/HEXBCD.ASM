.model small
.stack 64
.data

msg      db      10,13,'menu','$
msg1     db      10,13,'1.HEX TO BCD','$'
msg2     db      10,13,'2.BCD TO HEX','$'
msg3     db      10,13,'3.EXIT','$'
msg4     db      10,13,'4.ENTER YOUR CHOICE','$'

a        db       0


.code

print   MACRO   msg
        mov     ax,@data
        mov     ds,ax
        mov     ah,09
        lea     dx,msg
        int     21h
        ENDM


input   MACRO   var
        mov     ax,@data
        mov     ds,ax
        mov     ax,01h
        mov     var,al
        int     21h
        ENDM

main    proc    far
        mov     ax,@data
        mov     ds,ax
        print   msg
        print   msg1
        print   msg2
        print   msg3
        print   msg4
        input   a
        mov     ah,09
        lea     dx,msg
        int     21h
        mov     ah,4ch
        int     21h
main    endp
        end     main

