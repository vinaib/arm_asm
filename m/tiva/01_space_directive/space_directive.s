
	area first_pgm, code, readonly	
	;area keyword has to start after one tab, otherwise assembler throws error
	entry
	export __main
		
__main
	ldr r0, =a
	mov r1, #5
	str r1,[r0]
	
	ldr r0,=c
	mov r1,#9
	str r1,[r0]
	
	ldr r0,=d
	mov r1,#100
	str r1,[r0]
	
stop	b stop

	area first_data, data, readwrite
	;Allocate space in SRAM memory
a 	space 4
c 	space 4
d 	space 4
		
	end		
			