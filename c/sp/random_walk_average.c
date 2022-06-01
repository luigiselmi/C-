/*
  The program performs a number of random walks, each walk made
	up of a number of random steps leftward (-1) or rightward (+1).
	At each step x the program takes a sample for each random walk,
	computes the sum of x^2 and its error x^4 and put them in an array.
	After the random walks are completed, computes the average values of
	x^2 and its error at each step and writes the values on a file. The
	data can be plotted using gnuplot and the command:

	gnuplot> plot 'rw1d_ave.dat'

	Credit: Barone et al. - Scientific Programming, https://chimera.roma1.infn.it/SPENG/
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MY_EXIT_SUCCESS       0
#define MY_EXIT_FAILURE      -9

typedef unsigned long long RANDOM_TYPE;

FILE *fDat;

/*********************************/
int main(void) {

  long i, j, numberOfSteps = 100000, numberOfSamples = 5000;
  long position;
  double doubleM, iDoubleM;
  double *x2Average, *x2Error;
  RANDOM_TYPE a, seed, randomNumber;

  fDat = fopen("rw1d_ave.dat","w");
  if(fDat == NULL){
    printf("Error: can't open the file with write permissions\n");
    exit(MY_EXIT_FAILURE);
  }

  a = 1181783497276652981;
  seed = 131419;

  doubleM = pow(2.,64.);
  iDoubleM = 1.0 / doubleM;

  printf("# a = %Lu m = 2^64 I0 = %Lu\n", a, seed);
  printf("# Number of steps made by the traveler: %d\n", numberOfSteps);
  printf("# Number of samples: %d\n", numberOfSamples);
  fprintf(fDat, "# a = %Lu m = 2^64 I0 = %Lu\n", a, seed);
  fprintf(fDat, "# Number of steps made by the traveler: %d\n",
	  numberOfSteps);
  fprintf(fDat, "# Number of samples: %d\n", numberOfSamples);

  if(sizeof(RANDOM_TYPE) < 8){
    printf("Error: RANDOM_TYPE must be at least 8 byte,"
	   " but it's  %d\n", sizeof(RANDOM_TYPE));
    exit(MY_EXIT_FAILURE);
  }

  x2Average = calloc(numberOfSteps, sizeof(double));
  if (x2Average == NULL) {
    printf("Error: calloc for x2Average failed\n");
    exit(MY_EXIT_FAILURE);
  }
  x2Error = calloc(numberOfSteps, sizeof(double));
  if (x2Error == NULL) {
    printf("Error: calloc for x2Error failed\n");
    exit(MY_EXIT_FAILURE);
  }

  randomNumber = seed;

  for (j = 0; j < numberOfSamples; j++) {
    position = 0;
    for (i = 0; i < numberOfSteps; i++) {
      double r, x, x2, x4;
      randomNumber = a * randomNumber;
      r = (double)randomNumber * iDoubleM;
      if(r < 0.5){
	      position += 1;
      }
			else {
	      position -= 1;
      }
      x = (double)position;
      x2 = x * x;
      x4 = x2 * x2;
      x2Average[i] += x2;
      x2Error[i] += x4;
    }
  }
  for (i = 0; i < numberOfSteps; i++) {
    x2Average[i] /= (double) numberOfSamples;
    x2Error[i] /= (double) numberOfSamples;
    x2Error[i] -= (x2Average[i] *  x2Average[i]);
    if (numberOfSamples > 1) {
      x2Error[i] /= (double) (numberOfSamples - 1);
    }
		else {
      x2Error[i] = 0.0;
    }
    if (x2Error[i] > 0.0) {
      x2Error[i] = sqrt(x2Error[i]);
    }
		else {
      x2Error[i] = 0.0;
    }
    fprintf(fDat, "%ld %lg %lg\n", i+1, x2Average[i], x2Error[i]);
  }
  fclose(fDat);
}
