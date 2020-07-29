.text

.global main
main:

mov r1, #3
mov r2, #3
cmp r1, r2
beq case_equal		/* if eq jump to case_equal*/
case_different:
mov r0, #5
b end				/* unconditional jump */
case_equal:
mov r0,#4
end:
bx lr

