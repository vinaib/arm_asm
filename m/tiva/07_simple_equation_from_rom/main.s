;p = q + r + s
;q = 2 r=4 s=5

stack_size equ 0x00000100

	area my_stack, data, noinit, readwrite, align=3

stack_mem space stack_size
	
	area reset_area, data, readonly
	export __Vectors

__Vectors
	DCD stack_mem + stack_size
	DCD Reset_Handler
		
	align

	area my_pgm_data, data, readonly
	;area my_pgm_data, data, readwrite

p space 4	;reserves 4 bytes of memory
q dcd 2		;creates variable q in memory with initial value 2
r dcd 4
s dcd 5

	area my_code, code, readonly
	entry
	export Reset_Handler
	
Reset_Handler
	ldr r0, q
	ldr r1, r
	ldr r2, s
	add r3, r0, r1
	add r3, r3, r2
	
stop b stop
	align
	end
