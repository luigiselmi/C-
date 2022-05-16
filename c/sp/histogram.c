#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 10000
#define MAX_BINS 100

int defineInput(double buf[], int max);
void fillDist(double *data , int *bin , double min , double max , int n, int nData );
void printHisto(int *bin , int n);

int main () {
  int k, bins , entries , content[MAX_BINS] = {0};
  int seed;
  double xmin , xmax;
  double data[MAX_NUM ];
  seed = time (0);
  srand48(seed );
  entries = defineInput (data , MAX_NUM );
  printf (" Enter the limits of the histogram\n xmin = ");
  scanf ("%lf",&xmin );
  printf (" xmax = ");
  scanf ("%lf",&xmax );
  do {
   printf (" Enter the number of bins = ");
   scanf ("%d",&bins );
  } while (bins <= 0 || bins > MAX_BINS );

 fillDist(data , content , xmin , xmax , bins , entries );

 printHisto(content , bins );

 exit(EXIT_SUCCESS );
}
/*
  Creates an array of uniformly random numbers.
*/
int defineInput(double buf[], int max) {
  int k, N;
  do {
    printf (" Number of events = ");
    scanf ("%d", &N);
  } while (N < 0 || N > max);

  for(k = 0; k < N; k++) {
    buf[k] = (double)lrand48 () / (RAND_MAX + 1.);
  }
  return N;
}
/*
  Fills the bins of the histogram from the input data according to the size of the bins.
*/
void fillDist(double *data , int *bin , double min , double max , int n, int nData) {
  int i, j;
  double invWidth = (double)n / (max - min);
  for (i = 0; i < nData; i++) {
    j = ((*( data + i) - min) * invWidth );
    if (j < n && j >=0)
      (*( bin+j))++;
  }
}
/*
  Prints the histogram. It builds a 2D array of characters number_of_bins x height.
*/
void printHisto(int *bin , int n) {
  int i, j, max;
  int maxChar = 100;
  char c = '*', empty = ' ', hist[n + 2][ maxChar + 1];

  for (i = 0; i < n + 2; i++) {
    for (j = 0; j < maxChar; j++) {
      hist[i][j] = empty;
    }
  }

  max = bin [0];
  for (i = 1; i < n; i++) {
    if (bin[i] > max) {
      max = bin[i];
    }
  }

  if (max > maxChar) {
    max = maxChar;
  }

  for (j = 0; j <= max; j++) {
    hist [0][j] = '|';
  }

  hist [0][0] = hist [1][0] = '_';
  for (i = 2; i < n + 2; i++) {
    hist[i][0] = '_';
    for (j = 0; j < *(bin + i - 2); j++) {
      hist[i][j + 1] = c;
    }
  }

  for (j = max; j >= 0 ; j--) {
    for (i = 0; i < n + 2; i++) {
      printf ("%c", hist[i][j]);
    }
    printf ("\n");
  }
}
