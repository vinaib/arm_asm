ASM=as
LD=ld
CC=gcc

PREFIX=arm-linux-gnueabihf-

OBJ = pgm.o

%.o: %.s 
	$(PREFIX)$(ASM) $< -o $@ -march=armv6

#$(PREFIX)$(LD) $^ -o $@
exe: $(OBJ)
	$(PREFIX)$(CC) -o $@ $^
	cp exe /var/lib/tftpboot

clean:
	rm -rf exe *.o
