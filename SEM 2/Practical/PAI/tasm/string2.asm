.model small
.data
 extern str1:byte
        str2:byte

.code
 public concat
 concat proc far
    lea dx,str1
    mov ah,09h
    int 21h
    ret 
endp
end
