.586
.model flat,stdcall
includelib libucrt.lib
includelib kernel32.lib

includelib ../../Lib/lib/Debug/lib.lib
ExitProcess PROTO : DWORD
outint PROTO : DWORD

.stack 4096

.const
	lI0 SDWORD  0
	lI1 SDWORD  0

.data
	       g_d BYTE 255 DUP(0)
	      d_ou SDWORD  0
	    Main_x SDWORD  0
	    Main_y SDWORD  0
	    Main_z SDWORD  0
	  Main_fds SDWORD  0
	Main_liter SDWORD  0

main PROC
	push x
	push y
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push 0
	pop eax
	pop ebx
	imul ebx
	push eax
main ENDP
end main

