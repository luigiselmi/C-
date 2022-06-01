/*
  The program performs a number of random steps (e.g. 100000)
	leftward (-1) or rightward (+1), in one dimension and writes
	the position at each step on a file. The final position depends
	on the seed. The data can be plotted using gnuplot and the
	command:
	 
	gnuplot> plot 'rw1d.dat'
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

  long i, numberOfSteps = 1000000;
  long position;
  double doubleM, iDoubleM;
  RANDOM_TYPE a, seed, randomNumber;

  fDat = fopen("rw1d.dat","w");
  if(fDat == NULL){
    printf("Error: can't open the file with write permissions\n");
    exit(MY_EXIT_FAILURE);
  }

  a = 1181783497276652981;
  seed = 131419;

  doubleM = pow(2.,64.);
  iDoubleM = 1.0 / doubleM;

  printf("# a = %Lu m = 2^64 I(0) = %Lu\n", a, seed);
  printf("# Number of steps made by the traveler: %d\n", numberOfSteps);
  fprintf(fDat, "# a = %Lu m = 2^64 I0 = %Lu\n", a, seed);
  fprintf(fDat, "# Number of steps made by the traveler: %d\n", numberOfSteps);

  if(sizeof(RANDOM_TYPE)<8){
    printf("Error: RANDOM_TYPE must be at least 8 bytes,"
	   " but it's  %d\n", sizeof(RANDOM_TYPE));
    exit(MY_EXIT_FAILURE);
  }

  randomNumber = seed;
  position = 0;

  for(i = 0; i < numberOfSteps; i++){
    double r;
    fprintf(fDat, "%d %d\n", i, position);
    randomNumber = a * randomNumber;
    r = (double)randomNumber * iDoubleM;
    if(r < 0.5){
      position += 1;
    }else{
      position -= 1;
    }
  }
  fprintf(fDat, "%d %d\n", i, position);
  fclose(fDat);
	printf("Position at the last step: %d", position);
}
