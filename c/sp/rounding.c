#include <stdio.h>

//#define N 10000000
#define N 2396747
/* This program shows the errors than can arise while
   working with rational numbers. These errors affects
   particularly non-linear systems for which small
   differences of initial conditions may produce very
   different results (see Lorentz on Meteorology, Ruelle
   on Chaos Theory, ensemble forecasting). Therefore
   it is fundamental to understand what errors may arise
   and how to avoid them.  
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
