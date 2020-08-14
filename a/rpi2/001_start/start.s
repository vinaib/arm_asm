.equ GPFSEL2, 	0x3F200008
.equ GPSET0,	0x3F20001C
.equ GPCLR0,	0x3F200028

.section .text

.globl _start

_start:
	b vin

/* ENTRY(main)*/
.globl vin
.align 4
vin:

/*ENDPROC(main)*/
	/* set gpio output*/
	ldr r0, =GPFSEL2
	ldr r1, [r0]
	mov r2, #1
	orr r1, r1, r2, lsl #12
	str r1, [r0]					@ dsb sy

loop: 
	ldr r0, =GPSET0
	ldr r1, [r0]
	mov r2, #1
	orr r1, r1, r2, lsl #24			@ On
	str r1, [r0]					@ dsb sy

	mov r3, #1048576				@orr r3, r3, r2, lsl #24
1:	
	subs r3, r3, #1
	bne 1b

	ldr r0, =GPCLR0
	ldr r1, [r0]
	mov r2, #1
	orr r1, r1, r2, lsl #24			@ off
	str r1, [r0]

	mov r3, #1048576				@orr r3, r3, r2, lsl #24
2:	
	subs r3, r3, #1
	bne 2b

	b loop

.type vin, %function
.size vin, .-vin
