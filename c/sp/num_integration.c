/*
  Numerical integration using the rectangle rule.
  The integral of a function f(x) defined over an
  interval [a, b] is computed by dividing the interval
  in M segments of length d = (b - a) / M over which
  the function is assumed constant, so that the area
  of integral on each segment is Im = f(a + d * m) * d
  and the integral I of the function is the sum of the
  area of each interval.
*/
#include <stdio.h>
#include <math.h>

double func(double);
double integral(double (*f)(double), double a, double b, int m);
/*
  The main function computes the integrals of a function
  dividing the integral in smaller segments each time.
*/
int main () {
  double a = 0.0, b = 1.0;
  int m = 10; // number of segments in which the interval [a, b] is divided.
  printf ("Num. segments | Integral\n\n");
  while (m < 1e+6) {
    printf ("%-15d %.4f\n", m, integral(func , a, b, m));
    m *= 10;
  }
}
/*
  The function to be integrated.
*/
double func(double x) {
  return sin(x);
}
/*
  The function implements the integration operator that is
  applied to the function passed as an argument by a pointer.
  The function argument takes a double and returns a double.
*/
double integral(double (*f)(double), double a, double b, int m) {
  double d = (b - a) / (double) m;
  double I = 0.0, x;
  for (int i = 0; i < m; i++) {
    x = a + d * i;
    I += (*f)(x);
  }
  return I * d;
}
