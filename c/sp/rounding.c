#include <stdio.h>

//#define N 10000000
#define N 2396747
/* This program shows the errors than can arise while
   working with rational numbers. In single precision
   a floating point number is represented as a binary
   number with 32 digits. The first digit on the left represents
   the sign of the exponent (0 positive, 1 negative),
   then there are 8 digits for the exponent
   (with base = 2) and finally 24 digits for the mantissa
    with the first digit that represents the sign of the mantissa.
   The decimal value of the exponent is
   computed from the 8 bits less 127. The decimal value
   of the mantissa is computed by adding the powers
   of 2 of each bit's position in the mantissa. The decimal
   point is set just after the most significant digit.
*/
int main () {
  float S = 0., x = 7.;
  unsigned int i, iS = 0, ix = 7;
  for (i = 0; i < N; i++) {
    S += x;
    iS += ix;
  }
  printf (" Using floats : %.0f x %d = %.0f\n", x, N, S);
  printf (" Using integers: %d x %d = %d\n", ix , N, iS);
}
