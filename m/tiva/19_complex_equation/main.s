;(A + 8B + 7C - 27)/4
; Let A = 25, B = 19, C = 99

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
	mov r0, #25
	mov r1, #19
	add r0, r0, r1, LSL #3
	mov	r1, #99
	mov r2, #7
	mla r0, r1, r2, r0	;add 7c to r0 put result in r0
	sub r0, r0, #27
	mov r0, r0, ASR #2 	;divide the toal by 4
	
stop	b stop

signdata dcb	+13, -10, +19, +14, -18, -9, +12, -100

	align
	end