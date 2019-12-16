.586
.model flat,stdcall
includelib libucrt.lib
includelib kernel32.lib

includelib lib.lib


ExitProcess PROTO : DWORD
outint PROTO : DWORD
outstr PROTO : DWORD
outintn PROTO : DWORD
outstrn PROTO : DWORD
isGreather	PROTO: DWORD, :DWORD
checkLines	PROTO: DWORD, :DWORD

.stack 4096

.const
	divisionByZero db 'ERROR: DIVIDE BY ZERO', 0
	belowZeroNum db 'ERROR: NUM IS BELOVER THAN ZERO', 0
	lI0 SDWORD 2
	lI1 SDWORD 1
	lI2 SDWORD 6
	lI3 SDWORD 3
	lS4 BYTE "True" , 0
	lS5 BYTE "False" , 0
	lI6 SDWORD 0

.data
	       d_z SDWORD  0
	     del_u SDWORD  0
	     del_l SDWORD  0
	    Main_m SDWORD  0
	    Main_l SDWORD  0
	    Main_s SDWORD  0
	 Main_func SDWORD  0
	Main_func1 SDWORD  0
	  Main_del SDWORD  0
	    Main_d SDWORD  0

.code
glob_d PROC d_x: DWORD, d_y: DWORD, d_k: DWORD
	push d_x
	push d_y
	pop ebx
	pop eax
	add eax, ebx
	push eax
	push lI0
	pop ebx
	pop eax
	imul ebx
	push eax
	push d_k
	pop ebx
	mov edx, 0 
	pop eax
	idiv ebx
	push edx
	mov eax, edx
	pop eax
	cmp eax, 0
	jl below
	mov d_z, eax
	ret
	below:
	push offset belowZeroNum
	call outstr
	call exitProcess
glob_d ENDP
glob_del PROC del_x: DWORD, del_y: DWORD
	push del_x
	push del_y
	pop ebx
	pop eax
	add eax, ebx
	push eax
	pop eax
	cmp eax, 0
	jl below
	mov del_l, eax
	ret
	below:
	push offset belowZeroNum
	call outstr
	call exitProcess
glob_del ENDP

main PROC
	mov Main_m, 1
	push lI1
	mov Main_l, 6
	push lI2
	mov Main_s, 3
	push lI3
	push Main_l
	push Main_m
	call glob_del
	mov Main_func, eax
	push Main_func
	call outintn
	push Main_l
	push Main_func
	push Main_m
	call glob_d
	mov Main_func1, eax
	push Main_func1
	call outintn
	push Main_m
	push Main_l
	pop ecx
	pop edx
	cmp edx, ecx
	jg trueResult
	jl falseResult
	trueResult:
	push offset lS4
	call outstr
	jmp code
	leave
	falseResult:
	push offset lS5
	call outstr
	leave
	code:
	ret
	below:
	push offset belowZeroNum
	call outstr
	call exitProcess
main ENDP
end main

