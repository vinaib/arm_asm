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
	ldr r0, =0xf62562fa		; 32 bit number
	ldr r1, =0xf412963b		; 32 bit number/literal
	
	mov r2, #0x35	;8 bit literal/number
	mov r3, #0x21	; 8 bit number
	
	adds r5, r1, r0	
	adc r6, r2, r3	; adc add with carry r6 = r2 + r3 + carry (carry from previous operation) 
					; and carry flag is not altered it will remain still 1. even current instrucation
					; do not generate carry bit
	adds r6, r2, r3	; 
	
	ldr r2, =0x8000	; not 32 bit number
	ldr r3, =0x8000	; not 32 bit number

	adds r7, r2, r3	; carry bit is only set when top Most significant bit are added and addition generates
					; carry then only carry bit is set. Addition like above numbers (0x8000 + 0x8000 MSB is 0)
					; in other words 0x8000 is 0x00008000.
					
	ldr r2, =0x80000000
	ldr r3, =0x80000000
	
	adds r7, r2, r3		; for this operation carry flag will be set, along with that Z flag is set and also V flag is set
						; r7 = 0x00000000 (result)
	
stop	b stop

	align
	end