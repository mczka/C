#include <stdio.h>

struct {
    unsigned short limit;
    unsigned long base;
} __attribute__((packed)) idtr;

int main() {
    asm("sidt %0" : "=m" (idtr));
    printf("%lx %x\n", idtr.base, idtr.limit);
    return 0;
}
/* orginal 
int swallow_redpill () 
{
  unsigned char m[2+4], rpill[] = "\x0f\x01\x0d\x00\x00\x00\x00\xc3";
  *((unsigned*)&rpill[3]) = (unsigned)m;
  ((void(*)())&rpill)();
  return (m[5]>0xd0) ? 1 : 0;
}
*/
