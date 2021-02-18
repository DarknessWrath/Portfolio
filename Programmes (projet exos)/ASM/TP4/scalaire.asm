data      SEGMENT
taille    DB 3
vec1      DB 1,2,3
vec2      DB 4,5,6
prod      DW 1(?)
data      ENDS
assume cs:code , ds:data
code segment
debut: 
mov AX, data
mov DS, AX
mov CL, taille
	boucle: 
xor AX, AX
mov AL, vec1[SI]
xor BX, BX
mov BL, vec2[SI]
mul BL
add DL, AL
inc SI
	loop boucle
mov prod, DX
code ends
end debut

 
 