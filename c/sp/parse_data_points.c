/*
  Reads a file of data points. The first line
  contains the number of lines containing a
  data point. A point is a pair of double
  separated by comma, e.g.:

  4
  0.2, 1.2
  1.0, 2.0
  2.0, 3.0
  2.5, 3.5

  The program provides two functions, one to open
  the input data file and one to load the data point
  in an array of struct. Uncomment the main function
  to test them.
*/
#include <stdio.h>
#include <stdlib.h> // exit()

struct point {
  double x;
  double y;
};

/*
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
*/
/*
  Opens the input data file and return its pointer.
*/
FILE *_open(int argc, char *argv[]) {
  FILE *fp;
  while (--argc > 0)
   if ((fp = fopen(*++argv, "r")) == NULL) {
         fprintf(stderr, "The file \'%s\' cannot be opened.\n", *argv);
         exit(1);
   }

   return fp;
}
/*
  Parses the input data file and fills an array of points.
*/
int parse(FILE *source, struct point data[]) {
   double x, y;
   int line, i = 0;
   while ((line = fscanf(source, "%lf, %lf", &x, &y)) != EOF) {
      data[i].x = x;
      data[i].y = y;
      i++;
   }
   return 0;
}
