stack_size	equ 0x00000100		;define stack size of 256 bytes
	
		area STACK, noinit, readwrite, align=3
			
stackmem space stack_size

		area reset, data, readonly
		export __Vectors
		
__Vectors
		dcd stackmem + stack_size
		dcd Reset_Handler
		align
			
		area my_proj, code, readonly, align=2
		entry
		export Reset_Handler

Reset_Handler
		mov r0, #-1
		mov r1, #-2
		adds r2,r0,r1
		
		mov r0, #2
		mov r1, #1
		subs r2, r0, r1
		
		movw r0, #0x0000
		movt r0, #0x7b00
		
		movw r1, #0x0000
		movt r1, #0x3000
		
		adds r3, r0, r1
		
		ldr r0, =0x7b000000
		ldr r1, =0x30000000
		adds r2, r0, r1
		
stop	b stop
		align
		end