	area mymain, code, readonly
	entry								;there should be only one entry in project
	export __main
		
__main
			ldr r3, =0xdeadbeef
			ldr r4, =0xbabeface
			push {r3}	;push the contents of r3 to top of stack
			push {r4}	;push the contents of r4 to top of stack
			pop {r5}	;pop top of stack to r5
			pop {r6}	;pop top of stack to r6
stop		b stop

			align
			end