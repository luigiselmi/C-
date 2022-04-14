#include <stdio.h>

#define MAX_DIGITS_EXPONENT 8
#define MAX_DIGITS_MANTISSA 23
#define EXPONENT_BIAS 127

/* In single precision a floating point number is represented
   as a binary number with 32 digits. The first digit on the
   left represents the sign (0 positive, 1 negative),
   then there are 8 digits for the exponent
   (with base = 2) and finally 24 digits for the mantissa
   with the first binary digit that is always 1 and is not shown.
   The number of digits in the mantissa is called the precision, p = 24 for
   single precision.
   The decimal value of the exponent is computed from the 8 bits
   less the bias (127). The decimal value of the mantissa is computed by
   adding the powers of 2 of each bit's position in the mantissa.
   The decimal point is set just after the most significant digit. From right
   to left the contribution of each binary digit at position n
   is given by

   bit(n) * 2^(-n)

   and the mantissa is the sum of all the 23 digits plus 1, the
   hidden digit.

   float sum = 1.0;
   for (int n = 23; n > 0; ++n)
    sum += bit[n] * 2^(-n);
*/
int char2bin(char c[], int i[], int length);
int exp2dec(int ie[], int len);
double mant2dec(int im[], int len);
int power(int base, int n);
int validbin(char c[], int len);

int main () {

  char exp_array[MAX_DIGITS_EXPONENT];
  char mant_array[MAX_DIGITS_MANTISSA];

  printf("Write the binary representation of the exponent\n");
  scanf("%s", exp_array);
  if (!validbin(exp_array, MAX_DIGITS_EXPONENT)) {
    printf("Input error. Use only binary digits: \'1\' or \'0\'.");
    return 0;
  }

  printf("Write the binary representation of the mantissa\n");
  scanf("%s", mant_array);
  if (!validbin(mant_array, MAX_DIGITS_MANTISSA)) {
    printf("Input error. Use only binary digits: \'1\' or \'0\'.");
    return 0;
  }

  // exponent
  int ie[MAX_DIGITS_EXPONENT];
  for (int i = 0; i < MAX_DIGITS_EXPONENT; i++)
    ie[i] = 0;

  char2bin(exp_array, ie, MAX_DIGITS_EXPONENT);

  int exp = exp2dec(ie, MAX_DIGITS_EXPONENT);
  printf("Floating-point exponent (dec): %d\n", exp);

  // mantissa
  int im[MAX_DIGITS_MANTISSA];
  for (int i = 0; i < MAX_DIGITS_MANTISSA; i++)
    im[i] = 0;

  char2bin(mant_array, im, MAX_DIGITS_MANTISSA);

  double mant = mant2dec(im, MAX_DIGITS_MANTISSA);
  printf("Floating-point mantissa (dec): %.10f\n", mant);

  // decimal value sign * mantissa * 2^(exponent)
  double value = mant * power(2, exp - EXPONENT_BIAS);
  printf("Value (dec): %.10f\n", value);

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
int exp2dec(int ie[], int len) {
  int exp = 0;
  for (int i = 0; i < len; i++)
    exp += ie[i] * power(2, len - i - 1);
  return exp;
}
/* Computes the decimal representation of the mantissa. */
double mant2dec(int im[], int len) {
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
int validbin(char c[], int len) {
  for (int i = 0; i < len; i++) {
    if (c[i] != '0' && c[i] != '1')
      return 0;
  }
}
