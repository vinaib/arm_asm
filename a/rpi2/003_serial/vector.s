    .section .rodata    @ mark this data as read-only
    .align  2

    @@ All of the eight instructions in the vector table are 
    @@ ldr pc,[pc, #24]
    @@ which loads the program counter with the program
    @@ counter + 24. When the pc is used in this addressing
    @@ mode, there is an 8-byte offset because of the 
    @@ pipeline (8+24=32). The address of the corresponding
    @@ handler will be stored 32 bytes after each entry.

Vector_Table:
    ldr pc,[pc, #24]
    ldr pc,[pc, #24]
    ldr pc,[pc, #24]
    ldr pc,[pc, #24]
    ldr pc,[pc, #24]
    ldr pc,[pc, #24]
    ldr pc,[pc, #24]
    ldr pc,[pc, #24]

rh: .word reset_handler
uh: .word undef_handler
sh: .word swi_handler
ph: .word pAbort_handler
dh: .word dAbort_handler
vh: .word reserved_handler
ih: .word irq_handler
fh: .word fiq_handler

    .equ VT_SIZE, (. - Vector_Table)
@@@ --------------------------------------------------------------

    .text
    .align  2
    .global setup_vector_table

setup_vector_table:
    @@ Cortex-A and similar: set the vector base address
    @@ to 0x0. (The boot loader may have changed it.)

    mov r0,#0
    mcr p15,0,r0,c12,c0,0   @ Write VBAR

    @@ This section will copy Vector_Table to address 0x0 
    ldr r0,=Vector_Table @ pointer to table of addresses
    ldr r1,=0x0
    mov r3,#VT_SIZE

movit: 
    ldr r2,[r0],#4
    str r2,[r1],#4
    cmp r1,r3
    blt movit
    mov pc,lr

@ stop after 64 bytes
@ return
