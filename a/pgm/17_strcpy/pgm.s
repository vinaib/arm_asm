.section .data

.section .text
.globl asm_strcpy

/* with out this line, on calling this function it says an illegal instruction.
 * This line looks like mandatory when you call assemlby function from c file.
 * Can it be called from other asm file?
 * Yes it can be called from other asm file. Following .type attribute is
 * required only when we call asm function from C file.
 */
/* .type asm_strcpy, %function */

asm_strcpy:
	push {r7, lr}
	mov r4, r2

copy_loop:

.ifdef DEBUG
	/* as external function is called in loop, registers has to be pushed to
	 * stack and after return from external function, rgister contents has to be
	 * popped out.
	 */
	push {r0-r7, lr}
	ldr r0, =format_lp
	mov r1, r4
	mov r2,r3
	bl printf
	pop {r0-r7, lr}
.endif
	/* ldr r3, [r1, r5, LSL #2] // r1, base addr will not change
	   str r3, [r0, r5, LSL #2]	// r0, base addr will not change
	   add r5, r5, #1			// with this method additional reg is required
	 */
	ldr r3, [r1], #4
	str r3, [r0], #4
	subs r4,r4,#4
start_loop:
	bne copy_loop
	
	pop {r7, pc}

format_lp: .asciz "%d: %c\n"
