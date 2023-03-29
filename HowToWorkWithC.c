#include <stdio.h>  // printf
#include <stdlib.h> // for atoi and atof
#include <string.h> // for strcmp
#include <stdbool.h>// bool

#include <sys/socket.h> // struct sockaddr, struct sockaddr_storage
#include <netinet/in.h> // struct sockaddr_in, struct sockaddr_in6,
                        // struct in_addr, struct in6_addr

// gcc -std=c11 -Wall -fmax-errors=10 -Wextra -g str.c -o strbin
// ./strbin -p1212 -o test sthfhghgABC123

void dumpmem(FILE *out, const void *ptr, const size_t size);

int main(int argc, char **argv)
{
        printf("%p: argc-> %d\n", &argc, argc);
        printf("%p: argv-> %p %p\n", &argv, &(**argv), &(*argv));
        printf("I have %d arguments from the command line: \n", argc);
        for (int i = 0; i<argc; i++) {
                printf("\tArgument %d: %s\n", i, argv[i]);
        }
        for (int i = 0; i<argc; i++) {
                printf("%p: %p, argv[%d]-> %s %X\n", &(*(argv+i)), &(*argv[i]), i, argv[i], (int )argv[i]);
        }



        unsigned long long a=1024*1024*1024; // 1GB
        unsigned long long b=(1U << 30);
        unsigned long long * addrOfA = &a;
        printf("address of a: %p\n", addrOfA);
        printf("value of a: %lld\n\n", *addrOfA);
        printf("address of b: %p\n", &b);
        printf("value of b: %lld\n\n", b);
        printf("SIZE of val:\n");
        printf("bool %zuB\n", sizeof(bool));
        printf("short %zuB\n", sizeof(short));
        printf("int %zuB\n", sizeof(int));
        printf("long %zuB\n", sizeof(long));
        printf("unsigned long long %zuB\n", sizeof(unsigned long long));
        printf("long double %ldB\n", sizeof(long double));

        printf("STRUCT:\n");
        printf("sockaddr_storage %zuB\n", sizeof(struct sockaddr_storage));
        printf("sockaddr %zuB\n", sizeof(struct sockaddr));

        printf("sockaddr_in %zuB\n", sizeof(struct sockaddr_in));
        printf("sockaddr_in6 %zuB\n", sizeof(struct sockaddr_in6));
        printf("in_addr %zuB\n", sizeof(struct in_addr));
        printf("in6_addr %zuB\n", sizeof(struct in6_addr));

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
	
        dumpmem(stdout, &argc, 0x10);
        dumpmem(stdout, &(*argv), 0x40);

    return 0;
}


void dumpmem(FILE *out, const void *ptr, const size_t size)
{
        const size_t BYTES_PER_LINE = 16;
        size_t offset, read;

        uint8_t *p = (uint8_t *)ptr;
        const uint8_t *maxp = (p + size);

        if (out == NULL || ptr == NULL || size == 0)
        {
                return;
        }

        for (offset = read = 0; offset != size; offset += read)
        {
                uint8_t buf[BYTES_PER_LINE];

                for (read = 0; read != BYTES_PER_LINE && (&p[offset + read]) < maxp; read++)
                {
                        buf[read] = p[offset + read];
                }

                if (read == 0)
                        return;

                fprintf(out, "%p: ", p + offset);

                /* raw data */
                for (size_t i = 0; i < read; i++)
                {
                        fprintf(out, " %.2x", buf[i]);
                        if (BYTES_PER_LINE > 8 && BYTES_PER_LINE % 2 == 0 && i == (BYTES_PER_LINE / 2 - 1))
                                fprintf(out, " ");
                }

                /* ASCII */
                if (read < BYTES_PER_LINE)
                {
                        for (size_t i = read; i < BYTES_PER_LINE; i++)
                        {
                                fprintf(out, "  ");
                                fprintf(out, " ");
                                if (BYTES_PER_LINE > 8 && BYTES_PER_LINE % 2 == 0 && i == (BYTES_PER_LINE / 2 - 1))
                                        fprintf(out, " ");
                        }
                }
                fprintf(out, " ");
                for (size_t i = 0; i < read; i++)
                {
                        if (buf[i] <= 31 || buf[i] >= 127) /* ignore control and non-ASCII characters */
                                fprintf(out, ".");
                        else
                                fprintf(out, "%c", buf[i]);
                }

                fprintf(out, "\n");
        }
}
