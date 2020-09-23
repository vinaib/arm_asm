ENTRY(_start)

SECTIONS {
	. = 0x8000;

	__start__ = .;
	__text_start__ = .;

	.text :
	{
		*(.text)
	};
	. = ALIGN(4096);
	__text_end__ = .;

}
