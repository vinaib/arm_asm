/* Demonstrating stack operations, Following any of instructions can be used
 * which all have same effect. push and pop are not arm instructions, rather
 * they are assembler directive provided by GAS for arm arch. They replace
 * with stmdb sp!, ldmia sp!.
 * stmdb, stmfd, push, str
 * ldmia, ldmfd, pop, ldr
 */

.data 
msg:	.asciz 	"pvh: HelloWorld\n"
msg2:	.asciz	"pvi: Intermediate World\n"
msg1:	.asciz	"pvb: ByeWorld\n"


.text
.globl main

pvh:
	stmdb sp!, {r4-r11,lr}	
	ldr r0, =msg
	bl printf
	bl pvi
	ldmia sp!, {r4-r11,lr}
	bx lr						/* control goes back to calling function, if
								   this instruction does not there then it will
								   continue with main and again call pvh, then
								   main and continues till stack explodes
								*/

pvi:
	str lr, [sp, #-4]!
	ldr r0, =msg2
	bl printf
	bl pvb
	ldr lr, [sp], #+4
	bx lr

main:
	push {r4-r11,lr}
	bl pvh
	pop {r4-r11,lr}
	bx lr

pvb:
	stmfd sp!, {r4-r11,lr}
	ldr r0, =msg1
	bl printf
	ldmfd sp!, {r4-r11,lr}
	bx lr

