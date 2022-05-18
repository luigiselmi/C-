/*
  Computes the linear interpolation from data
  read on a file using the least squares method.
*/
#include <stdio.h>
#include <stdlib.h> // exit()

struct point {
  double x;
  double y;
};

int parse(FILE *source, struct point data[]);

int main(int argc, char *argv[]) {
   FILE *fp;  // pointer to a file
   char *prog = argv[0];
   int N;

   if (argc == 1) {// no files to open
      printf("The input data file is missing.");
      exit(1);
   }
   else
      while (--argc > 0)
         if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "The file \'%s\' cannot be opened.\n", *argv);
            exit(1);
         }
         else {
            fscanf(fp, "%d", &N);
            struct point data[N];
            parse(fp, data);
            for (int i = 0; i < N; i++)
               printf("%d) x = %f, y = %f\n", i, data[i].x, data[i].y);
            fclose(fp);
         }

   if (ferror(stdout)) {
      fprintf(stderr, "%s: error writing on stdout.\n", prog);
      exit(2);
   }

   exit(0);
}
FILE *open(int argc, char *argv[]) {
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
