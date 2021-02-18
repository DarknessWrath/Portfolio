data      SEGMENT
taille    DB 3
mat       DB 1,2,3,4,5,6,7,8,9
vec       DB 2,3,4
res       DW 3 dup (?)
data      ENDS
assume cs:code , ds: data
debut: 
mov AX, data
mov DS, AX
mov BP, 0
mov DI, 0
boucle 1: mov CL, taille
mov SI, 0 
boucle2: XOR AX,AX
xor, DX, DX
mov AL, mat[BP+SI]
mov DL, vec[SI]
MUL, DL
add res[DI]
inc SI
loop boucle2
add DI, 2
add BP, 3 
cmp BP, 9
JNE boucle 1:
mov AX, 4C00h
int 21h
code ends
end debut
