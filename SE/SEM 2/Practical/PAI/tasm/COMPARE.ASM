.model small
.stack 64
.data

d       dw      10


.code

main    proc    far
        mov     ax,@data
        mov     ds,ax
        mov     bx,d
        CMP     bx,44
        je      ath
        mov     ax,4
        jmp     key

        ath:    mov ax,1
        key: 
        mov     ah,4ch
        int     21h
        main     endp
end     main

        
        
           

        
        

