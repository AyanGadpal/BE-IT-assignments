input     macro

mov     ah,01h

int     21h

sub     al,30h

mov     ah,01h

int     21h

sub     al,30h

mov     num2,al

mov     al,num1

mul     ten

add     al,num2

endm

output  macro

mov     ah,02h

int     21h

endm

disp    macro   var
        lea     dx,var
        mov     ah,09h
        int     21h
        endm

        .model  small
        .stack  64
        .data

line1   db      10,13,'Enter how many no.s:$'
line2   db      10,13,'enter numbers:$'
line3   db      10,13,'addition=$'
line4   db      10,13,'$'

array   db      15 dup(0)

count   db      0

num1    db      0

num2    db      0

temp    db      0

ten     db      10

        .code
main    proc    far
        mov     ax,@data
        mov     ds,ax
        lea     si,array
        disp    line1
        
         input
         mov     count,al
         mov     cl,count
         disp    line4
lb1:     disp    line2

        input

        mov     [si],al
        inc     si
        loop    lb1
        disp    line4
        disp    line3
        mov     ax,0000h
        mov     cl,count
        lea     si,array
lb2:    add     al,[si]
        inc     si
        loop    lb2
        mov     ch,02h
        mov     cl,04h
        mov     bl,al
lb3:    rol     bl,cl
        mov     dl,bl
        and     dl,0fh
        cmp     dl,09
        jbe     lb4
        add     dl,07

lb4:    add     dl,30h

        output
        dec     ch
        jnz     lb3
        mov     ah,4ch
        int     21h
main    endp
        end     main

