@@@ FILE: main.s

    .global main

main:

    @@ Set the GPIO pins
/*  
    mov r0,#0           @ Port 0
    bl GPIO_dir_output  @ set for output
    mov r0,#1           @ Port 1
    bl GPIO_dir_output  @ set for output
    mov r0,#2           @ Port 2
    bl GPIO_dir_output  @ set for output

    mov r0,#3 @ Port 3
    bl  GPIO_dir_input  @ set for input
    mov r0,#4           @ Port 4
    bl GPIO_dir_input   @ set for input
    mov r0,#5           @ Port 5
    bl  GPIO_dir_input  @ set for input

@@@ Main loop just reads buttons and updates the LEDs.
loop:
    @@ Read the state of the inputs and
    @@ set the ouputs to the same state.
    mov r0,#3           @ Pin 3
    bl GPIO_get_pin     @ read it
    mov r1,r0           @ copy pin state to r1
    mov r0,#0           @ Pin 0
    bl GPIO_set_pin     @ write it

    mov r0,#4 @ Pin 4
    bl GPIO_get_pin     @ read it
    mov r1,r0           @ copy pin state to r1
    mov r0,#1 @ Pin 1
    bl GPIO_set_pin     @ write it

    mov r0,#5 @ Pin 5
    bl GPIO_get_pin     @ read it
    mov r1,r0           @ copy pin state to r1
    mov  r0,#2          @ pin 2
    bl  GPIO_set_pin    @ write it
*/
    bl GPIO_dir_output
loop:
    bl GPIO_set_pin
    b loop 
    ldmfd sp!,{pc}

