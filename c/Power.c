#include <stdio.h>

/* defines a function to compute the power of a number */

int power(int m, int n); // declared here to be used in main() before its definition

int main() {

  for (int i = 0; i < 10; ++i)
    printf("%d %d %d\n", i, power(2, i), power(-3, i));

  return 0;
}

/* raise base to the power of n*/
int power(int base, int n) {

  int p;

  for (p = 1; n > 0; --n)
    p *= base;

  return p;
}
