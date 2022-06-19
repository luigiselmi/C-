/*
  
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NUM_ITER 200
#define L (2 * NUM_ITER)

typedef unsigned long long RANDOM_TYPE;
typedef char CELLULAR_AUTOMA;

/* Random number that could be used for a random
   initialization of the lattice sites  */
#define MYR64  myr64 = (6364136223846793005ULL * myr64)
#define MAX_RAND64     0XFFFFFFFFFFFFFFFFULL
RANDOM_TYPE myr64;
double inverseMaxRand64 = 1.0L / (double) MAX_RAND64;

CELLULAR_AUTOMA C[L], CP[L];
int rule = 150;
//int rule = 90;

FILE *fDat;

#define FAILURE -9
#define SUCCESS 1

/**************************************************/
int main(void) {
  long time, site;

	fDat = fopen("automaton.dat","w");
  if(fDat == NULL) {
    printf("Error: can't open the file with write permissions\n");
    exit(1);
  }

  for (site = 0; site < L; site++) {
    C[site] = 0;
    CP[site] = 0;
  }

  C[L / 2] = 1;
  printf("# The rule is %d\n", rule);

  for (time = 0; time < NUM_ITER; time++) {
    for (site = 0; site < L; site++) {
      //printf("X %ld T %ld CELLA %d\n", site - L / 2, time, C[site]);
			fprintf(fDat, "%d ", C[site]);
    }
		fprintf(fDat, "\n");
    /* synchronous update */
    for (site = 1; site < L - 1; site++) {
      if (rule == 90) {
	      /* rule 90 corresponds to the XOR of the two nearest neighbors */
	      CP[site] = C[site - 1] ^ C[site + 1];
      }
			else if (rule == 150) {
	      /* rule 150: XOR of the two nearest neighbors, and XOR with itself */
	      CP[site] = (C[site - 1] ^ C[site + 1]) ^ C[site];
      }
			else {
	      printf("Error: rule undefined\n");
	      exit(FAILURE);
      }
    }
    /* copies CP in C */
    for (site = 0; site < L; site++) {
      C[site] = CP[site];
    }
  }
	/*
  for (site = 0; site < L; site++) {
    printf("X %ld T %ld CELL %d\n", site - L / 2, time, C[site]);
  }
	*/
	printf("Data automaton.dat file ready.");
	fclose(fDat);
  return SUCCESS;
}
