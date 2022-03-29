#include <stdio.h>
#include <limits.h>

int power(int m, int n); // declared here to be used in main() before its definition

/* Prints the range of the data types available in C */

int main() {
  printf("Char: %d bytes\nInteger: %d bytes\nFloat: %d bytes\nDouble: %d bytes\nLong double: %d bytes\n", sizeof(char), sizeof(int), sizeof(float), sizeof(double), sizeof(long double));

  printf("Char bits: %d\n", CHAR_BIT);
  printf("Max Integer: %d\nMin Integer: %d\n", INT_MAX, INT_MIN);
  printf("Max Integer: %d\nMin Integer: %d\n", power(2, 31) - 1, -power(2, 31));
}

/* raise the base to the power of n*/
int power(int base, int n) {

  if (n == 0)
    return 1;

  int p;

  for (p = 1; n - 1 >= 0; --n)
    p *= base;

  return p;
}
