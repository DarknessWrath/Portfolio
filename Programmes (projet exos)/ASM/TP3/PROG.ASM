data segment
N db 7 
VAR db 3
TAB db 12, 4, 3, 9, 5, 21, 16
RES db ? 
MOYENNE DB 

data ends
assume cs:code , ds:data
code segment
debut:   
mov AX, data
mov ds, AX
lea BX, TAB
xor DX, DX
xor CX, CX
xor SI, SI
mov CL, N
mov DH, VAR
boucle:  
xor AX, AX
mov AL, byte ptr [BX+SI]
div DH
cmp AH, 0
jne next
inc DL
next: 
inc SI
loop boucle
mov RES, DL 
fin:  
mov AX,4C00h   
int 21h
code ends
end debut                                                                                                                                                                                                                        
