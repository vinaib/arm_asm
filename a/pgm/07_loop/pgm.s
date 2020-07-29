.text
.global main
main:
mov r0, #0
mov r1, #1
b check_loop
loop:
add r0, r0, r1
add r1, r1, #1
check_loop:
cmp r1, #22
ble loop
bx lr

