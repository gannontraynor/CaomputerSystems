/* CSC 373 Sections 601, 610 Spring 2018
   Implement each of the 5 functions below (1.5 each).
   They should all be in 1 file, called hw3.c -- there
   should NOT be a main function in your submission.

   Also submit the written portion of the assignment (2.5 points).
*/

int strcmp373(char str1[], char str2[]) {
  int i, diff;
  for (i=0; ; i++) {
  	diff = str1[i] - str2[i];
  	if (diff == 0 && str1[i] == 0)
	  return 0;	
    else if (diff != 0) return diff;
  }
}

char *strcat373(char dest[], char src[]) {
  int i;
  for (i=0; dest[i] != '\0'; i++);
  int j;
  for (j=0; dest[j] != '\0'; j++)
  	dest[i++] = src[j];
  dest[i] = '\0';
  return dest; 
}

char *strchr373(char str[], char c) {
  char *p = str;
  while (*p != '\0'&& *p != c) 
    p++;
  if (*p == '\0') return 0;
  else return p;
}

char *strncpy373(char dest[], char src[], int n) {
	int i;
	int null = 0;
	for (i=0; src[i] == '\0' || i<n; i++)
		dest[i] = src[i];
		if (src[i] == '\0') null = 1;
	if (null) src[i] = '\0';
}

char *strncat373(char dest[], char src[], int n) {
  int i;
  for (i=0; dest[i] != '\0'; i++);
  int j;
  for (j=0; j<n; j++) {
  	dest[i] = src[j];
  	if (dest[i] == '\0')
  		return dest;
  	else {
  		dest[i] = '\0';
  		return dest;
  	}
  }
} 

