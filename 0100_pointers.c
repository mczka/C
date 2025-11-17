## inspiration from https://github.com/wadehuber/codeexamples/tree/master/c
#include <stdio.h>
#include <stdlib.h>

int  power (int x, int y)
{
     return x*y;
}

int* newint_return (int x, int y)
{
    int* newptr;
    newptr = malloc(sizeof(int));
    *newptr = x*y;
    printf("+----------------+----------------+\n");                                               
    printf("| %p | %p | newptr NEWINT_RETURN STACK FRAME\n", &newptr, newptr);
    return newptr;
}

void newint_param(int ** ptr, int val) {
    int* newptr;
    newptr = malloc(sizeof(int));
    *newptr = val*val;
    *ptr = newptr;  /* Dereferencing ptr gives me an alias of the pointer that was passed */
    printf("+----------------+----------------+\n");
    printf("| %p | %p | newptr NEWINT_PARAM STACK FRAME\n", &newptr, newptr);
    printf("+----------------+----------------+\n");
    printf("| %p | %p | ptr (dptr) NEWINT_PARAM STACK FRAME\n", &ptr, ptr);
    printf("+----------------+----------------+\n");                                        
    printf("| %p | %p | ptr  NEWINT_PARAM STACK FRAME\n", &(*ptr), *ptr);
}

#define ELTS 10

int main ()
{
    /*    int val = 7;                                                                                         
     *    name: val                                                                                                                                     
     *    value: 7                                                                                                                                      
     *    type: int                                                                                                                                     
     *    location: where the variable is stored                                                                                                        
     *    address: label for the location                                                                                                               
     */ 
    
    int    val;
    int*   ptr;
    int** dptr;
    int(*fnptr) (int,int);
    int  arr[ELTS];
    int* arrptr;
    int*  ptr1=NULL;
    int*  ptr2=NULL;
    
    val = 512;
    ptr = &val;
    dptr = &ptr;
    fnptr = power;
    arrptr = arr;

    printf("A POINTER is a variable that holds the memory address of a variable\n");                
    printf("A DOUBLE POINTER is a variable that holds the memory address of a pointer variable\n"); 
    printf("\n");                                                                                   
    printf("   & : reference operator   - returns the address\n");                                  
    printf("   * : dereference operator - returns an alias [value]\n");
printf("\n");
printf("int    val;\n");
printf("int*   ptr;\n");
printf("int** dptr;\n");
printf("int(*fnptr) (int,int,int);\n");
printf("int   arr[ELTS];\n");
printf("int*  arrptr;\n");
printf("int*  ptr1=NULL;\n");
printf("int*  ptr2=NULL;\n");
printf("\n");
printf("       ADDR             DATA\n");
printf("+----------------+----------------+\n");           
printf("| %p | %14d | arr[9] (arr[ELTS-1])\n", &arr[9], arr[9]);
printf("+----------------+----------------+\n");
printf("...\n");
printf("+----------------+----------------+\n");
printf("| %p | %14d | arr[0]\n", &arr[0], arr[0]);              
printf("+----------------+----------------+\n");
printf("| %p | %14d |  val (**dptr=value or *ptr=value or val=value)\n", &val, val);
printf("+----------------+----------------+\n");
printf("| %p | %p |  ptr (ptr=&val or *dptr=ptr)\n", &ptr, ptr);
printf("+----------------+----------------+\n");
printf("| %p | %p | dptr (dptr=&ptr)\n", &dptr, dptr);
printf("+----------------+----------------+\n");
printf("| %p | %p | fnptr (fnptr=power)\n", &fnptr, power);
printf("+----------------+----------------+\n");
printf("| %p | %p | arrptr (arrptr=arr or =&arr[0])\n", &arrptr, arrptr);        
printf("+----------------+----------------+\n");
printf("| %p |              %p | ptr1 (ptr1=NULL)\n", &ptr1, ptr1);                                             
printf("+----------------+----------------+\n");
printf("| %p |              %p | ptr2 (ptr2=NULL)\n", &ptr2, ptr2);                                                                
printf("+----------------+----------------+\n");
printf("\n");

    printf("Operator Variable = value\n");                                         
    printf("    val\t= %d\n", val);                                                   
    printf("   &val\t= %p\n", (void *) &val);                                         
    printf("    ptr\t= %p\n", (void *) ptr);                                          
    printf("   *ptr\t= %d\n", *ptr);                                                  
    printf("   &ptr\t= %p\n", (void *) &ptr);
    printf("   dptr\t= %p\n", (void *) dptr);                                                                           
    printf("  *dptr\t= %p\n", *dptr);
    printf(" **dptr\t= %d\n", **dptr);                                                                                    
    printf("  &dptr\t= %p\n", (void *) &dptr);
    printf("*(&val)\t= %d\n", *(&val));                                          
    printf("&(*ptr)\t= %p\n", (void *) &(*ptr));
    printf("\n");

    printf("                                                     **dptr = value\n");
    printf("                            *dptr = ptr                *ptr = value\n");
    printf("    dptr = &ptr               ptr = &val                val = value\n");
    printf("+---------------+          +---------------+        +---------------+\n");
    printf("|%p |   --->   |%p |  --->  |           %d |\n", dptr, ptr, val);
    printf("+---------------+          +---------------+        +---------------+\n");
    printf(" %p             %p           %p\n", &dptr, &ptr, &val);
    printf("&dptr                      &ptr                     &val\n");
    printf("\n");

    printf("int* newint_return (int x, int y); /* return pointer */\n");
    printf("ptr1=newint_return(16,16);\n");
    ptr1 = newint_return(16,16);
    printf("+----------------+----------------+\n");                                                                      
    printf("| %p | %p | ptr1 MAIN STACK FRAME\n", &ptr1, ptr1);                                                   
    printf("+----------------+----------------+\n");                                                                      
    printf("| %p | %14d | *ptr1 HEAP MEMORY\n", ptr1, *ptr1);                                                    
    printf("+----------------+----------------+\n");
    printf("\n");
    printf("void newint_param(int ** ptr, int val); /*  pass &pointer to  ** ptr */\n");
    printf("newint_param(&ptr2,1024);\n");                                
    newint_param(&ptr2,1024);
    printf("+----------------+----------------+\n");                                               
    printf("| %p | %p | ptr2 MAIN STACK FRAME\n", &ptr2, ptr2);                                    
    printf("+----------------+----------------+\n");                                               
    printf("| %p | %14d | *ptr2 HEAP MEMORY\n", ptr2, *ptr2);                                          
    printf("+----------------+----------------+\n");
    printf("\n");

    printf("Array indexing and pointer arithmetic\n");
    printf("Array indexing arr[i], Pointer arithmetic (ptr+i) behind the scene (ptr+i*sizeof(int))\n");
    printf("\n");
    printf("ptr = arr; or ptr = &arr[0];\n");
    ptr = arr;
    printf("*(ptr+0)=0; or arr[0]=0;\n*(ptr+1)=11; or arr[1]=11; or *(arr+1)=11;\n");
    printf("arr[2]=22; arr[3]=33; *(arr+4)=44; *(ptr+5)=55; arr[6]=66; arr[7]=77; ptr[ELTS-2]=88; ptr[ELTS-1]=99;\n");
    printf("if ptr++ or ptr-- at this point the ptr does not point to the start of the array\n");
    printf("Array initialised:\n");
    *ptr = 0;
    *(ptr + 1) = 11;
    arr[2] = 22;
    arr[3] = 33;
    *(arr + 4) = 44;
    *(ptr + 5) = 55;
    arr[6] = 66;
    arr[7] = 77;
    ptr[ELTS-2] = 88;
    ptr[ELTS-1] = 99; /* array indexing using pointer name */
    for (int k=0;k<ELTS;k++)
        printf("arr[%d]=%d ", k, arr[k]);
    printf("\n");
printf("\n");                          
printf("       ADDR             DATA\n");
printf("+----------------+----------------+\n");
printf("| %p | %14d | arr[0] (ptr=arr; or ptr=&arr[0];)\n", &arr[0], arr[0]);
printf("+----------------+----------------+\n");
printf("| %p | %14d | arr[1]\n", &arr[1], arr[1]);                                                     
printf("+----------------+----------------+\n");                                                       
printf("| %p | %14d | arr[2]\n", &arr[2], arr[2]);                                               
printf("+----------------+----------------+\n");
printf("| %p | %14d | arr[3]\n", &arr[3], arr[3]);                                                     
printf("+----------------+----------------+\n");                                                       
printf("| %p | %14d | arr[4]\n", &arr[4], arr[4]);                                                     
printf("+----------------+----------------+\n");                                                       
printf("| %p | %14d | arr[5]\n", &arr[5], arr[5]);                                                     
printf("+----------------+----------------+\n");                                                       
printf("| %p | %14d | arr[6]\n", &arr[6], arr[6]);                                                     
printf("+----------------+----------------+\n");                                                       
printf("| %p | %14d | arr[7]\n", &arr[7], arr[7]);                 
printf("+----------------+----------------+\n");                   
printf("| %p | %14d | arr[8]\n", &arr[8], arr[8]);                                                   
printf("+----------------+----------------+\n");                   
printf("| %p | %14d | arr[9] (arr[ELTS-1])\n", &arr[9], arr[9]);   
printf("+----------------+----------------+\n");                   
printf("\n");
printf("Are arraays and pointers the same?\n");
printf(" sizeof(array) = %lu\n", sizeof(arr));
printf(" sizeof(ptr) = %lu\n", sizeof(ptr));
printf("   You can assign a value to a pointer, but not an array name\n"); 
printf("   VALID ptr = &ii;\n");
printf("   ERROR array = &ii;\n");
printf("\n");
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
    
    return fnptr(5,7);
}
