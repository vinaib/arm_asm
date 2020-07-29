/* https://thinkingeek.com/2013/01/11/arm-assembler-raspberry-pi-chapter-3/ */
.data

.balign 4

var1: .word	4
var2: .word 3

.text
.global main

main:
/* ldr r1, myvar1 */		/* indirect way of accessing var1, from code section
							 * we cannot access another section lables. 
							 */

ldr r1,=var1				/* or access var1 which is in data section use
							 * "=var1" 
							 */
ldr r1, [r1]
/* ldr r2, myvar2 */
ldr r2,=var2
ldr r2, [r2]
add r0,r1,r2
bx lr

myvar1: .word var1
myvar2: .word var2
