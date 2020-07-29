# prints relocation details
# arm-linux-gnueabihf-objdump -dr app.o

# display all section size .... and its attributes(Flags), very informative
# Sections:
# Idx Name          Size      VMA       LMA       File off  Algn  Flags
# arm-linux-gnueabihf-objdump -hw exe

# Display only contents of section .got "-j .got"
#arm-linux-gnueabihf-objdump -s -j .got exe

# display only symbol table
#arm-linux-gnueabihf-objdump -t exe

# display only dynamic symbol table
#arm-linux-gnueabihf-objdump -T exe

ASM=as
LD=ld
CC=gcc

PREFIX=arm-linux-gnueabihf-

OBJ = inc_res.o app.o

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
