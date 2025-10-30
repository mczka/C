#include<stdio.h>

int main(void) {

    /* int num = 6;
     *    name: num
     *    value: 6
     *    type: int
     *    location: where the variable i stored
     *    address: label for the location
     */
    int num = 6;     /* Integer */
    int * ptr;       /* Pointer to an integer (or integer pointer) */

    /* & : reference operator - returns the address */
    /* * : dereference operator - returns an alias */

    ptr = &num;    /* ptr holds the address of num */
    printf("num = %d, address %p, size=%ld\n", 
            num, (void *) &num, sizeof(num));
    printf("ptr = %p, address %p, size=%ld, *ptr=%d\n", 
           (void *) ptr, (void *) &ptr, sizeof(ptr), *ptr);

    /* *p is an alias of num */
    *ptr = 20;
    printf("\nAfter *ptr=20\n");
    printf("num = %d, address %p, size=%ld\n", 
            num, (void *) &num, sizeof(num));
    printf("ptr = %p, address %p, size=%ld, *ptr=%d\n",
            (void *) ptr, (void *) &ptr, sizeof(ptr), *ptr);

    printf("\n");
    printf("ptr & num: \n");
    printf("  ptr = %p\n", (void *) ptr);
    printf("  *ptr = %d\n", *ptr);
    printf("  num = %d\n", num);
    printf("  &num = %p\n", (void *) &num);
    printf("  *(&num) = %d\n", *(&num));
    printf("  &(*ptr) = %p\n", (void *) &(*ptr));
  
    return(0);
}
/*
clang 0100_pointers.c
./a.out
num = 6, address 0x7ffc42044694, size=4
ptr = 0x7ffc42044694, address 0x7ffc42044688, size=8, *ptr=6

After *ptr=20
num = 20, address 0x7ffc42044694, size=4
ptr = 0x7ffc42044694, address 0x7ffc42044688, size=8, *ptr=20

ptr & num: 
  ptr = 0x7ffc42044694
  *ptr = 20
  num = 20
  &num = 0x7ffc42044694
  *(&num) = 20
  &(*ptr) = 0x7ffc42044694
*/
