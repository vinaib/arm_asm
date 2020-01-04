
__inline int asm_sum(int a, int b)
{
	int sum;
	
	__asm {
		add sum, a, b
	}
	
	return sum;
}

int c_sum(int a, int b)
{
	return (a + b);
}

//define global, so that we can view it in watch window
int result = 0;

int main(void)
{
	int a = 10;
	int b = 30;
	
	result = asm_sum(a, b);
	
	result = c_sum(a, b);
		
	while(1);
}
