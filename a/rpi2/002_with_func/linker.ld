ENTRY(_start)
 
SECTIONS
{
	/* Need to understand this? In linker script is start address is 0x0 or
	 * 0x8000. when we generate uboot image with load address as 0x8000 image
	 * still works?
	 * Even if i change loadaddress in mkimage to 0x0 then also no change.
	 * May be this is because, It depends on where I download and run.
	 * In all these exercises I'm downloading at location 0x200000 and running
	 * from 0x200000. Looks like it is always executes from 0x200000. Then if
	 * that is the case, who uses uboot header, who will use 0x8000. Or do I
	 * need to copy .text to 0x8000 and run?
	 */
    /* Starts at LOADER_ADDR. */
	. = 0x8000;
    /* . = 0x0; */
	/* . = 0x1000; */
    __start__ = .;
    __text_start__ = .;
    .text :
    {
        *(.text)
    }
    . = ALIGN(4096); /* align to page size */
    __text_end__ = .;
    __end__ = .;
}
