		area swap, code, readonly
		entry
		export __main		
__main
		ldr	r0,=0xbabeface
		ldr r1,=0xdeadbeef
		
		eor r0,r0,r1
		eor r1,r0,r1
		eor r0,r0,r1
	
stop 	b stop
		;to stop 0x2 bytes pad warning
		align		
		end
		