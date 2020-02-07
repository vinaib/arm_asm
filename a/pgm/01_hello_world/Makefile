ASM=as
LD=ld

PREFIX=arm-linux-gnueabihf-

OBJ_32 = pgm_32.o
OBJ_64 = pgm_64.o

%_32.o: %.s 
	$(PREFIX)$(ASM) $< -o $@

exe_32: $(OBJ_32)
	$(PREFIX)$(LD) $^ -o $@

clean:
	rm -rf exe_32 exe_64 *.o
