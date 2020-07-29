.data

.balign 4

msg1: .asciz "CPSR %0x\n"


.text
.global main

main:
	/* this has to be called if you call other function
	 * from your program
	 */
	stmdb sp!, {lr}

	mrs r1, cpsr
	ldr r0, add_of_msg1 

	bl printf

	orr r1, r1, #64
	msr cpsr_c, r1

	mrs r1, cpsr
	ldr r0, add_of_msg1 
	bl printf

	mrc p15, 0, r1, c0, c0, 0
	ldr r0, add_of_msg1 
	bl printf


	/* restore lr contents */
	ldmia sp!, {lr}

	bx lr

add_of_msg1: .word msg1

.global printf
