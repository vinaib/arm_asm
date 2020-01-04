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
		mov r5,#0x1234
		mov r3,#0x1234
		add r6,r5,r3
stop	b stop
		align
		end