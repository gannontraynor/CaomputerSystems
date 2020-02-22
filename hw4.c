#include <stdio.h>

/*
CSC 373 Sections 601, 610 Spring 2018
Homework assignment 4
Due:  Date and time as specified on D2L

In the coding portion of this assignment, you 
must complete the 5 functons below.  Each 
function's body must consist of just a single C 
statement. Furthermore, the statement must not be 
a control statement, such as if, switch, or any 
kind of loop.  For each problem, you are also 
restricted to the operators and constants as specified.
No variables (other than the parameters) are allowed.
*/

/* 1.  Write a function which returns 2 to the nth power,
*      where n is a parameter passed to the function.  For
*      example, power(3) returns 8.  You may assume that n >= 0.
*      You may use no constants (the parameter is a variable, so
*      you may use it), and the only operator you may use is <<. 
*/

int power(int n) {
    return 0; // replace
}

/* 2.  Write a function that returns the maximum unsigned long
       integer.  The function is passed no parameters.  You may 
	   only use the constant 0 in this function, and must restrict 
	   yourself to using the bitwise operators.
*/

unsigned long maximum() {
	return 0;   // replace
}

/* 3.  Write a function to return -1.  You may only use the constant 0,
       and one or more bitwise operators.
*/

int neg_one() {
  return 0;   // replae
}

/* 4.  Write a function which sets the integer x to negative x.
       The parameter passed to the function is a pointer to x.
       You may only use the constant 1 in this function,
       and must restrict yourself to the assignment operator, 
       the dereferencing operator, the bitwise operators, and 
       the + operator.
*/

int negative(int x) {
    return 0;   // replace
}

/* 5.  Write a function called set_byte.  It is passed 3
       parameters:  a pointer to an unsigned integer x, an
       index i, and a new value v for the byte.
       The function should change the ith byte of x to
       v.  Byte 0 is x's least significant byte; byte 1
       is the next least significant byte, etc.; byte 3
       is x's most significant byte.  You may only use the
       constants 0-ff in this function, and must restrict
       yourself to the the assignment operator, the
       dereferencing operator, multiplication, bitwise 
       operators and shift operators.  Since xptr is a pointer
       to a signed integer, you may assume that 0 <= i <= 3.
*/

void set_byte(unsigned int *xptr, int i, char a_byte) {
	// add code
}




