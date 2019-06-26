   .model small
   .stack 100h
   .data
      msg0 db 10,10,10,'Enter choice    :  ','$'
      msg1 db 10,'1.BCD to Hexadecimal  ','$'
      msg2 db 10,'2 Hexadecimal to BCD ','$'
      msg3 db 10,'3.Exit  ','$'
      msg4 db 10,10,'Enter 5 digit BCD no : ','$'
      msg5 db 10,'HEX value is         : ','$'
      msg6 db 10,10,'Enter 4 digit HEX no : ','$'
      msg7 db 10,'BCD no is            : ','$'
      msg8 db 10,'Invalid Input   ','$'
      k  db 0
      array db 5 dup(0)
      res dw 0
      i dw 0

      disp1 MACRO msg
        lea dx,msg
        mov ah,09h
        int 21h
     ENDM

     INPUT MACRO
        mov ah,01h
        int 21h
     ENDM

     OUTPUT MACRO
        mov ah,02h
        int 21h
    ENDM
   .code
              
      mov ax,@data
      mov ds,ax

      label1:
        disp1 msg0
        disp1 msg1
        disp1 msg2
        disp1 msg3
      mov ah,01h
      int 21h
      mov k,al

             cmp k,31h
             je l1
             cmp k,32h
             je l2
             cmp k,33h
             je l3
             jmp label1
             l1:call bcd_to_hex
                jmp label1
             l2:call hex_to_bcd
                jmp label1
             l3:

             cmp k,33h
             je l4

             jmp label1

 l4:  mov ah,4ch
      int 21h

      bcd_to_hex proc near

       disp1 msg4

       lea si,array
       mov ch,05h


       loop1: INPUT
              cmp al,39h
              ja loop1
              mov ah,00h
              sub ax,30h
              mov [si],ax
            
              inc si
              dec ch
              jnz loop1
      ; dec si
       sub si,05
       mov ax,[si]
       cmp al,06h
       ja invalid
       add si,04
       mov ch,05h
       mov ax,0000h
       mov res,0000h
       mov i,0001h
       loop4: mov bx,[si]
              mov bh,00h
              mov ax,bx
              mul i
           
              add res,ax
              mov ax,i
              mov bx,000Ah
              mul bx
              mov i,ax


           
              dec si
              dec ch
              jnz loop4
     
     disp1 msg5
     call disp
     jmp r1
     invalid:  disp1 msg8
     r1:  ret
     bcd_to_hex ENDP


        disp proc near
                 mov ax,res
                 mov bx,ax
                 mov cx,0404h
                loop5:
                       rol bx,cl
                       mov dl,bl
                       and dl,0Fh
                       cmp dl,09h
                       jbe l
                       add dl,07h
                    l:add dl,30h

                       OUTPUT
                       dec ch
                       jnz loop5
                       ret
        disp endp

     



      hex_to_bcd proc near

       disp1 msg6

       mov cx,0404h
       mov dx,0000h
       w1:INPUT
          cmp al,39h
          jbe s1
          cmp al,41h
          jbe w1
          cmp al,46h
          jbe s1
          cmp al,61h
          jb w1
          cmp al,66h
          ja w1

        s1:  mov ah,00h
             sub ax,0030h
             cmp al,09h
             jbe d2

             sub al,07h

             cmp al,29h
             jbe d2
             sub al,20h

             d2:
             rol dx,cl
             add dx,ax
        
          dec ch
          jnz w1

       
      mov ax,dx
      mov bx,000Ah
      mov dx,0000h
      mov ch,04h
      mov k,00h
    w2: div bx
        push dx
        inc k
        mov dx,0000h
        dec ch
        jnz w2

    disp1 msg7
    mov ch,k
    w3:pop dx
       add dx,0030h
       OUTPUT
       dec ch
       jnz w3

       ret
     hex_to_bcd ENDP

  end
