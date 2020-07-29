.data
number_1: .word 0xDEADBEEF

.text
.globl main
main:
	push {r7, lr}

	ldr r0, =format_number
	/* number_1 is in data segment, it has to be accessed indirectly.
	 * this instruction loads address of number_1 to register r1.
	 * if we do "ldr r1, number_1" to load value in number1, assembler gives
	 * error, when we access elements of cross segments.
	 */
	ldr r1, =number_1
	ldr r2, [r1]
	bl printf

	ldr r0, =format_pointer
	/* in same segment, instruction "ldr r1, pointer_to_number1" loads value in
	 * pointer_to_number1 to register r1.
	 * pointer_to_number1 holds address of number1
	 */
	ldr r1, pointer_to_number1
	/* r2 is loaded with number_1*/
	ldr r2, [r1]
	bl printf

	ldr r0, =format_pointer
	/* in same segment, instruction ldr r1, =pointer_to_number1 stores address
	 * of pointer_to_number1 to register r1.
	 */
	ldr r1, =pointer_to_number1
	ldr r2, [r1]
	bl printf

	ldr r0, =format_main
	ldr r1, =main
	ldr r2, [r1]
	bl printf
/*
loop_sleep:
	mov r0,#10
	bl sleep
	bl loop_sleep

*/
	mov r0, #0

	pop {r7, pc}

pointer_to_number1: .word number_1
format_number:	.asciz "DS(number_1): %p(%x)\n"
format_pointer:	.asciz "TS(pointer_to_number1) %p(%x)\n"
format_main:	.asciz "TS(main) %p %x\n"
