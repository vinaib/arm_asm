	area |.text|, code, readonly

	import adder
	import num
	export __main
	entry
	
__main
		ldr r1, =num
		mov r0,#100
		str r0, [r1]
		bl adder
		
stop	b stop
		end
		