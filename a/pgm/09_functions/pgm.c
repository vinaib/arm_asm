#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void pc(char c, int n)
{
	int i=1, j= 0;

	char *p = malloc(n);

	memset(p,c,n);

	for(i=1;i<n;i+=2,j++)
		printf("%*.*d\n",100+j,i,i);

}

int main()
{
	pc('*', 10);
}
