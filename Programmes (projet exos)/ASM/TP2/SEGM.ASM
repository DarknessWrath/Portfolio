data SEGMENT
	a DB 12h
	b DW 1234h
	c DD 12345678h
	d DB 12h,24h,56h,78h 
	e DB 'ABCDEF' 
	f DB 100 dup(?)
data ENDS
code segment
	assume CS:code, DS:data
debut: mov AX,data
	mov DS,AX
	mov BX, 
	lea SI, e 
	mov AL, [SI]
	mov AH, [SI+05h]
	
code ends 
	end debut

 