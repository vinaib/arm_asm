	area mymain, code, readonly
	entry								;there should be only one entry in project
	export __main
		
__main
			import add_func
			ldr r0, = 2010
			mov r1, #10
			mov r2, #0
again			
			cmp r0, r1
			blo next_op
			subs r0, r0, r1
			add r2, r2, #1
			b again
next_op			
			mov r4, r2
			
			mov r0, #10
			mov r1, #20
			bl add_func
			
stop		b stop

			align
			end