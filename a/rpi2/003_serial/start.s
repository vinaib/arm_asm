@@@ FILE: start.s

    .include "mode.s"

@@@ -----------------------------------------------------------
@@@ The startup code should be loaded by the boot loader.
@@@ The entry point is _start which performs initialization of
@@@ the hardware, then calls a C function.
@@@ -----------------------------------------------------------

    .section .text

    .global _start
    .func _start

_start:         @@ On reset, we should be in SVC mode.

@@ Switch to SVC mode with interrupts disabled
    msr CPSR_c,#SVC_MODE|I_BIT|F_BIT

@@ Call the Main function
    bl main

    @@ If main ever returns, cause an exception
    swi 0xFFFFFF        @ this should never happen
    .size _start, . - _start

    .endfunc

