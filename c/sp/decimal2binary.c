#include <stdio.h>
#include <string.h> // strcmp(), strcpy(), strlen()
#include <math.h>  // frexp(), modf()
#define MAX_DIGITS_EXPONENT 8
#define MAX_DIGITS_MANTISSA 23
#define EXPONENT_BIAS 127
#define PRECISION 0.0000001

/*
   What we are more interested in to understand how floating-point arithmetic
   works is how to represent a decimal value as floating-point with 32 binary
   digits (single precision). The binary representation of a floating point
   number will help us to understand the rounding errors. The steps to represent
   a number in binary floating point are as follows
   1) put the number in normalized scientific notation, with a ratio and an
      exponent (base 2) so that we can convert the exponent and the mantissa separately
   2) Convert the exponent in binary
   3) For the mantissa, transform the ratio into binary form.
      We use two functions from the <math.h> library: frexp() and modf(). The
      first one is used to compute the normalized form of a number in order to have
      a fraction (ratio) r with 0<r<1 and an exponent e with base 2 (2^e). The
      second one is used to extract the integer part on the left of the decimal
      point, and the decimal part on the right.

*/
int getexp(int power);
void int2binary(int intnum, int bin[], int len);
void ratio2binary(double ratio, int bin[], int len);
int mant2dec(int im[], int len);
int power(int base, int n);

int main () {

  char exponent[MAX_DIGITS_EXPONENT];
  char mantissa[MAX_DIGITS_MANTISSA];

  float num;
  printf("Write the rational number (in decimal):\n");
  scanf("%f", &num);
  int powerb2;
  float ratio = frexp(num, &powerb2);  // ratio and exponent (base 2) of the input number
  printf("Normal form ratio %f, power (base 2): %d\n", ratio, powerb2);
  /*
  double integral;
  double fraction = modf(num, &integral);
  printf("Integral part.: %.0f, Fractional part. %f, \n", integral, fraction);
  */

  int exp = getexp(powerb2);
  printf("Floating-point exponent (dec): %d\n", exp);

  // initialization of the array for the exponent binary digits
  int exp_array[MAX_DIGITS_EXPONENT];
  for (int i = 0; i < MAX_DIGITS_EXPONENT; i++)
    exp_array[i] = 0;

  // Converts the floating-point exponent from decimal to binary
  int2binary(exp, exp_array, MAX_DIGITS_EXPONENT);
  printf("Floating-point exponent (binary): ");
  for (int i = 0; i < MAX_DIGITS_EXPONENT; i++)
    printf("%d", exp_array[i]);
  printf("\n");

  // initialization of the array for the mantissa binary digits
  int mant_array[MAX_DIGITS_MANTISSA];
  for (int i = 0; i < MAX_DIGITS_MANTISSA; i++)
    mant_array[i] = 0;

  // Converts the ratio from the normal form of the input number into binary
  ratio2binary(ratio, mant_array, MAX_DIGITS_MANTISSA);
  printf("Floating-point mantissa (binary): ");
  for (int i = 0; i < MAX_DIGITS_MANTISSA; i++)
    printf("%d", mant_array[i]);
  printf("\n");

  int mant = mant2dec(mant_array, MAX_DIGITS_MANTISSA);
  printf("Floating-point mantissa (dec): %d\n", mant);
}
/* Computes the floating-point exponent in decimal from the
   power of the input number in normal form.
*/
int getexp(int power) {
  return EXPONENT_BIAS + power - 1;
}
/* Converts an integer number from decimal to binary.
   The remainder of a division by 2 is always '1' or '0'.
*/
void int2binary(int intnum, int bin[], int len) {
  int remainder = 0;
  int i = 0;
  while (intnum != 0) {
    remainder = intnum % 2;
    if (remainder == 0)
      bin[len - 1 - i] = 0;
    else
      bin[len - 1 - i] = 1;
    i++;
    intnum /= 2;
  }

}
/* Computes the mantissa from the ratio of the input number in normal form. */
void ratio2binary(double ratio, int bin[], int len) {
  int i = 0;
  double init_integral; // not used
  double decimal = modf(ratio * 2, &init_integral);
  while (decimal > PRECISION) {
    double integral;
    double next_decimal = modf(decimal * 2, &integral);
    bin[i] = integral;
    decimal = next_decimal;
    //printf("i = %d, integral = %.0f, decimal = %f\n", i, bin[i], decimal);
    i++;
  }

}
/* Converts the mantissa from binary to decimal */
int mant2dec(int im[], int len) {
  int dec = 0;
  for (int i = 0; i < len; i++)
    dec += im[i] * power(2, len - i - 1);
  return dec;
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
