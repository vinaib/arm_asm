; source: https://jumpnowtek.com/shellcode/linux-arm-shellcode-part1.html	
	.text
	.global _start

_start:
	mov r0, #1			@fd = stdout
	ldr r1, =string1	@address of the string
	mov r2, #12			@string length
	mov r7, #4			@syscall for write
	swi #0				@software interrupt

_exit:
	mov r7, #1			@syscall for exit
	swi #0

	.data
	string1:	.asciz	"Hello world \n"

