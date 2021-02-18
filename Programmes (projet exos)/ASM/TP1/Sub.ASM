code segment
     assume CS :code
debut:
mov AL, 27h
sub AL, 21h

mov AX 4C00h
int 21h
code ends 
     end debut
