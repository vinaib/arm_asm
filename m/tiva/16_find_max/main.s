count 	rn 	r0
max		rn  r1
pointer rn	r2
next	rn	r3

stack_size equ 0x00000100
	
	area my_stack, data, noinit, readwrite, align=3
		
stackmem	space stack_size

	area my_data, data, readonly
mydata dcd	69,87,86,45,75		

	area reset, data, readonly
	export __Vectors
		
__Vectors
	dcd stackmem + stack_size
	dcd Reset_Handler
		

	area startup, code, readonly
	entry
	export Reset_Handler
		
Reset_Handler
		mov count, #5
		mov max, #0
		ldr pointer, =mydata
	
again
		ldr next, [pointer]
		cmp max, next
		bhs ctnu
		mov max, next
	
ctnu	
		add pointer, pointer, #4
		subs count, count, #1
		bne again

stop	b stop

	align
	end