/*
  Computes the linear interpolation from data
  read on a file using the least squares method.
  Compile using the command:

  $ cc interpolation.c parse_data_points.c -o interpolation

*/
#include <stdio.h>
#include <stdlib.h> // exit()
#include "parse_data_points.h" // declare the functions used to read
                               // the input file and to create an array of points


int parse(FILE *source, struct point data[]);
FILE *_open(int argc, char *argv[]);

int main(int argc, char *argv[]) {
   FILE *fp;  // pointer to a file
   int N; // number of data points

   if (argc == 1) { // no files to open
      printf("The input data file is missing.");
      exit(1);
   }
   else
     fp = _open(argc, argv);

   fscanf(fp, "%d", &N);  // reads the number of lines
   struct point data[N];
   parse(fp, data);

   for (int i = 0; i < N; i++)
      printf("%d) x = %f, y = %f\n", i, data[i].x, data[i].y);

   fclose(fp);

   exit(0);
}
