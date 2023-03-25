#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	int a=(1U << 21)+256;
	printf("argc %d\n", argc);
        printf("hex: %X\n", a);
	double b=3.1415;
	int *ptr1;
	double *ptr2;
        ptr1=&a;
	ptr2=&b;
	union rep
	{
		double b;
		unsigned char bytes[sizeof(double)];
	};

	union rep r = {.b = 3.141500 };


	printf("Memory location, variable,  value\n");
	printf("%p: a-> %d %.16X\n", &a, a, a);	
	printf("%p: b-> %lf ", &b, b);
        for ( size_t i = 0; i < sizeof r.b; i++ )
                printf( "%02hhx ", r.bytes[i] );
	printf("\n");
	printf("%p: %p ptr1-> %d\n", &ptr1, ptr1, *ptr1);
	printf("%p: %p ptr2-> %lf\n", &ptr2, ptr2, *ptr2);

	return 0;
}
