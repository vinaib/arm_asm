@@@ FILE: main.s

	.include "gpio.s"

    .global main

	.type main, %function
	.func main

main:
	
	/* set gpio24 as output */
	ldr r0, =GPFSEL2
	ldr r1, =PIN_4
	ldr r2, =GPIO_AS_OUTPUT
	bl gpio_set_function

	
1:	
	ldr r0, =GPSET0
	mov r1, #24
	bl gpio_set_clear_output

	mov r0, #1048576
	bl delay
	
	ldr r0, =GPCLR0
	mov r1, #24
	bl gpio_set_clear_output

	mov r0, #1048576
	bl delay

	b 1b

	.size _main, . - main

	.endfunc
