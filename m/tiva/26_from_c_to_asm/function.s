	
	;|.text| directive allows the module to call it from C
	; as per AAPCS [Arm Application Procedural Call Standard]
	; r0 contains return value
	; if we use other register, we will not able to return read value
	
	area |.text|, code, readonly
	export number	;to access this modules from other files it has to be exported
number mov r0, #121
		bx lr
		align
		end
		
		