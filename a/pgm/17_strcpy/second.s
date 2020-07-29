.section .data

.section .text
.globl asm_wrapper

/* with out this line, on calling this function it says an illegal instruction.
 * This line looks like mandatory when you call assemlby function from c file.
 * Can it be called from other asm file?
 */
.type asm_wrapper, %function

asm_wrapper:

	push {r7, lr}
	bl asm_strcpy
	mov r0, #0
	pop {r7, pc}
