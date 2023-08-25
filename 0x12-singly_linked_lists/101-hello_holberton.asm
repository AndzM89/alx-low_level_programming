global main
extern printf

section .data
format db "Hello, Holberton", 0x0A

section .text
main:
	mov edi, format
	xor eax, eax
	call printf
	mov eax, 0
	ret
