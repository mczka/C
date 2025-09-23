#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// buf1 in zero-initialized global vars area
char buf1[8] = {0};
// buf2 in initialized global vars area
char buf2[8] = {0, 1, 2, 3, 4, 5, 6, 7};

init main (int argc, char *argv[]}  /* char **argv */
{
  char buf3[8]; // buf3 on stack
  char *buf4;   // buf4 on stack (pointer)
  buf4 = malloc(8); // buf4 points to heap

  strcpy(buf1, argv[1]);
  printf("We got the input string: %s \n",buf1);
  return 0;
}
