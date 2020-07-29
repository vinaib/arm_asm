.data 
.balign 4
a: .skip 400

.text
.global main
main:
	ldr r1, =a		/* array base address */
	mov r2, #0		/* loop index */

	b L1			/* unconditional jump */	
L2:

	add r2, r2, #1
L1:
	cmp r2, #99
	blt L2

	mov r0, r2
	bx lr

