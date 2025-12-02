#include<stdio.h>

typedef unsigned char u8;

u8 BitRead(u8 word, u8 n)
{
  return (word>>n) & 1;
}

u8 BitSet(u8 word, u8 n)
{
  return word | (1<<n);
}

u8 BitClear(u8 word, u8 n)
{
  return word & !(1<<n);
}

u8 BitFlip(u8 word, u8 n)
{
  return word ^ (1<<n);
}

int main() {
    unsigned int num = 8;

    printf("\nInitial:\n");
    printf("  num = %x\n", num);

    printf("\nLeft shift by 2:\n");
    num = num << 2;
    printf("  num = %x\n", num);

    printf("\nRight shift by 4:\n");
    num = num >> 4;
    printf("  num = %x\n", num);

    printf("\nLeft shift by 2:\n");
    num = num << 2;
    printf("  num = %x\n", num);

    printf("\nBitwise operators:\n");
    printf("num & 1 = %x\n", num & 1);   /* Logical AND */
    printf("num | 1 = %x\n", num | 1);   /* Logical OR */
    printf("num ^ 1 = %x\n", num ^ 1);   /* Logical XOR */

    printf("\n");
    printf("num & 9 = %x\n", num & 9);   /* Logical AND */
    printf("num | 9 = %x\n", num | 9);   /* Logical OR */
    printf("num ^ 9 = %x\n", num ^ 9);   /* Logical XOR */

    u8 word = 1;
    u8 ret;
    word = BitSet(word,1);
    word = BitClear(word,0);
    word = BitFlip(word,4);

    ret = BitRead(word,0);
  
    return ret;
}
