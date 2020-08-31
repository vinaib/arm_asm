.equ GPFSEL2, 	0x3F200008
.equ GPSET0,	0x3F20001C
.equ GPCLR0,	0x3F200028

.equ    GPIO_AS_OUTPUT,     0x1

.equ	PIN_0,	0
.equ	PIN_1,	1
.equ	PIN_2,	2
.equ	PIN_3,	3
.equ	PIN_4,	4
.equ	PIN_5,	5
.equ	PIN_6,	6
.equ	PIN_7,	7
.equ	PIN_8,	8
.equ	PIN_9,	9

.equ stack_top, 0x10000000

.equ SYS_MODE, 0x1F 
.equ I_BIT, 0x80
.equ F_BIT, 0x40

.section .text

.globl _start
.globl gpio_set_function
.globl gpio_set_unset_output
.globl delay

_start:
	@@ initialize stack and disable irq and fiq
	@@ with out initializing stacks too function call works
	@@ then what would be the default sp value?
	@msr CPSR_c,#SYS_MODE|I_BIT|F_BIT
	@ldr sp,=stack_top

	b vin

/* ENTRY(main)*/
.globl vin
.align 4
vin:

/*ENDPROC(main)*/
	/* gpio 24 as output*/
	ldr r0, =GPFSEL2
	ldr r1, =PIN_4
	ldr r2, =GPIO_AS_OUTPUT
	bl gpio_set_function

loop: 
	ldr r0, =GPSET0
	mov r1, #24
	bl gpio_set_unset_output

	mov r0, #5242880
	bl delay

	ldr r0, =GPCLR0
	mov r1, #24
	bl gpio_set_unset_output

	mov r0, #1048576
	bl delay

	b loop

.type vin, %function
.size vin, .-vin

@@ function: gpio_set_function
@@ input parameters:
@@ 	r0:	base register
@@	r1: pin_no
@@  r2: function

	.type gpio_set_function, %function
gpio_set_function:
	push {r4-r11, lr}
    lsl r4, r1, #1
    add r4, r4, r1              @@ r4 = r1 * 3
    lsl r2, r2, r4              @@ r1 = r1 << r4
	ldr r4, [r0]
	orr r4, r4, r2
    str r2, [r0]
	pop {r4-r11, pc}

@@ function: gpio_set_unset_output
@@ input parameters:
@@ 	r0: base register
@@	r1: pin no

.type gpio_set_unset_output, %function
gpio_set_unset_output:
	push {r4-r11, lr}
	ldr r2, [r0]
	mov r3, #1
	@@ lsl r1, r3, r1
	@@ orr r2, r2, r1
	orr r2, r2, r3, lsl r1
	str r2, [r0]
	pop {r4-r11, pc}

@@ function: delay
@@ input parameters:
@@ 	r0: counter

.type delay, %function
delay:
	push {r4-r11, lr}
1:	subs r0, r0, #1
	bne 1b
	pop {r4-r11, pc}

