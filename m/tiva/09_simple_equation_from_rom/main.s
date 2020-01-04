stack_size equ 0x00000100
	
	area my_stack, noinit, readwrite, align=3
		
stack_mem space stack_size

	area reset, data, readonly
	export __Vectors

__Vectors
	DCD (stack_mem + stack_size)
	DCD Reset_Handler


	area my_startup, code, readonly
	entry
	export Reset_Handler
		
Reset_Handler
		adrl r0, p
		ldr	r1, [r0,#4]
		ldr r2, [r0,#8]
		add r2, r1, r2
		ldr r1, [r0,#12]
		add r2, r2, r1
	
stop	b stop

	area my_startup, data, readonly
p space 4
q dcd 2
r dcd 4
s dcd 6	
	
	align
	end