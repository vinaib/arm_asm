.data

.align 4

first:	.word 64
second:	.word 46

.global result
result:	.word 0

.text

.global main

main:
	push {r4, r5, fp, lr}

	ldr r0, addr_of_first
	ldr r0, [r0]

	ldr r1, addr_of_second
	ldr r1, [r1]

	ldr r2, addr_of_result
	ldr r2, [r2]

	add r2, r0, r1

	bl incr_res
	
	mov r0, r2

	pop {r4, r5, fp, pc}

addr_of_first:	.word first
addr_of_second:	.word second
addr_of_result:	.word result


