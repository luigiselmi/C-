/*
  Computes the linear interpolation y = A + Bx from
  data read from a file using the least squares method.
  Compile using the command:

  $ cc interpolation.c parse_data_points.c -o interpolation

*/
#include <stdio.h>
#include <stdlib.h> // exit()
#include <math.h> // sqrt()
#include "parse_data_points.h" // declare the functions _open() and
                               // parse() used to read the input file
                               // and to create an array of points

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

   double S, Sx, Sy;

   double s2 = sigma * sigma;
   for (int i = 0; i < N; i++) {
     Sx += data[i].x  / s2;
     Sy += data[i].y  / s2;
     S += 1. / s2;
   }

   double Stt, tt, A, B, sigma_A, sigma_B;
   for (int i = 0; i < N ; i++) {
     tt = (data[i].x - Sx / S) / sigma;
     Stt += tt * tt;
     B += tt * data[i].y / sigma;
   }

   B /= Stt;
   A = (Sy - Sx * B) / S;

   sigma_A = sqrt ((1. + Sx * Sx / (S * Stt)) / S);
   sigma_B = sqrt (1./ Stt);

   printf("A = %.2f, sigma_A = %.2f\n", A, sigma_A);
   printf("B = %.2f, sigma_B = %.2f\n", B, sigma_B);

   exit(0);
}
