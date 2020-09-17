@@ FILE: serial.s

@@ Serial Debug pins
@@ GPIO14: TXD0	ALT0
@@ GPIO15: RXD0	ALT0
@@ GPIO32: TXD0 ALT3
@@ GPIO33: RXD0 ALT3
@@ GPIO36: TXD0 ALT2(Pull High)
@@ GPIO37: RXD0 ALT2
@@
@@ GPIO16,GPIO30: CTS0 ALT3
@@ GPIO17,GPIO31: RTS0 ALT3
@@ GPIO38: RTS0, ALT2
@@ GPIO39: CTS0, ALT2

@@ Correction:
@@ In BCM28355 ARM Peripherals.docx it is printed as 0x7E20100.
@@ The correct one is PL011 USRT base address 0x7E201000.
@@ ARM space: 0x3F201000
@@ Older boards: 0x2E201000

@@ FIFO Memory
@@ TX: 16 x 8
@@ RX: 16 x 12

@@ std asynchronous communication bits
@@ STOP, START, PARITY: added on transmission, removed on reception

@@ False start bit detection?

@@ Line break generation and detection?


	.equ	UART_BASE		0x3F201000

	.equ	UART_DR			0x00		@@ DATA REG
	.equ	UART_RSRECR		0x04		@@ RECEIEVE STATUS/ERROR CLEAR REG
	.equ	UART_FR			0x18		@@ FLAG REG
	.equ	UART_ILPR		0x20		@@ NOT IN USE
	.equ	UART_IBRD		0x24		@@ INTEGER BAUD RATE DIVISOR
	.equ	UART_FBRD		0X28		@@ FRACTIONAL BAUD RATE DIVISOR
	.equ	UART_LCRH		0X2C		@@ LINE CONTROL REG
	.equ	UART_CR			0X30		@@ CONTROL REG
	.equ	UART_IFLS		0X34		@@ INTR FIFO LEVEL SELECT REG
	.equ	UART_IMSC		0X38		@@ INTR MASK SET CLR REG
	.equ	UART_RIS		0X3C		@@ RAW INTR STATUS REG
	.equ	UART_MIS		0X40		@@ MASKED INTR STATUS REG
	.equ	UART_ICR		0X44		@@ INTR CLR REG
	.equ	UART_DMACR		0X48		@@ DMA CONTROL REG
	.equ	UART_ITCR		0X80		@@ TEST CONTROL REG
	.equ	UART_ITIP		0X84		@@ INTEGRATION TEST INPUT REG
	.equ	UART_ITOP		0X88		@@ INTEGRATION TEST OUTPUT REG
	.equ	UART_TDR		0X8C		@@ TEST DATA REG

	.equ	DR_MASK_DATA	0x000000FF		@@ DATA BYTE
	@@ bits of data register: frame error
	@@ When set to 1, it indicates that the received character did
	@@ not have a valid stop bit
	.equ	UART_DR_BIT_FE		(1<<8)		@@ FRAME ERROR
	.equ	UART_DR_BIT_PE		(1<<9)		@@ PARITY ERROR
	.equ	UART_DR_BIT_BE		(1<<10)		@@ BREAK ERROR
	.equ	UART_DR_BIT_OE		(1<<11)		@@ OVERRUN ERROR

	@@ Bits of flag register
	.equ	UART_FR_BIT_RI		(1<<8)		@@ Ring Indicator
	.equ	UART_FR_BIT_TXFE	(1<<7)		@@ TXFIFO Empty
	.equ	UART_FR_BIT_RXFF	(1<<6)		@@ RX FIFO Full
	.equ 	UART_FR_BIT_TXFF	(1<<5)		@@ TX FIFO Full
	.equ	UART_FR_BIT_RXFE	(1<<4)		@@ RX FIFO Empty
	.equ	UART_FR_BIT_BUSY	(1<<3)		@@ UART is busy
	.equ	UART_FR_BIT_DCD		(1<<2)		@@ unsupported, data carrier detect
	.equ	UART_FR_BIT_DSR		(1<<1)		@@ unsupported, data sense/set ready
	.equ	UART_FR_BIT_CTS		(1<<0)		@@ clear to send

	@@ Bits of line control register
	.equ	UART_LCRH_BIT_SPS	(1<<7)		@@ enable stick parity
	.equ	UART_LCRH_BIT_WLEN1	(1<<6)		@@ msb of word length
	.equ	UART_LCRH_BIT_WLEN0	(1<<5)		@@ lsb of word length
	.equ	UART_LCRH_BIT_FEN	(1<<4)		@@ enable fifo's
	.equ	UART_LCRH_BIT_STP2	(1<<3)		@@ use 2 stop bits
	.equ	UART_LCRH_BIT_EPS	(1<<2)		@@ even parity select
	.equ	UART_LCRH_BIT_PEN	(1<<1)		@@ enable parity
	.equ	UART_LCRH_BIT_BRK	(1<<0)		@@ send break

	@@ Bits of contorl register
	.equ	UART_CR_BIT_CTSEN	(1<<15)		@@ Enable CTS
	.equ	UART_CR_BIT_RTSEN	(1<<14)		@@ Enable RTS
	.equ	UART_CR_BIT_OUT2	(1<<13)		@@ unsupported
	.equ	UART_CR_BIT_OUT1	(1<<12)		@@ unsupported
	.equ	UART_CR_BIT_RTS		(1<<11)		@@ request to send
	.equ	UART_CR_BIT_DTR		(1<<10)		@@ unsupported
	.equ	UART_CR_BIT_RXE		(1<<9)		@@ enable receiver
	.equ	UART_CR_BIT_TXE		(1<<8)		@@ enable transimitter
	.equ	UART_CR_BIT_LBE		(1<<7)		@@ enable loopback
	.equ	UART_CR_BIT_SIRLP	(1<<2)		@@ unsupported
	.equ	UART_CR_BIT_SIREN	(1<<1)		@@ unsupported
	.equ	UART_CR_BIT_UARTEN	(1<<0)		@@ enable uart

