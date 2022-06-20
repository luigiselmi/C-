/*
  This program implements a one-dimensional cellular automaton,
	a lattice of N sites in which the state of a site at time
	t + 1 depends on its own state and on the states of its
	nearest neighbors at time t, according to a very simple rule.
	Since the state of a site A at time t + 1 depends on the state
	of three sites at time t, that is $2^3 = 8$ states, site A may
	have one of $2^8 = 256$ state at time t + 1. In this example a
	site may have at any time one of two possible states from the
	set {0, 1}. The rules implemented in this example are rule 90 and
	rule 150 in the Wolfram classification. Rule 90 is a XOR
	between a site neighbors. Rule 150 is a XOR of the two nearest
	neighbors, and a XOR with itself. The interesting outcome of the
	cellular automaton is that even if the rules are local, that
	is the state of any site depends only on its previous state
	and on that of its nearest neighbors, they may produce
	correlations at long distances. The initial state of
	the lattice at time t = 0 has all the sites at state 0 but
	the central site N/2 at state 1. The program creates a file
	in which each line represents the state of the lattice at
	different times. The data can be plotted using gnuplot with
	the lattice in the horizontal axis and the time in the vertical
	axis.

	Original code:
	https://chimera.roma1.infn.it/SPENG//PROGRAMMI/cap14/cap14_automa.c

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
