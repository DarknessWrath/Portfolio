data        SEGMENT
valeur      dw  0f8b4h;  
diviseur dw 10000,1000,100,10,1
message db "Le code decimal est :$"
reschain db 30h,30h,30h,30h,30h,"$"
data ends
assume cs:code, ds:data
code segment
debut:  	
mov AX, data
mov DS, AX
mov SI, 0
mov Bp, 0 
xor AX, AX
mov AX, valeur 
boucle: 
xor DX,DX
div diviseur[SI]
add reschain[BP], AL
xor AX, AX
mov AX, DX
add SI, 2
inc BP
cmp BP, 5
jne boucle 
xor DX, DX
lea DX, message
mov AH, 09h
int 21h
lea DX, reschain
mov AH, 09h
int 21h 
mov AX, 4C00h
int 21h 

code ends
end debut 