/*
  Numerical integration of a function using the
  sample-mean Monte Carlo statistical method.
  We assume the integration of a function f(x) over an
  interval [a, b]. The integral can be approximated
  to the average value of N samples of f(x)/P(x) where
  P(x) is a distribution function and a <= x <= b.
  If we use the uniform distribution over the interval
  [a, b] then P(x) = 1 / (b - a).
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double mc_integral(double (*f)(double), double a, double b, int N);
double func(double x);

int main() {
  double a = 0.0, b = 1.0;
  int N = 10; // number of random samples
  int seed = 123;
  srand(seed);
  printf ("Num. samples | MC Integral\n\n");
  while (N < 1e+6) {
    printf ("%-15d %.4f\n", N, mc_integral(func , a, b, N));
    N *= 10;
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
double mc_integral(double (*f)(double), double a, double b, int N) {
  double I = 0.0, x;
  for (int i = 0; i < N; i++) {
    x = a + (b - a) * (double)lrand48 () / (double)RAND_MAX;
    I += (*f)(x);
  }
  return I * (b - a) / N;
}
