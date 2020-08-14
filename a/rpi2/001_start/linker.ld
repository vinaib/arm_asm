ENTRY(_start)
 
SECTIONS
{
    /* Starts at LOADER_ADDR. */
    . = 0x8000;
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
