.data
msg: .asciz "HelloWorld\n"

.text

.globl fact

fact:
	push {r7,lr}
	mov r1, r0
	mov r2, #1
	cmp r1, #0
	bne compute
	mov r0, #1
	b end
compute:
	mul r2,r2,r1
	subs r1,r1,#1
	bne compute
	mov r0,r2
end:
	pop {r7, pc}
	
.globl main

main:
	push {r7, lr}
	mov r0, #5
	bl fact
	pop {r7, pc}
	.size main, .-main
