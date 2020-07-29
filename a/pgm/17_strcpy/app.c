#include<stdio.h>

extern void asm_wrapper(char *dest, char const *src, int n);


int main(int argc, char **argv)
{
	char src[] = "vinai kumar";
	char dest[15];

	if(argc > 1) 
		asm_wrapper(dest, argv[1], 12);
	else
		asm_wrapper(dest, src, 12);

	printf("After copy %s\n", dest);
}
