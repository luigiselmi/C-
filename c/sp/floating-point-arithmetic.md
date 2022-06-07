Floating-point arithmetic
=========================
## Binary to decimal
In single precision a floating point number is represented
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

```
bit(n) * 2^(-n)
```
and the mantissa is the sum of all the 23 digits plus 1, the
hidden digit.

```
float sum = 1.0;
for (int n = 23; n > 0; ++n)
 sum += bit[n] * 2^(-n);
```
## Decimal to binary
What we are more interested in to understand how floating-point arithmetic
works is how to represent a decimal value as floating-point with 32 binary
digits (single precision). The binary representation of a floating point
number will help us to understand the rounding errors. The steps to represent
a number in binary floating point are as follows
1. put the number in normalized scientific notation, with a ratio and an
   exponent (base 2) so that we can convert the exponent and the mantissa separately  
2. Convert the exponent in binary  
3. For the mantissa, transform the ratio into binary form.
   We use two functions from the <math.h> library: frexp() and modf(). The
   first one is used to compute the normalized form of a number in order to have
   a fraction (ratio) r with 0<r<1 and an exponent e with base 2 (2^e). The
   second one is used to extract the integer part on the left of the decimal
   point, and the decimal part on the right.  
