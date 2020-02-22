#include <stdio.h>
#include <string.h>
#include "hw3.c"

int main() {

  // 1.  strcmp373
  printf("Problem 1.\n");
  int c1, c2, c3, c4;
  c1 = strcmp373("bin", "bag"); // returns 8 
  c2 = strcmp373("computer", "game"); // returns -4 
  c3 = strcmp373("computer", "computer"); // returns 0 
  // returns -97 the difference between '\0' and 'a
  c4 = strcmp373("are", "area"); 
  printf("%d %d %d %d\n", c1, c2, c3, c4);

  // 2.  strcat373
  printf("Problem 2.\n");
  char stra[10] = "comp";
  char strb[ ] = "uter";
  char strc[10] = "comp";
  printf("%s contains %s\n", stra ,stra);
  printf("%s contains %s\n", strb ,strb);
  printf("%s contains %s\n", strc, strc);
  printf("concatenate %s and %s\n", stra, strb);
  strcat373(stra, strb);
  printf("stra contains %s\n", stra);
  printf("strb contains %s\n", strb);
  printf("concetenate %s and %s\n", strb, strc);
  printf("str2 contains %s\n", strcat373(strb, strc));

  // 3.  strchr373
  printf("Problem 3.\n");
  char words[] = "off-campus and on-campus housing";
  char *c= strchr373(words, '-');
  printf("Looking for '-' in %s\nFound at location %s\n", words, c);
  char *d;
  d = strchr373(&words[5], '-');
  printf("Looking for '-' in %s\nFound at location %s\n", c+1, d);

  // 4.  strncpy373
  printf("Problem 4\n");
  char s1[] = "comp";
  char s2[] = "systems";
  printf("Using strncpy into %s from %s,\n", s1, s2);
  printf("but only allowing 4 characters\n");
  strncpy373(s1, s2, 4);
  printf("Result is s1 %s and s2 %s\n", s1, s2);

  // 5.  strncat373
  printf("Problem 5\n");
  char strn1[100] = "comp";     // this is where all the concatenation is
  char strn2[] = "uter ";       // going on so I made it bigger
  char strn3[] = "science";
  strncat(strn1, strn2, 5);
  strncat(strn1, strn3, 7);
  char strn4[15] = "comp";     // a smaller array.  The entire concatenation
  strncat(strn4, strn2, 5);    // can't fit
  strncat(strn4, strn3, 5);
  printf("strn4 is %s\n", strn4);
  char x;
  scanf("%c", &x);
}
