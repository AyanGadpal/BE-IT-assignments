.model small
.stack 64
.data

buff    db      81
        db      0
        db      81 dup('$')
msg0    db      10,13,'MENU','$'
msg1    db      10,13,'1.LENGTH','$'
msg2    db      10,13,'2.DISPLAY REVERSE','$'
msg3    db      10,13,'3.PALINDROME','$'
msg4    db      10,13,'4.ENTER YOUR CHOICE','$'





input   MACRO   msg
       ; mov     ax,@data
        mov     ah,0ah
        mov     dx, seg buff
        mov     ds,dx
        mov     dx,offset buff
        int     21h
        ENDM

disp    MACRO   var
        mov     ax,@data
        mov     ah,09h
        lea     dx,var
        int     21h
        ENDM
.code
main    proc    far
        mov     ax,@data
        input   buff
label1:
        disp    msg0
        disp    msg1
        disp    msg2
        disp    msg3
        mov     ax,4c00h
        int     21h
main    endp
        end     main

