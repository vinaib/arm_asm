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
	ldr r2, =0x1000
	ldr r3, =0x2000
	
	add r1, r2, r3
	adc r1, r2, r3
	
	sub r1, r3, r2
	rsb r1, r2, r3
		
stop	b stop

	align
	end