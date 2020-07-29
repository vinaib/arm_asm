.data

i:		.word 	0
j:		.word	1
fmt:	.asciz	"Hello\n"
ch:		.byte	'A', 'B', 0
ary:	.word	0,1,2,3,4

.text

.global main

main:
	
		bx lr
