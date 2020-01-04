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
	mov r2, #4
	mov r3, #2
	mov r4, #4
	
	subs r5, r2, r3		;r5 4 - 2 = 2 C carry flag is set
	subs r5, r2, r4		;r5 4 - 4 = 0 z zero flag is set
	subs r5, r3, r4		;r5 2 - 4 = 0xfffffffe(-2) N negative flag is set
	
stop	b stop

	align
	end