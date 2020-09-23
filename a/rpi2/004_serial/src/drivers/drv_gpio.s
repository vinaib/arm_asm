@@ FILE: drv_gpio.s

    .include "gpio.s"

.section .text

@@ globals
    .global gpio_set_function
    .global gpio_dir_input
    .global gpio_set_pin
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

@@ function: gpio_set_pin
@@ input parameters: 
@@		r0: gpio base
@@		r1: pin_no

	.type gpio_set_pin, %function
    .func gpio_set_pin
gpio_set_pin:
    push {r4-r11, lr} 
    ldr r0, =GPSET0
    ldr r1, [r0]
    mov r2, #1
    orr r1, r1, r2, lsl #24 
    str r1, [r0]
    pop {r4-r11, pc} 
    .endfunc

@@ function: gpio_get_pin
	.type gpio_get_pin, %function
    .func gpio_get_pin
gpio_get_pin:
    push {r4-r11, lr} 

    pop {r4-r11, pc}
    .endfunc

