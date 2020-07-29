.data 
.balign 4
a: .skip 10

.text
.global main
main:
	ldr r1, =a				/* array base address */
	mov r2, #0				/* loop index */

	b L1					/* unconditional jump */	
L2:
	add r3, r1, r2, LSL #2	/* baseaddr + (i*4) */
	str r2, [r3]			/* a[i] = i */
	add r2, r2, #1			/* inc i */
L1:
	cmp r2, #99
	blt L2

	mov r0, r2
	bx lr

