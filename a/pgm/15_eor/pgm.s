.data 
msg:	.asciz "hello world\n"
.text

.equ FIQ_MODE,0x00000011
.equ HYP_MODE,0x0000001a
.equ SVC_MODE,0x00000013

.globl main


main:
	push {r7,lr}

	ldr r0, =msg
	bl printf

	mov r0, #HYP_MODE
	mov r1, #SVC_MODE
	eor r1, r1, #HYP_MODE
	mov r0, r1

	pop {r7, pc}

