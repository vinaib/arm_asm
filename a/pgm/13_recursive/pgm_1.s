.data
int_fmt: .asciz "%d\n"

.text
.globl main

factorial:
	push {r4, lr}
	mov r4, r0

	cmp r0, #1
	bne is_non_zero
	mov r0,#1
	b end

is_non_zero:
	sub r0, r0, #1
	bl factorial

	mov r0, r4
	mul r0, r0, r1
	
	mov r1, r0
	ldr r0, =int_fmt
	bl printf

	mov r0,r1

end:
	pop {r4, lr}
	bx lr

main:
	push {lr}
	mov r0, #5
	mov r4, r0
	bl factorial
	pop {lr}
	bx lr
