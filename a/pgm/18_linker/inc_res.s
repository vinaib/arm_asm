.text

.globl incr_res

incr_res:
	push {r4,r5,fp,lr}
	ldr r0, addr_of_res
	ldr r0, [r0]
	add r0, r0, #1
	pop {r4,r5,fp,lr}
	
addr_of_res:	.word result
