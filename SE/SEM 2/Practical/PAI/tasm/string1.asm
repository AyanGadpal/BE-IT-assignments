.model small 
.data
 str1 db 'enter your name'
 str2 db 'you name is:'
 public str1,str2

.code
 extern concat far
 call concat
end 
