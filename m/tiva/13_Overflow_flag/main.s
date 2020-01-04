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
	ldr r1, =1000000000		; 1 arab or 1 billion or 100 crores
	ldr r2, =2000000000		; 2 arab
	ldr r3, =3000000000		; 3 arab
	ldr r4, =4000000000		; 4 arab
	ldr	r5, =4100000000
	
	mov r8, #0				; r8 = 0 for saving the lower word
	mov r9, #0				; r9 - 0 for accumulating the carries
	
	adds r8, r8, r1			; r8 = r8 + r1
	adc r9, r9, #0			; r9 = r9 + 0 + Carry
	
	;for 32 bit signed number the range is from -2000000000 (-2arab) to 
	;+2000000000 (+2 arabs). For unsigned number it is 0 to approx 4 arabs(4294967296)
	;hence values in r1, r2 .. are signed numbers, adding 1arab to 2 arab will result in
	;overflow and also it goes to negative scale
	adds r8, r8, r2			; r8 = r8 + r2
	adc r9, r9, #0			; r9 = r9 + 0 + Carry

	adds r8, r8, r3			; r8 = r8 + r3
	adc r9, r9, #0			; r9 = r9 + 0 + Carry

	adds r8, r8, r4			; r8 = r8 + r4
	adc r9, r9, #0			; r9 = r9 + 0 + Carry

	adds r8, r8, r5			; r8 = r8 + r5
	adc r9, r9, #0			; r9 = r9 + 0 + Carry
	
stop	b stop

	align
	end