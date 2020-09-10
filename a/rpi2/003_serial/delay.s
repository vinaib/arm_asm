@@file delay.s

	.globl delay
	.type delay, %function

	.func delay

delay:
	push {lr}
1:	subs r0, r0, #1
	bne 1b
	pop {pc}
	.size delay, . - delay
	.endfunc

