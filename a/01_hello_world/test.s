# GNU style
	.section .text
	.global _start

_start:					//start
	mul r1, r0, r0
	mov r0,r1
	mov pc,lr

	.end

