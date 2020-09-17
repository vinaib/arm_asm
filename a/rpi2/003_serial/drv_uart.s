@ File drv_serial.s

	.include "serial.s"

	.text 

@@ globals
	.globl uart_init
	.globl uart_set_baud
	.globl uart_put_byte
	.globl uart_get_byte

@@ function: uart_init
@@ input_parameters:
@@ notes:
	.type uart_init, %function
	.func uart_init
uart_init:
	push {r4-r11, lr}
	ldr r1, =UART_BASE	@ load address of macro into r1
	ldr r1, [r1]		@ load value stored at r1 into r1

	@@ set baud rate divisor
	@@ (3MHz / (115200 * 16)) = 1.6276041667
	@@ = 1.101000 in binary
	mov r0, #1
	str r0,[r1, #UART_IBRD]
	mov r0, #0x28
	str r0, [r1, #UART_FBRD]

	@@ set parity, word len, enable fifos
	.equ BITS, (UART_LRCH_BIT_WLEN1|UART_LRCH_BIT_WLEN0|UART_LRCH_BIT_STP2)
	mov r0, #BITS
	str r0, [r1, #UART_LRCH]

	@@ mask all UART interrupts
	mov r0, #0
	str r0, [r1, #UART_IMSC]

	@@ enable tx | rx | uart bits in CR
	.equ FINALBITS, (UART_CR_BIT_TXE | UART_CR_BIT_RXE | UART_CR_BIT_UARTEN)
	ldr r0, =FINALBITS
	str r0, [r1, #UART_CR]

	pop {r4-r11, pc}
	.endfunc

@@ function: uart_set_baud
@@ input_parameters:
@@ notes:
	.type uart_set_baud, %function
	.func uart_set_baud
uart_set_baud:
	push {r4-r11, lr}
	
	pop {r4-r11, pc}
	.endfunc


@@ function: uart_put_byte
@@ input_parameters:
@@ notes:
	.type uart_put_byte, %function
	.func uart_put_byte
uart_put_byte:
	push {r4-r11, lr}
	
	pop {r4-r11, pc}
	.endfunc


@@ function: uart_get_byte
@@ input_parameters:
@@ notes:
	.type uart_get_byte, %function
	.func uart_get_byte
uart_get_byte:
	push {r4-r11, lr}
	
	pop {r4-r11, pc}
	.endfunc
