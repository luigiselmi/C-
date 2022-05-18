/*
  Computes the Lagrange polynomial from
  data read from a file.
  Compile using the command:

  $ cc lagrange_polynomial.c parse_data_points.c -o lagrange

*/
#include <stdio.h>
#include <stdlib.h> // exit()
#include <math.h> // sqrt()
#include "parse_data_points.h" // declare the functions _open() and
                               // parse() used to read the input file
                               // and to create an array of points

double lagrange(double y, int n, struct point data[]);

int main(int argc, char *argv[]) {
   FILE *fp;  // pointer to a file
   int N; // number of data points
   const double sigma = 0.01; // measurement error (or variance)

   if (argc == 1) { // no files to open
      printf("The input data file is missing.");
      exit(1);
   }
   else
     fp = _open(argc, argv);

   fscanf(fp, "%d", &N);
   struct point data[N];
   parse(fp, data);
   fclose(fp);

   double x_0 = 1.5, y_0 = -0.25;
   double y = lagrange(x_0, N, data);

   printf("y = %.3f, y - y0 = %.3f\n", y, y - y_0);

   exit(0);
}
/*
  Computes the value of the Lagrange polynomial at a
  point y.
*/
double lagrange(double y, int n, struct point data[]) {
  double P, S = 0.;
  int i, j;

  for (i = 0; i < n; i++) {
    P = 1.;
    for (j = 0; j < n; j++) {
      if (j != i) {
        P *= (y - data[j].x) / (data[i].x - data[j].x);
      }
    }
    S += P * data[i].y;
  }
 return S;
}
