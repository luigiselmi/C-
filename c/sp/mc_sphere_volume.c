/*
  Computes the volume of a sphere using the
  Monte Carlo method. The sphere is inscribed
  in a cube that delimits the values of the
  x, y and z coordinates. The volume of the
  sphere is proportional to the ratio of the
  random points P(x, y, z) that happen to fall
  inside the sphere to the total number of
  sampled points.
*/
#include <stdio.h>
#include <stdlib.h>

double mc_volume(int N);

#define L 2      // length of cube side
#define R 1      // sphere radius
/*
  The volume is computed several time using
  an increasing number of random samples.
*/
int main() {
  int N = 10; // number of random sample
  int seed = 123;
  srand(seed);
  printf ("Num. samples | Volume\n\n");
  while (N < 1e+8) {
    printf ("%-15d %.4f\n", N, mc_volume(N));
    N *= 10;
  }
}
/*
  Computes the volume of a sphere using the
  Monte Carlo method.
*/
double mc_volume(int N) {
  double x, y, z, V;
  int i = 0, k = 0;
  for (i = 0; i < N; i++) {
    x = L * (double)lrand48 () / RAND_MAX;
    y = L * (double)lrand48 () / RAND_MAX;
    z = L * (double)lrand48 () / RAND_MAX;
    if ((x * x + y * y + z * z) < (R * R)) {
      k++;
    }
  }
  V = (double )(L * L * L) * k / N;

  return V;
}
