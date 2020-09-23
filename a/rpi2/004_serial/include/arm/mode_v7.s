@@@ FILE: mode_v7.s
@@@ Definitions of mode field and interrupt bits in CPSR
    .equ I_BIT, 0x80        @ when I=1 IRQ is disabled
    .equ F_BIT, 0x40        @ when F=1 FIQ is disabled
    .equ IF_BITS, 0xC0      @ both IRQ, FIQ set 

    .equ USR_MODE, 0x10     @ shares sp,lr,CPSR with sys mode
    .equ FIQ_MODE, 0x11     @ fiq mode all interrupts masked
    .equ IRQ_MODE, 0x12     @ irq mode all interrupts masked
    .equ SVC_MODE, 0x13
    .equ ABT_MODE, 0x17
    .equ UND_MODE, 0x1B
    .equ SYS_MODE, 0x1F     @ shares sp,lr,CPSR with usr mode

