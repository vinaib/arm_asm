@@@ FILE: start.s

    .include "mode.s"

@@@ Stack locations
    @@ uncomment one of the following two lines
    .equ stack_top, 0x10000000 @ Raspberry pi only

    .equ fiq_stack_top, stack_top
    .equ irq_stack_top, stack_top - 0x1000
    .equ abt_stack_top, stack_top - 0x2000
    .equ und_stack_top, stack_top - 0x3000
    .equ mon_stack_top, stack_top - 0x4000
    .equ svc_stack_top, stack_top - 0x5000
    .equ sys_stack_top, stack_top - 0x6000

@@@ -----------------------------------------------------------
@@@ The startup code should be loaded by the boot loader.
@@@ The entry point is _start which performs initialization of
@@@ the hardware, then calls a C function.

    .section .text.boot

    .global _start
    .func _start

_start:         @@ On reset, we should be in SVC mode.

    @@ Switch to FIQ mode with interrupts disabled
    msr CPSR_c,#FIQ_MODE|I_BIT|F_BIT
    ldr sp,=fiq_stack_top       @ set the FIQ stack pointer

    @@ Switch to IRQ mode with interrupts disabled
    msr CPSR_c,#IRQ_MODE|I_BIT|F_BIT
    ldr sp,=irq_stack_top       @ set the IRQ stack pointer

    @@ Switch to ABT mode with interrupts disabled
    msr CPSR_c,#ABT_MODE|I_BIT|F_BIT
    ldr sp,=abt_stack_top       @ set the ABT stack pointer

    @@ Switch to UND mode with interrupts disabled
    msr CPSR_c,#UND_MODE|I_BIT|F_BIT
    ldr sp,=und_stack_top       @ set the UND stack pointer

    @@ Switch to SYS mode with interrupts disabled
    msr CPSR_c,#SYS_MODE|I_BIT|F_BIT
    ldr sp,=sys_stack_top       @ set SYS/USR stack pointer

    @@ Switch to SVC mode with interrupts disabled
    msr CPSR_c,#SVC_MODE|I_BIT|F_BIT
    ldr sp,=svc_stack_top       @ set SVC stack pointer
    @@ Clear the .bss segment to all zeros
    @@ The __bss_start__ and __bss_end__ symbols are
    @@ defined by the linker.
    ldr r1,=__bss_start__   @ load pointer to bss and
    ldr r2,=__bss_end__     @ to byte following bss
    mov r3,#0               @ load fill value (zero)

bssloop:cmp r1,r2           @ Start filling
    bge bssdone
    str r3,[r1],#4
    b bssloop               @ loop until done

bssdone:
    @@ Set up the vector table
    bl setup_vector_table

@@ Call the Main function
    bl main

    @@ If main ever returns, cause an exception
    swi 0xFFFFFF        @ this should never happen
    .size _start, . - _start

    .endfunc

