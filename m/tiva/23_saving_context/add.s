op1 rn r0
op2 rn r1
res rn r2

	area add_proc, code, readonly
	export add_func
				
add_func	add res, op1, op2
			mov pc, lr
			
			end