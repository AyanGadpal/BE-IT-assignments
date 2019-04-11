string_input macro x
	lea dx,x
	mov ah,3fh
	int 21h
endm

string_display macro
	mov ah,09h
	int 21h
endm

.model small
.data
	msg db 10,13,'Enter Main String=>',10,13,'$'
	msg1 db 10,13,'Enter Sub-String=>',10,13,'$'
	msg2 db 'No. of times sub-string is present in main string:- ','$'
	noc db 30h
	str1 db 20 dup('$')
	str2 db 20 dup('$')
.code
	mov ax,@data
	mov ds,ax
	
	lea dx,msg
	mov ah,09h
	int 21h
	
	lea dx,str1
	mov ah,3fh
	int 21h
	
	lea dx,msg1
	mov ah,09h
	int 21h
	
	lea dx,str2
	mov ah,3fh
	int 21h
	
	lea si,str1
	lea di,str2
	dec di
	dec si
	
l0:
	inc di
	cmp byte ptr[di],'$'
	jne l0

	dec di
	mov byte ptr[di],'$'
	dec di
	mov byte ptr[di],'$'
	 
l1:	
	lea di,str2
	inc si
	mov dl,byte ptr[si]
	cmp dl,'$'
	je exit
	cmp dl,byte ptr[di]
	je l2
	jmp l1
	
l2:
	inc si
	inc di
	mov dl,byte ptr[di]
	cmp dl,byte ptr[si]
	je l2
	cmp dl,'$'
	jne l1
	inc noc
	cmp byte ptr[si],'$'
	je exit
	jmp l1
	
exit:	
	lea dx,msg2
	mov ah,09h
	int 21h
	
	mov dl,noc
	mov ah,02h
	int 21h
	
	mov ah,4ch
	int 21h
end
