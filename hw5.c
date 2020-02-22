#include <stdio.h>

int f1(int x){
	unasigned char result = x - 'a';
	return result <= 25;
}

int f2(int x, int y, int z){
	return x == y && x == z;
}

long f3(unsigned long x){
	return ~x >> 63;
}

int f4(int x, int y){
	int a = 1;
	if(x <= 1)
		return a;
	x++;
	y = 2;
L8: a *= y;
	y++
	if (y != x)
		goto L8;
	return a;
}

int f5(chars* arr, int len){
	if (len <= 1)
		return 1;
		while(*(arr+1)!= '\0'){
			if(*arr>*(arr+1))
				return 0;
			arr++;
		}
		return 1;
}
