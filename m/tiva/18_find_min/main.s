data_pointer	rn 	r0
data_1			rn  r1
data_2			rn  r2
counter			rn  r3
min				rn  r4


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
	mov counter, #8
	ldr data_pointer, =signdata
	ldrsb data_1, [data_pointer]

loop
	add data_pointer, data_pointer, #1
	ldrsb data_2, [data_pointer]
	cmp data_2, data_1
	bge next
	mov data_1, data_2
	
next
	subs counter, counter, #1
	bne loop

stop	b stop

signdata dcb	+13, -10, +19, +14, -18, -9, +12, -100

	align
	end