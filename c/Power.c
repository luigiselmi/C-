#include <stdio.h>

/* defines a function to compute the power of a number */

int power(int m, int n); // declared here to be used in main() before its definition

int main() {

  for (int n = 0; n < 32; ++n)
    printf("%d %d %d\n", n, power(2, n), power(-3, n));

  return 0;
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
