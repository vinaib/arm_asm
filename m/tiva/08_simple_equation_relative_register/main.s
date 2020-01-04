;p = q++r+s
;q=2 r=4 s=5		
		area my_code, code, readonly
		entry
		export __main

__main
		;ldr	r4, =Vals
		adrl	r4, Vals
		ldr 	r1, [r4, #q]
		ldr 	r2, [r4, #r]
		ldr 	r3, [r4, #s]
	
		add 	r0, r1, r2
		add 	r0, r0, r3
		
		str 	r0, [r4, #p]
	
stop 	b 		stop

p 		equ 	0
q 		equ 	4
r 		equ 	8
s 		equ 	12

		area my_code, data, readwrite
		
Vals	space 	4
		dcd 	2
		dcd 	4
		dcd 	5
		align	

		align
		
		end
	


