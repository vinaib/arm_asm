data_pointer	rn 	r0
data			rn  r1
counter			rn  r2
sum				rn	r3

stack_size equ 0x00000100
	
	area my_stack, data, noinit, readwrite, align=3
stackmem	space stack_size

	;area my_data, data, readonly
;signdata dcb	+13, -10, +9, +14, -18, -9, +12, -19, +16

	area reset, data, readonly
	export __Vectors
		
__Vectors
	dcd stackmem + stack_size
	dcd Reset_Handler
		
	area startup, code, readonly
	entry
	export Reset_Handler
		
Reset_Handler
	ldr data_pointer, =signdata
	mov counter, #9
	mov sum, #0
	
loop	
	ldrsb data, [data_pointer]
	add sum, sum, data
	add data_pointer, data_pointer, #1
	subs counter, counter, #1
	bne loop

stop	b stop

signdata dcb	+13, -10, +9, +14, -18, -9, +12, -19, +16

	align
	end