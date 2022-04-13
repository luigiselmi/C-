#include <stdio.h>
#include <string.h> // strcmp(), strcpy(), strlen()
#include <math.h>
#define MAX_DIGITS_EXPONENT 8
#define MAX_DIGITS_MANTISSA 23
#define BIAS 127

/*
   What we are more interested in is how to represent a decimal value
   as floating point with 32 binary digits (single precision). The steps
   are as follows
   1) put the number in normalized scientific notation, e.g., if the number
      is 10 digits divide by 10^9
   2) transform the digit on the left of the decimal point into binary form
   3) transform the digits on the right of the decimal point into binary form

*/

int power(int base, int n);
int dec2bin_exp(float num);
void bin_exp(int dec_exp, int bin[], int len);
void bin_mant(double dec_mant, int bin[], int len);
int dec2bin_mant(int im[], int len);

int main () {

  char exponent[MAX_DIGITS_EXPONENT];
  char mantissa[MAX_DIGITS_MANTISSA];

  float decimal;
  printf("Write the rational number in decimal\n");
  scanf("%f", &decimal);
  int exp1;
  float ratio1 = frexp(decimal, &exp1);
  printf("Ratio %f, Exp.: %d\n", ratio1, exp1);

  double int2;
  double dec2 = modf(decimal, &int2);
  printf("Int.: %.0f, Dec. %f, \n", int2, dec2);
  // exponent
  int exp2 = dec2bin_exp(decimal);
  printf("Number (decimal): %.10f, Exponent %d\n", decimal, exp2);

  int bin[MAX_DIGITS_EXPONENT];
  for (int i = 0; i < MAX_DIGITS_EXPONENT; i++)
    bin[i] = 0;

  bin_exp(exp2, bin, MAX_DIGITS_EXPONENT);
  printf("Exponent: ");
  for (int i = 0; i < MAX_DIGITS_EXPONENT; i++)
    printf("%d", bin[i]);
  printf("\n");

  // mantissa
  int mant_array[MAX_DIGITS_MANTISSA];
  for (int i = 0; i < MAX_DIGITS_MANTISSA; i++)
    mant_array[i] = 0;


  bin_mant(ratio1, mant_array, MAX_DIGITS_MANTISSA);
  printf("32-bit (float) mantissa (bit 23 to 1): ");
  for (int i = 0; i < MAX_DIGITS_MANTISSA; i++)
    printf("%d", mant_array[i]);
  printf("\n");

  int dec_mant = dec2bin_mant(mant_array, MAX_DIGITS_MANTISSA);
  printf("Mantissa from binary (dec): %d\n", dec_mant);
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
void bin_exp(int dec_exp, int bin[], int len) {
  int remainder = 0;
  int i = 0;
  while (dec_exp != 0) {
    remainder = dec_exp % 2;
    if (remainder == 0)
      bin[len - 1 - i] = 0;
    else
      bin[len - 1 - i] = 1;
    i++;
    dec_exp /= 2;
  }

}
/* Computes the mantissa in binary format of a number in decimal */
void bin_mant(double dec_mant, int bin[], int len) {
  printf("Mantissa (dec): %f\n", dec_mant);
  int i = 0;
  double precision = 0.00001;
  double init_integral;
  double init_decimal = modf(dec_mant * 2, &init_integral);
  printf("Start: integral = %.0f, decimal = %f\n", init_integral, init_decimal);
  double decimal = init_decimal;
  double integral = init_integral;
  while (decimal > precision) {
    double integral;
    double next_decimal = modf(decimal * 2, &integral);
    bin[i] = integral;
    decimal = next_decimal;
    //printf("i = %d, integral = %.0f, decimal = %f\n", i, bin[i], decimal);
    i++;
  }

}
/* Converts from the binary to the the decimal representation of the mantissa */
int dec2bin_mant(int im[], int len) {
  int mant = 0;
  for (int i = 0; i < len; i++)
    mant += im[i] * power(2, len - i - 1);
  return mant;
}
