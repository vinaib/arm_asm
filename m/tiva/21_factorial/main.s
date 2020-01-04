	area mymain, code, readonly
	entry								;there should be only one entry in project
	export __main
		
__main
			mov r6, #10			; use higher registers
			mov r7, #1
loop						
			cmp	r6, #0			
			ITTT GT					; 3T's, which means 3 then instructions, there is no else
			mulgt r7, r6, r7
			subgt r6, r6, #1
			bgt loop
stop		b stop

			align
			end