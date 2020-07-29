	.text
	.global main

main:	
	mov r0, #2	/* on shell type echo $? to see error code, it should show 2*/
	bx lr


