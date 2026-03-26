#include <stdio.h>

long SquareMultiply(int x, unsigned int exp)
{
	int result=1;

	for (result = 1; exp != 0; exp = exp >> 1)
        {                        
                if (exp & 0x1)
		{     
                        result *= x;
		}
		x = x * x;
        }
	
	return result;
}

int main (int argc, char **argv)
{
	printf("x(p) = %lu\n", SquareMultiply(2,0));
	printf("x(p) = %lu\n", SquareMultiply(2,1));
	printf("x(p) = %lu\n", SquareMultiply(2,2));
        printf("x(p) = %lu\n", SquareMultiply(2,3));
        printf("x(p) = %lu\n", SquareMultiply(2,7));
	return 0;
}
