;p = q + r + s
;let q=2, r=4, s=5
q equ 2
r equ 4
s equ 5

stack_size equ 0x00000100
	
	area stack, data, noinit, readwrite, align=3
		
stack_mem space stack_size

	area reset, data, readonly
	export __Vectors
		
__Vectors
	DCD	stack_mem + stack_size
	DCD Reset_Handler

	align
		
	area my_startup, code, readonly
	entry
	export Reset_Handler
		
Reset_Handler
	mov r0,#q
	mov r1,#r 
	mov r2,#s 
	add r3, r0, r1
	add r3, r3, r2
	
stop	b stop
	align
	end



