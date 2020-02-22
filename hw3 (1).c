// Gannon Traynor

/* CSC 373 Sections 601, 610 Spring 2018
   Implement each of the 5 functions below (1.5 each).
   They should all be in 1 file, called hw3.c -- there
   should NOT be a main function in your submission.

   Also submit the written portion of the assignment (2.5 points).
*/
#include <stdio.h>

int strcmp373(char str1[], char str2[]) {
  int result = 0;
  int i = 0;
  while (str1[i] != '\0'){
  	i++;
  	if(str1[i] == str2[i]) result = 0;
  	else return str1[i] - str2[i];
  }
  return result;
 }

char *strcat373(char dest[], char src[]) {
   while(*dest)
      dest++;
 
   while(*src)
   {
      *dest = *src;
      src++;
      dest++;
   }
   *dest = '\0';
   return *dest;
}

char *strchr373(char str[], char c) {
  int i = 0;
  while (str[i] != '\0'){
  	i++
  	if (str[i] == c)
	}
	return 0;
}

char *strncpy373(char dest[], char src[], int n) {
  // you didn't explain what these are supposed to do

 
  return dest;
}

char *strncat373(char dest[], char src[], int n) {
  return dest;  // replace this
} 




