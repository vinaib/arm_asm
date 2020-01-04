ram1_addr equ 0x20000000
ram2_addr equ 0x20000100	
feed_babe equ 0xfeedbabe	

;mov r0, =ram1_addr ;wrong
;ldr r0,=ram1_addr	;correct

;ldr r1, =ram1_addr	;correct

;mov r2, #0xdeadbeef	;wrong
;mov r2,#0xff			;correct
	
;ldr r3, #0xfeedbabe	;wrong
;ldr r3, =feed_babe		;correct
;ldr r3, =0xfeedbabe


	area my_copy, code, readonly
	entry
	export __main

__main
	bl fill
	bl copy
	
stop b stop

fill	
	;ldr r0, =ram1_addr
	mov r0,#0x20000000
	ldr r1, =0xfeedbabe
	;mov r1, #0xfeedbabe
	movw r1, #0xbeef
	movt r1, #0xdead
	mov r3, #10
	
LOOP1	str r1, [r0]
		add r0, r0, #4
		subs r3,r3,#1
		bne LOOP1

	;bx lr
	mov pc,lr
	
copy
	ldr r0, =ram1_addr
	ldr r1, =ram2_addr
	mov r3, #10

LOOP2	ldr r2, [r0]
		str r2, [r1]
		add r0, r0, #4
		add r1, r1, #4
		subs r3,r3,#1
		BNE LOOP2
	
	;bx lr
	mov pc,lr

	align
	end