data SEGMENT
TAB dw 26,14,9,37,13,5
MOYENNE db ?
N db 6
data ends
assume cs:code , ds:data
code segment
MOV AX, data
MOV DS, AX
MOV AX, 0 
MOV CL, 1
MOV SI, 0
debut_boucle : 
CMP CL, N
JG fin_boucle 
ADD AX, TAB[SI]
INC CL
INC SI
INC SI
JMP debut_boucle
fin_boucle : 
DIV N
MOV MOYENNE, AL 
code ends
end 