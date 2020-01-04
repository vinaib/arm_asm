;register renaming, for register renaming rn directive is used
val1 rn r1
val2 rn r2
sum rn r3

;equ directive is used for number literals
num equ 0x344


	area rn_directive, code, readonly
	entry
	export __main
		
__main
		mov val1, #0x25
		mov val2, #0x34
		add sum,val1,val2
stop	b stop
		align
		end