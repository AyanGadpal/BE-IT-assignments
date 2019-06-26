	input 	macro

        mov     ah,01h
        
	int 	21h
       
        sub 	al,48
           
	mov 	num1,al

        mov 	ah,01h
            
	int 	21h
            
	sub 	al,48
            
	mov 	num2,al     

        mov 	al,num1
            
	mul 	ten
            
	add 	al,num2
	
	endm

	output 	macro

	mov 	ah,02h

	int 	21h

	endm

disp 	macro 	var

	lea 	dx,var

	mov 	ah,09h

	int 	21h

	endm

	.model 	small

	.stack

	.data

m1 	db 	10,13,'how many nos?:$'

m2 	db 	10,13,'enter nos:$'

m3 	db 	10,13,'addition=$'

m4 	db 	10,13,'$'

array 	db 	10 dup(0)

count 	db 	0
   
num1 	db 	0
    
num2 	db 	0
    
temp 	db 	0
   
ten 	db 	10
	
	.code

	mov 	ax,@data

	mov 	ds,ax

	lea 	si,array

	disp 	m1

	input

	mov 	count,al

	mov 	cl,count

	disp	m4

s1: 	disp 	m2

	input

	mov 	[si],al

	inc 	si

	loop 	s1

	disp 	m4

	disp 	m3

	mov 	ax,0000h

	mov 	cl,count

	lea 	si,array

s2: 	add 	al,[si]

	inc 	si

	loop 	s2

	mov 	ch,02h

	mov 	cl,04h

	mov 	bl,al

s3: 	rol 	bl,cl

	mov 	dl,bl

	and 	dl,0fh

	cmp 	dl,09

	jbe 	s4

	add 	dl,07

s4: 	add 	dl,30h
	
	output

	dec 	ch

	jnz 	s3

	mov 	ah,4ch

	int 	21h

	end
