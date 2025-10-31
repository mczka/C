 #include<stdio.h>

int main(void) {

    /* int num = 6;
     *    name: num
     *    value: 6
     *    type: int
     *    location: where the variable is stored
     *    address: label for the location
     */
    int num = 6;     /* Integer */
    int * ptr;       /* Pointer to an integer (or integer pointer) */

    printf("   & : reference operator - returns the address\n");
    printf("   * : dereference operator - returns an alias [value]\n\n");

    ptr = &num;    /* ptr holds the address of num */
    printf("   ptr holds the address of num (value)\n");
    printf("ADDR: %p  DATA: [num or *ptr = %d, size=%ld]\n", 
            (void *) &num, num, sizeof(num));
    printf("ADDR: %p  DATA: [ptr = %p size=%ld] ->  DATA: *ptr=%d\n", 
           (void *) &ptr, (void *) ptr, sizeof(ptr), *ptr);

    /* *ptr is an alias of num */
    *ptr = 20;

    printf("\n   *ptr is an alias of num (value) -> new value of num *ptr=20\n");
    printf("ADDR: %p  DATA: [num or *ptr = %d size=%ld]\n", 
            (void *) &num, num, sizeof(num));
    printf("ADDR: %p  DATA: [ptr = %p size=%ld] -> DATA: *ptr=%d\n",
            (void *) &ptr, (void *) ptr, sizeof(ptr), *ptr);

    printf("\n");
    printf("Operator Variable = value: \n");
    printf("  num\t=\t%d\n", num);
    printf(" &num\t=\t%p\n", (void *) &num);
    printf("  ptr\t=\t%p\n", (void *) ptr);
    printf(" *ptr\t=\t%d\n", *ptr);
    printf(" &ptr\t=\t%p\n", (void *) &ptr);
    printf("*(&num)\t=\t%d\n", *(&num));
    printf("&(*ptr)\t=\t%p\n", (void *) &(*ptr));
  
    return(0);
}

/*
clang 0100_pointers.c
./a.out 
   & : reference operator - returns the address
   * : dereference operator - returns an alias [value]

   ptr holds the address of num (value)
ADDR: 0x7ffcd57b8844  DATA: [num or *ptr = 6, size=4]
ADDR: 0x7ffcd57b8838  DATA: [ptr = 0x7ffcd57b8844 size=8] ->  DATA: *ptr=6

   *ptr is an alias of num (value) -> new value of num *ptr=20
ADDR: 0x7ffcd57b8844  DATA: [num or *ptr = 20 size=4]
ADDR: 0x7ffcd57b8838  DATA: [ptr = 0x7ffcd57b8844 size=8] -> DATA: *ptr=20

Operator Variable = value: 
  num	=	20
 &num	=	0x7ffcd57b8844
  ptr	=	0x7ffcd57b8844
 *ptr	=	20
 &ptr	=	0x7ffcd57b8838
*(&num)	=	20
&(*ptr)	=	0x7ffcd57b8844

*/
