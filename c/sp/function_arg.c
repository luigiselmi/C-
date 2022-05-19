/*
  A function can be passed as an argument to
  another function, for example to a function
  that implements a mathematical operator. The
  main function computes the derivative of a
  function reducing each time the delta. It is
  shown that the value of the derivative gets
  wrong when the delta is too small.
*/
#include <stdio.h>

double func(double );
double derivative(double (*)( double), double , double );

int main () {
  double delta = 1.;
  printf ("delta | derivative\n\n");
  while (delta > 1.e-18) {
    printf ("%e %f\n", delta , derivative(func , 1., delta ));
    delta /= 10.;
  }
}

double func(double x) {
  return x * x;
}
/*
  The function implements the derivative operator that is
  applied to the function passed as an argument by a pointer.
  The function argument takes a double and returns a double.
*/
double derivative(double (*f)( double), double x, double delta) {
  return ( f(x + delta) - f(x) ) / delta;
}
