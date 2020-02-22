#include <stdio.h>
#include "hw2.c"

int main() {
  int numbers[ ] = {3, 6, 2, 6, 1, 0, 6};
  int numbers2[ ] = {4, 10, 2017};
  add_index(numbers, 7);
  int i;
  for (i=0; i<7; i++)
    printf("%d ", numbers[i]);
  printf("\n");

  int scores[ ] = {4, 6, 7, 9, 8, 8, 10, 8, 10, 9, 8, 6, 7, 2, 7};
  int min, max;
  min_and_max(scores, 15, &min, &max);
  printf("The min is %d and the max is %d\n", min, max); 

  int x[ ] = {3, 1, 2};
  int y[3];
  copy_array(y,x,3);
  for (i=0; i<3; i++)
    printf("%d ", y[i]);
  printf("\n");

  int rev[] = {1, 2, 3, 4, 5};
  reverse_array(rev, 5);
  for (i=0; i<5; i++)
    printf("%d ", x[i]);
  printf("\n");

  int t1, t2;
  char s1, s2;
  t1 = 32; s1 = 'F';
  convert_temp(t1, s1, &t2, &s2);
  printf("This output should be 0 C\n");
  printf("%d %c\n", t2, s2);
  convert_temp(t2, s2, &t1, &s1);
  printf("This output should be 32 F\n");
  printf("%d %c\n", t1, s1);

  // this should print 0 C
  t1 = 50; s1 = 'F';
  convert_temp(t1, s1, &t2, &s2);
  printf("This output should be 10 C\n");
  printf("%d %c\n", t2, s2);
  convert_temp(t2, s2, &t1, &s1);
  printf("This output should be 50 F\n");
  printf("%d %c\n", t1, s1);
  }

