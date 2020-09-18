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
	@@ set baud rate divisor using formula:
	@@ (3000000/(r0 x 16)) 
	lsl r1, r0,#4			@@ r1 = desired baud * 16
	ldr r0, =(3000000<<6)	@@ load 3Mhz as a U(26.6) in r0
	bl divide				@@ divide clk freq by (baud x 16)
	asr r1, r0, #6			@@ put integer divisor into r1
	and r0, r0, #0x3f		@@ put fractional divisor into r0
	ldr r2, =UART_BASE
	ldr r2, [r2]
	str r1, [r2, #UART_IBRD]	@@ set integer divisor
	str r0, [r2, #UART_FBRD]	@@ set fractional divisor
	pop {r4-r11, pc}
	.endfunc


@@ function: uart_put_byte
@@ input_parameters:
@@ r0: input byte
@@ notes:
	.type uart_put_byte, %function
	.func uart_put_byte
uart_put_byte:
	push {r4-r11, lr}
	ldr r1, =UART_BASE
	ldr r1, [r1]
1:	ldr r2, [r1, #UART_FR]
	tst r2, #UART_FR_BIT_TXFF
	bne 1b
	str r0, [r1, #UART_DR]
	pop {r4-r11, pc}
	.endfunc


@@ function: uart_get_byte
@@ input_parameters:
@@ notes:
	.type uart_get_byte, %function
	.func uart_get_byte
uart_get_byte:
	push {r4-r11, lr}
	ldr r1, =UART_BASE
	ldr r1, [r1]
1:	ldr r2, [r1, #UART_FR]
	tst r2, #UART_RXFE
	bne 1b
	ldr r0, [r1, #UART_DR]
	@@ check for overrun error
	tst r0, #UART_DR_BIT_OE
	bne get_ok1
	@@ write code to handle overrun error
	@@ check for break error
get_ok1: tst r0, #UART_DR_BIT_BE
	bne get_ok2
	@@ write code to handle break error
	@@ check for parity error
get_ok2: tst r0, #UART_DR_BIT_PE
	bne get_ok3
	@@ write code to handle parity error
	@@ check for frame error
get_ok3: tst r0, #UART_DR_BIT FE
	bne get_ok4
	@@ write code to handle frame error
get_ok4:
	@@ successfull return
	pop {r4-r11, pc}
	.endfunc
