#include <stdio.h>
#include <string.h> // strcmp(), strcpy(), strlen()

#define MAX_DIGITS_EXPONENT 8
#define MAX_DIGITS_MANTISSA 24

/* In single precision a floating point number is represented
   as a binary number with 32 digits. The first digit on the
   left represents the sign (0 positive, 1 negative),
   then there are 8 digits for the exponent
   (with base = 2) and finally 23 digits for the mantissa
    with the first binary digit that is always 1 and is not shown.
   The decimal value of the exponent is computed from the 8 bits
   less 127. The decimal value of the mantissa is computed by
   adding the powers of 2 of each bit's position in the mantissa.
   The decimal point is set just after the most significant digit. From right
   to left the contribution of each binary digit at position n
   is given by

   bit(n) * 2^(-n)

   and the mantissa is the sum of all the 23 digit plus 1, the
   hidden digit.

   float sum = 1.0;
   for (int n = 23; n > 0; ++n)
    sum += bit[n] * 2^(-n);

   What we are more interested in is to represent a decimal value
   as floating point and its representation in 32 binary digits
   (single precision)

*/
int char2bin(char c[], int i[], int length);
int dec_exp(int ie[], int len);
double dec_mant(int im[], int len);
int power(int base, int n);

int main () {

  char exponent[MAX_DIGITS_EXPONENT];
  char mantissa[MAX_DIGITS_MANTISSA];

  printf("Write the binary representation of the exponent\n");
  scanf("%s", exponent);
  printf("Exponent: %s\n", exponent);

  printf("Write the binary representation of the mantissa\n");
  scanf("%s", mantissa);
  printf("Mantissa: %s\n", mantissa);

  int ie[MAX_DIGITS_EXPONENT];
  for (int i = 0; i < MAX_DIGITS_EXPONENT; i++)
    ie[i] = 0;
  char2bin(exponent, ie, MAX_DIGITS_EXPONENT);
  for (int i = 0; i < MAX_DIGITS_EXPONENT; i++)
    printf("%d", ie[i]);
  printf("\n");

  int im[MAX_DIGITS_MANTISSA];
  for (int i = 0; i < MAX_DIGITS_MANTISSA; i++)
    im[i] = 0;
  char2bin(mantissa, im, MAX_DIGITS_MANTISSA);
  for (int i = 0; i < MAX_DIGITS_MANTISSA; i++)
    printf("%d", im[i]);
  printf("\n");

  int exp_decimal = dec_exp(ie, MAX_DIGITS_EXPONENT);
  printf("Exponent (dec): %d\n", exp_decimal);

  double mant_decimal = dec_mant(im, MAX_DIGITS_MANTISSA);
  printf("Mantissa (dec): %.10f\n", mant_decimal);

  double value_decimal = mant_decimal * power(2, exp_decimal);
  printf("Value (dec): %f\n", value_decimal);
}
/* Transforms the input array of char into an array of binary digits */
int char2bin(char c[], int i[], int length) {
  for (int n = 0; n < length; n++)
    if (c[n] == '1')
      i[n] = 1;
    else if (c[n] == '0')
        i[n] = 0;
    else
      return -1;

  return 0;
}
/* Computes the decimal representation of the exponent */
int dec_exp(int ie[], int len) {
  int exp = 0;
  for (int i = 0; i < len; i++)
    exp += ie[i] * power(2, len - i - 1);
  return exp - 127;
}
/* Computes the decimal representation of the mantissa. */
double dec_mant(int im[], int len) {
  double mant = 1.0;
  for (int i = 0; i < len; i++)
    mant += im[i] * (1.0 / power(2, i + 1));
  return mant;
}
/* Raises the base to the power of n*/
int power(int base, int n) {
  if (n == 0)
    return 1;
  int p;
  for (p = 1; n - 1 >= 0; --n)
    p *= base;
  return p;
}
