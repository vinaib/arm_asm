	area mymain, code, readonly
	entry								;there should be only one entry in project
	export __main
		
__main
			ldr r4, =0xbabeface
			ldr r5, =0xdeadbeef
			ldr r6, =0xc0def0de
			ldr r7, =0xfadefeed
			
			stmdb sp!, {r4-r7,lr}
			ldmia sp!, {r4-r7,pc}

stop		b stop

			align
			end