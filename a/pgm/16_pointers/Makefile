ASM=as
LD=ld
CC=gcc

PREFIX=arm-linux-gnueabihf-

OBJ = pgm.o

%.o: %.s 
	$(PREFIX)$(ASM) -g $< -o $@

#$(PREFIX)$(LD) $^ -o $@
exe: $(OBJ)
	$(PREFIX)$(CC) -g -o $@ $^
	cp exe /var/lib/tftpboot

clean:
	rm -rf exe *.o
