data segment 
var dw 2016
ANNEES dw [N]
N db ? 
res dw []

data ends
assume cs:code , ds:data
code segment
mov AX, data
mov DS, AX
mov AX, var 
xor BX, BX
mov BX, 400
div BX
cmp AL, 0
jmp estbis
xor BX, BX
mov BX, 4
div BX
cmp AL,0
jmp estbis
xor BX, BX
mov BX, 100
div BX
cmp AL, 0
jmp estpasbis

estbis: 
mov AX, 1
jmp fin
estpasbis: 
mov AX, -1
jmp fin
fin:
code ends
end 