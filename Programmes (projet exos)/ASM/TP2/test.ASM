data SEGMENT
	a DW 7h
	
data ENDS
code segment
	assume CS:code, DS:data
debut: 
mov AL, byte ptr [a]
code ends 
	end debut

 