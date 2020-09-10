@@ FILE: drv_gpio.s

@@ .include "gpio.s"

.section .text

@@ globals
    .global gpio_set_function
    .global gpio_dir_input
    .global gpio_set_clear_output
    .global gpio_get_pin

@@ function: gpio_set_function
@@ input parameters: 
@@		r0: gpio base
@@ 		r1: pin_no
@@		r2: function
@@ Notes:
@@ Find out GPFSELn register based on pin number
@@ each register configures 10 pins, each pin 3bits wide
@@ [30-31] unused pins
@@ hardcoding to gpio24
@@ gpio_set_function(gpio_base, pin_no, function)

	.type gpio_set_function, %function
    .func gpio_set_function
gpio_set_function:
    push {r4-r11, lr} 
	lsl r4, r1, #1				
	add r4, r4, r1				@@ r4 = r1 * 3
	lsl r2, r2, r4				@@ r1 = r1 << r4
	ldr r4, [r0]
	orr r4, r4, r2
    str r2, [r0]
    pop {r4-r11, pc} 
    .endfunc

@@ function: gpio_dir_input

	.type gpio_dir_input, %function
    .func gpio_dir_input
gpio_dir_input:
    push {r4-r11, lr} 

    pop {r4-r11, pc} 
    .endfunc

@@ function: gpio_set_clear_output
@@ input parameters: 
@@		r0: gpio base
@@		r1: pin_no
@@ notes:

	.type gpio_set_clear_output, %function
    .func gpio_set_clear_output
gpio_set_clear_output:
    push {r4-r11, lr}
	ldr r2, [r0]
	mov r3, #1
	orr r2, r2, r3, lsl r1
	str r2, [r0]
    pop {r4-r11, pc}
	.size gpio_set_clear_output, . - gpio_set_clear_output
    .endfunc

@@ function: gpio_get_pin
	.type gpio_get_pin, %function
    .func gpio_get_pin
gpio_get_pin:
    push {r4-r11, lr} 

    pop {r4-r11, pc}
    .endfunc

