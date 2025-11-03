#include<stdio.h>
#include<stdlib.h>

int * new_int_return(int val) {
    int * newptr;
    newptr = malloc(sizeof(int));
    *newptr = val;
    return newptr;
}

void new_int_parm(int ** ptr, int val) {
    int * newptr;
    newptr = malloc(sizeof(int));
    *newptr = val;
    *ptr = newptr;  /* Dereferencing ptr gives me an alias of the pointer that was passed */
}

int main(void) {

    /* int val = 7;                                                                                         
     *    name: val                                                                                                                                     
     *    value: 7                                                                                                                                      
     *    type: int                                                                                                                                     
     *    location: where the variable is stored                                                                                                        
     *    address: label for the location                                                                                                               
     */                                                                                                     
    int num = ~0;     /* Integer variable */                                                                 
    int val = 7;
    int * ptr;        /* Pointer to an integer (or integer pointer) */                   
    ptr = &val;           /* Integer pointer variable (pointer to int) */        
    int ** dptr = &ptr;   /* Integer pointer pointer variable (pointer to int pointer) */
                                       
                                                                                                            
    printf("A POINTER is a variable that holds the memory address of a variable\n");                
    printf("A DOUBLE POINTER is a variable that holds the memory address of a pointer variable\n"); 
    printf("\n");                                                                                   
    printf("   & : reference operator   - returns the address\n");                                  
    printf("   * : dereference operator - returns an alias [value]\n\n");
printf("\n");
printf("int main ()          main:\n");
printf("{                            pushp   rbp\n");
printf("                             mov     rbp, rsp\n");
printf("                             mov     dword ptr [rbp - 4], 0 /* zeroed to aligment 8B */\n");
printf("\n");
printf("    int val = 7;             mov     dword ptr [rbp - 8], 7\n");
printf("\n");
printf("    int* ptr=&val;           lea     rax, [rbp - 8]\n");
printf("                             mov     qword ptr [rbp - 16], rax\n");
printf("\n");
printf("    int** dptr=&ptr;         lea     rax, [rbp - 16]\n");
printf("                             mov     qword ptr [rbp - 24], rax\n");
printf("\n");
printf("    **dptr = 0;              mov     rax, qword ptr [rbp - 24]\n");
printf("                             mov     rax, qword ptr [rax]\n");
printf("                             mov     dword ptr [rax], 0\n");
printf("\n");
printf("    return **dptr;           mov     rax, qword ptr [rbp - 24]\n");
printf("}                            mov     rax, qword ptr [rax]\n");
printf("                             mov     eax, dword ptr [rax]\n");
printf("                             popp    rbp\n");
printf("                             ret\n");
printf("\n");

    printf("             Address   :   Data\n");
    printf("    &val %p: val = %d   (size=%ld)\n",                                                               
            (void *) &val, val, sizeof(val));                                                               
    printf("    &ptr %p: [%p] = ptr = &val  (size=%ld) .->  *ptr=%d\n",                                                  
           (void *) &ptr, (void *) ptr, sizeof(ptr), *ptr);
    printf("   &dptr %p: [%p] = dptr = &ptr -> [%p] *dptr = ptr = &val  (size=%ld) .->  **dptr=%d\n",                  
           (void *) &dptr, (void *) dptr, *dptr, sizeof(dptr), **dptr);                                                 
printf("\n");
printf("                                                   **dptr\n");
printf("                           *dptr                     *ptr\n");
printf("       dptr                  ptr                      val\n");
printf("+---------------+       +---------------+      +---------------+\n");
printf("|%p |  ->   |%p |  ->  |             %d |\n", dptr, ptr, val);
printf("+---------------+       +---------------+      +---------------+\n");
printf(" %p          %p         %p\n", &dptr, &ptr, &val);
printf("&dptr                   &ptr                   &val\n");
printf("\n");                                                                                                            

    ptr = &num;           /* Integer pointer variable (pointer to int) */
    printf("Operator Variable = value: \n");                                         
    printf("  num\t= %d\n", num);                                                   
    printf(" &num:\t= %p\n", (void *) &num);                                         
    printf("  ptr\t= &num = %p\n", (void *) ptr);                                          
    printf(" *ptr\t= %d\n", *ptr);                                                  
    printf(" &ptr\t= %p\n", (void *) &ptr);                                      
    printf("*(&num)\t= %d\n", *(&num));                                          
    printf("&(*ptr)\t= %p\n", (void *) &(*ptr));

    int * ptr1=NULL;
    int * ptr2=NULL;

    printf("/* Note that the pointers are not initalized here, so we are not dereferencing */\n");
    printf("Original:\n");
    printf("   ptr1=%p  &ptr1=%p\n", (void*) ptr1, (void*) &ptr1);
    printf("   ptr2=%p  &ptr2=%p\n", (void*) ptr2, (void*) &ptr2);
    printf("\n");

    printf("ptr1=new_int_return(4)\nptr2=new_int_return(7)\n");
    ptr1 = new_int_return(4);
    ptr2 = new_int_return(7);
    printf("   ptr1=%p  *ptr=%d  &ptr1=%p\n", (void*) ptr1, *ptr1, (void*) &ptr1);
    printf("   ptr2=%p  *ptr=%d  &ptr2=%p\n", (void*) ptr2, *ptr2, (void*) &ptr2);
    printf("\n");

    printf("new_int_parm(&ptr1, 3)\nnew_int_parm(&ptr2, 8)\n");
    new_int_parm(&ptr1, 3);
    new_int_parm(&ptr2, 8);
    printf("   ptr1=%p  *ptr=%d  &ptr1=%p\n", (void*) ptr1, *ptr1, (void*) &ptr1);
    printf("   ptr2=%p  *ptr=%d  &ptr2=%p\n", (void*) ptr2, *ptr2, (void*) &ptr2);
    printf("\n");
    return 0;
}


/*
clang -g -Wall 0100_pointers.c
./a.out 
A POINTER is a variable that holds the memory address of a variable
A DOUBLE POINTER is a variable that holds the memory address of a pointer variable

   & : reference operator   - returns the address
   * : dereference operator - returns an alias [value]


int main ()          main:
{                            pushp   rbp
                             mov     rbp, rsp
                             mov     dword ptr [rbp - 4], 0 /* zeroed to aligment 8B */

    int val = 7;             mov     dword ptr [rbp - 8], 7

    int* ptr=&val;           lea     rax, [rbp - 8]
                             mov     qword ptr [rbp - 16], rax

    int** dptr=&ptr;         lea     rax, [rbp - 16]
                             mov     qword ptr [rbp - 24], rax

    **dptr = 0;              mov     rax, qword ptr [rbp - 24]
                             mov     rax, qword ptr [rax]
                             mov     dword ptr [rax], 0

    return **dptr;           mov     rax, qword ptr [rbp - 24]
}                            mov     rax, qword ptr [rax]
                             mov     eax, dword ptr [rax]
                             popp    rbp
                             ret

             Address   :   Data
    &val 0x7ffe29f80900: val = 7   (size=4)
    &ptr 0x7ffe29f808f8: [0x7ffe29f80900] = ptr = &val  (size=8) .->  *ptr=7
   &dptr 0x7ffe29f808f0: [0x7ffe29f808f8] = dptr = &ptr -> [0x7ffe29f80900] *dptr = ptr = &val  (size=8) .->  **dptr=7

                                                   **dptr
                           *dptr                     *ptr
       dptr                  ptr                      val
+---------------+       +---------------+      +---------------+
|0x7ffe29f808f8 |  ->   |0x7ffe29f80900 |  ->  |             7 |
+---------------+       +---------------+      +---------------+
 0x7ffe29f808f0          0x7ffe29f808f8         0x7ffe29f80900
&dptr                   &ptr                   &val

Operator Variable = value: 
  num	= -1
 &num:	= 0x7ffe29f80904
  ptr	= &num = 0x7ffe29f80904
 *ptr	= -1
 &ptr	= 0x7ffe29f808f8
*(&num)	= -1
&(*ptr)	= 0x7ffe29f80904

/* Note that the pointers are not initalized here, so we are not dereferencing */
Original:
   ptr1=0  &ptr1=0x7ffe29f808e8
   ptr2=0  &ptr2=0x7ffe29f808e0

ptr1=new_int_return(4)
ptr2=new_int_return(7)
   ptr1=0x7fd4fea35c80  *ptr=4  &ptr1=0x7ffe29f808e8
   ptr2=0x7fd4fea35c90  *ptr=7  &ptr2=0x7ffe29f808e0

new_int_parm(&ptr1, 3)
new_int_parm(&ptr2, 8)
   ptr1=0x7fd4fea35ca0  *ptr=3  &ptr1=0x7ffe29f808e8
   ptr2=0x7fd4fea35cb0  *ptr=8  &ptr2=0x7ffe29f808e0
*/
