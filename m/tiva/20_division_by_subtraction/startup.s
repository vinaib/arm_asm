stack_size equ 0x00000100
	area my_stack, data, noinit, readwrite, align=3
stackmem	space stack_size


	area reset, data, readonly
			export __Vectors
		
__Vectors
			dcd stackmem + stack_size
			dcd Reset_Handler

	area startup, code, readonly
			
Reset_Handler	proc
				export Reset_Handler
				import __main			;if main defined in same file no need of importing. if we do it gives error
				ldr r0, =__main
				bx r0
				endp

				end