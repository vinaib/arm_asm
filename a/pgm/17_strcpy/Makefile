ASM=as
LD=ld
CC=gcc

PREFIX=arm-linux-gnueabihf-

OBJ = second.o pgm.o app.o

%.o: %.s 
	$(PREFIX)$(ASM) -g $< -o $@

%.o: %.c
	$(PREFIX)$(CC) -g -c $< -o $@

#$(PREFIX)$(LD) $^ -o $@
exe: $(OBJ)
	$(PREFIX)$(CC) -g -o $@ $^
	cp exe /var/lib/tftpboot

clean:
	rm -rf exe *.o
