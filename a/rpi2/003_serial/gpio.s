@@@ FILE: gpio.s

	.equ	PERIPHERAL_BASE,	0x3F000000
	.equ	GPIO_BASE,			0x00200000

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
	

    @@@ GPIO Function Select
    @@@ 000 = GPIO Pin as an input
    @@@ 001 = GPIO Pin as an output
    @@@ 100 = GPIO Pin takes alternate function 0
    @@@ 101 = GPIO Pin takes alternate function 1
    @@@ 110 = GPIO Pin takes alternate function 2
    @@@ 111 = GPIO Pin takes alternate function 3
    @@@ 011 = GPIO Pin takes alternate function 4
    @@@ 010 = GPIO Pin takes alternate function 5
    @@@ 3 bits: for each pin, 30:31 are reserved
	.equ	GPIO_AS_INPUT,		0x0
	.equ	GPIO_AS_OUTPUT,		0x1
	.equ	GPIO_ALT_FUNC_0,	0x4
	.equ	GPIO_ALT_FUNC_1,	0x5
	.equ	GPIO_ALT_FUNC_2,	0x6
	.equ	GPIO_ALT_FUNC_3,	0x7
	.equ	GPIO_ALT_FUNC_4,	0x3
	.equ	GPIO_ALT_FUNC_5,	0x2

    @@@ each register configures 10 pins
    @@@ SEL0: PIN0 - PIN9
    @@@ SEL1: PIN10 - PIN19
    @@@ SEL2: PIN20 - PIN29
    @@@ SEL3: PIN30 - PIN39
    @@@ SEL4: PIN40 - PIN49
    @@@ SEL5: PIN50 - PIN53 [31:12] Reserved
    .equ    GPFSEL0,    0x3F200000    
    .equ    GPFSEL1,    0x3F200004
    .equ    GPFSEL2,    0x3F200008
    .equ    GPFSEL3,    0x3F20000C
    .equ    GPFSEL4,    0x3F200010
    .equ    GPFSEL5,    0x3F200014
    @@@ GPIO Pin output set registers
    .equ    GPSET0, 0x3F20001C      @@ PIN 0 -  PIN 31
    .equ    GPSET1, 0x3F200020      @@ PIN 32 - PIN 53
    @@@ GPIO Pin Output Clear
    .equ    GPCLR0, 0x3F200028      @@ PIN 0 -  PIN 31  
    .equ    GPCLR1, 0x3F20002C      @@ PIN 32 - PIN 53
    @@@ GPIO Pin Level
    .equ    GPLEV0, 0x3F200034      @@ PIN 0 -  PIN 31  
    .equ    GPLEV1, 0x3F200038      @@ PIN 32 - PIN 53
    @@@ GPIO Pin Event Detect Status
    .equ    GPEDS0, 0x3F200040      @@ PIN 0 -  PIN 31  
    .equ    GPEDS1, 0x3F200044      @@ PIN 32 - PIN 53
    @@@ GPIO Pin Rising Edge Detect Enable
    .equ    GPREN0, 0x3F20004C      @@ PIN 0 -  PIN 31  
    .equ    GPREN1, 0x3F200050      @@ PIN 32 - PIN 53
    @@@ GPIO Pin Falling Edge Detect Enable
    .equ    GPFEN0, 0x3F200058      @@ PIN 0 -  PIN 31  
    .equ    GPFEN1, 0x3F20005C      @@ PIN 32 - PIN 53
    @@@ GPIO Pin High Detect Enable
    .equ    GPHEN0, 0x3F200064      @@ PIN 0 -  PIN 31  
    .equ    GPHEN1, 0x3F200068      @@ PIN 32 - PIN 53
    @@@ GPIO Pin Low Detect Enable
    .equ    GPLEN0, 0x3F200070      @@ PIN 0 -  PIN 31  
    .equ    GPLEN1, 0x3F200074      @@ PIN 32 - PIN 53
    @@@ GPIO Pin Async. Rising Edge Detect
    .equ    GPAREN0, 0x3F20007C     @@ PIN 0 -  PIN 31  
    .equ    GPAREN1, 0x3F200080     @@ PIN 32 - PIN 53
    @@@ GPIO Pin Async. Falling Edge Detect
    .equ    GPAFEN0, 0x3F200088     @@ PIN 0 -  PIN 31
    .equ    GPAFEN1, 0x3F20008C     @@ PIN 32 - PIN 53
    @@@ GPIO Pin Pull-up/down Enable
    @@@ [31 - 2] unused
    @@@ [1 - 0] PUD
    @@@ 00 = disable Pull up/down
    @@@ 01 = Enable pull down
    @@@ 10 = Enable pull up
    @@@ 11 = Reserved
    .equ    GPPUD, 0x3F200094
    @@@ GPIO Pin Pull-up/down Enable Clock
    .equ    GPPUDCLK0, 0x3F200098
    .equ    GPPUDCLK1, 0x3F20009C   @@ PIN 32 - PIN 53

