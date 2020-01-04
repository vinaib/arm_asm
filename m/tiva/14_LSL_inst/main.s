stack_size equ 0x00000100
	
	area my_stack, data, noinit, readwrite, align=3
		
stackmem	space stack_size


	area reset, data, readonly
	export __Vectors
		
__Vectors
	dcd stackmem + stack_size
	dcd Reset_Handler
		

	area startup, code, readonly
	entry
	export Reset_Handler
		
Reset_Handler
	mov r0, #0x11
	lsl r1, r0, #1
	
	mov r2, #2
	lsl r1, r1, r2
 	
stop	b stop

	align
	end