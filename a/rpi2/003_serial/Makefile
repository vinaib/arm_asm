PREFIX=arm-linux-gnueabihf-
LD=ld
CC=gcc
AS=as
OBJCOPY=objcopy
MKIMAGE=mkimage
RM=rm
OPT=
GCC_OPT=-O0
LOAD_ADDRESS=00008000

# source files
SOURCES_ASM := start.s main.s drv_gpio.s delay.s

# object files
OBJS 		:= $(patsubst %.s,%.o,$(SOURCES_ASM))

# Build flags
INCLUDES 	:= -I.
ASFLAGS 	:= $(INCLUDES)

# build targets
# kernel.img # for bare metal
all: uImage kernel.img

# Build image for uboot
# mkimage utility builds image for uboot
# -A set architecture type
# -T set image type
# -a load address
# -C set compression type
# -n set image name
# -d use image data from 'datafile'

uImage: kernel.img
	$(MKIMAGE) -A arm -T kernel -a $(LOAD_ADDRESS) -C none -n "bare metal" -d kernel.img pImage
	cp pImage /var/lib/tftpboot

# Build binary image for bare metal
kernel.img: bare.elf
	$(PREFIX)$(OBJCOPY) bare.elf -O binary kernel.img

# Build the ELF file
bare.elf: $(OBJS) linker.ld
	$(PREFIX)$(LD) $(OBJS) -Tlinker.ld -o $@

# Compile Assembly to object file
%.o: %.s
	$(PREFIX)$(AS) $(OPT) $(ASFLAGS) -c $< -o $@

# Clean up the build directory
clean:
	$(RM) -f $(OBJS) *.elf *.img uImage *.o pImage

dist-clean: clean
	
