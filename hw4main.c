#include <stdio.h>
#include "hw4.c"

int main() {
  int x;
  int *xptr = &x;
  long l;
  long *lptr = &l;
  unsigned long ul;
  unsigned long *ulptr = &ul;

  int i;
  for (i=0; i<5; i++)
     printf("power(%d) is %d\n", i, power(i));
  ul = maximum();
  printf("maximum long %#lx %lu\n", ul, ul);
  printf("neg_one() %d\n", neg_one());
  for (i=-5; i<=5; i++)
     printf("Negative %d is %d\n", i, negative(i));
  x = 0x13579ace;
  int *p = &x;
  for (i=0; i<4; i++) {
     set_byte(p, i, 0x55);
     printf("u = %#x\n", *p);
  }
} 



