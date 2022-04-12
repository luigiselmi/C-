#include <stdio.h>
#include <string.h> // strcmp(), strcpy(), strlen()
#include <math.h>
#define MAX_DIGITS_EXPONENT 8
#define MAX_DIGITS_MANTISSA 24
#define BIAS 127

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

   and the mantissa is the sum of all the 23 digit plus 1, the
   hidden digit.

   float sum = 1.0;
   for (int n = 23; n > 0; ++n)
    sum += bit[n] * 2^(-n);

   What we are more interested in is how to represent a decimal value
   as floating point with 32 binary digits (single precision). The steps
   are as follows
   1) put the number in normalized scientific notation, e.g., if the number
      is 10 digits divide by 10^9
   2) transform the digit on the left of the decimal point into binary form
   3) transform the digits on the right of the decimal point into binary form

*/
int char2bin(char c[], int i[], int length);
int dec_exp(int ie[], int len);
double dec_mant(int im[], int len);
int power(int base, int n);
int dec2bin_exp(float num);
void bin_exp(int dec_exp, char bin[], int len);
void bin_mant(double dec_mant, char bin[], int len);

int main () {
  // binary to decimal
  char exponent[MAX_DIGITS_EXPONENT];
  char mantissa[MAX_DIGITS_MANTISSA];
  /*
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
  printf("Value (dec): %.10f\n", value_decimal);
  */
  // decimal to binary
  float decimal;
  printf("Write the rational number in decimal\n");
  scanf("%f", &decimal);
  int exp1;
  float ratio1 = frexp(decimal, &exp1);
  printf("Number (decimal): %.10f, Ratio %f, Exp.: %d\n", decimal, ratio1, exp1);

  double int2;
  double dec2 = modf(decimal, &int2);
  printf("Number (decimal): %.10f, Int.: %.0f, Dec. %f, \n", decimal, int2, dec2);
  // exponent
  int exp2 = dec2bin_exp(decimal);
  printf("Number (decimal): %.10f, Exponent %d\n", decimal, exp2);

  char bin[MAX_DIGITS_EXPONENT];
  for (int i = 0; i < MAX_DIGITS_EXPONENT; i++)
    bin[i] = 0;

  bin_exp(exp2, bin, MAX_DIGITS_EXPONENT);
  for (int i = 0; i < MAX_DIGITS_EXPONENT; i++)
    printf("%c", bin[i]);
  printf("\n");

  // mantissa
  char mant_array[MAX_DIGITS_MANTISSA];
  for (int i = 0; i < MAX_DIGITS_MANTISSA; i++)
    mant_array[i] = 0;

  bin_mant(ratio1, mant_array, MAX_DIGITS_MANTISSA);
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
  return exp - BIAS;
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
/* Computes the exponent to be used to convert
   a decimal number into a binary in floating
   point.
*/
int dec2bin_exp(float num) {
  int exp;
  float dec = frexp(num, &exp);
  return BIAS + exp - 1;
}
/* Converts a decimal number into a binary one.
   The remainder of a division by 2 is always '1' or '0'.
*/
void bin_exp(int dec_exp, char bin[], int len) {
  int remainder = 0;
  int i = 1;
  while (dec_exp != 0) {
    remainder = dec_exp % 2;
    if (remainder == 0)
      bin[len - i] = '0';
    else
      bin[len - i] = '1';
    i++;
    dec_exp /= 2;
  }
  bin[i] = '\0';
}
/* Computes the mantissa in binary format of a number in decimal */
void bin_mant(double dec_mant, char bin[], int len) {
  printf("Mantissa (dec): %f\n", dec_mant);
}
