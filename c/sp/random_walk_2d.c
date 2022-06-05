/*
  The program performs a number of random walks on a 2-dimensional
	square lattice. At each step the traveler can move eastward,
	westward, northward or southward with equal probability 1/4.
	Therefore each random walk is made up of a fixed number of random
	steps. At each step t the program computes the squared absolute
	value of the distance from the origin x^2(t) and its error x^4(t)
	and adds them to the values computed in the preceding random walks
	stored in an array.
	After all the random walks (samples) are completed, the program
	computes the average values of x^2 and its error for each step
	and writes the values on a file. The average values of x^2 at step t,
	<x^2(t)> represents the (squared) probability for the traveler to
	be at position x in the square lattice.
	The <x^2(t)> data can be plotted using gnuplot and the command:

	gnuplot> plot 'rw2d_ave.dat'

  From the plot it can be seen that <x^2(t)> is linear according to the
	theory that says

	<x^2(t)> = a^2 * t / D

  where a is the length of the edges between two nodes of the square
	lattice (in our case a = 1), t is the step (or time), and D is the
	dimension (in our case D = 2). The above equation has been determined
	from the probability distribution of traveler position in the square
	lattice as a function of the position x = (x1, x2) and the step (time)

	P(x, t) = (D / 2*Pi*t)^(D/2) * exp(-Dx^2 / 2*t*a^2 )

	so that <x^2(t)> = S(x^2 * P(x, t)dx)  (S represents the integration operator)

  The application also stores in another file, rw2d_prob.dat, the position
	(x1, x2) at each step of any random walk (sample) that is a power of 10
	between 1 and 5, that is 10, 100, 1000, 10000 and 100000. We can plot the
	distribution of the positions achieved by the random traveler after, for
	instance 100 steps, in all the random walks. The position reached after
	100 steps will be distributed around a value of (100/2)^(1/2), that is 7.07.
	We can filter the data from the file to consider only the position after 100
	steps

	$ grep "T 99 " rw2d_prob.dat > rw2d_prob_100.dat

	If we use gnuplot to plot the data we set the range for x1 and x2

	gnuplot> set xrange [-300:300]
  gnuplot> set yrange [-300:300]

	then we plot the filtered data

	gnuplot> plot 'rw2d_prob_100.dat' using 6:8 linecolor 'blue'

  if we repeat the experiment filtering the data to extract the position
	after, let's say, 10000 step we will see the the distribution is much
	larger and the points are more dispersed.

	Another experiment is to compute the number of times a certain position
	in the square lattice has been reached by the random traveler after a
	certain number of steps. For instance, we can count the number of times
	the traveler went through the point at (0, 0) after 100 steps

	$ grep "T 99 X1 0 X2 0" rw2d_prob.dat |wc -l
	59

	If we repeat the test for the position (10, 10)

	$ grep "T 99 X1 10 X2 10" rw2d_prob.dat |wc -l
  4

	we see that it's much less likely. We can compute the values for all the
	points in the square lattice, within the ranges we have set above, to have
	the probability distribution for t = 100 or for any other value of t for
	which we have the data.  

	Credit: Barone et al. - Scientific Programming, https://chimera.roma1.infn.it/SPENG/
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MY_EXIT_SUCCESS       0
#define MY_EXIT_FAILURE      -9

typedef unsigned long long RANDOM_TYPE;

FILE *fDat, *fProb;

/*********************************/
int main(void) {

  long i, j, k, numberOfSteps = 100000, numberOfSamples = 10000;
  long numberOfPowers, thisPower, maxPower, *allPowers;

  struct x {
    long x1;
    long x2;
  } position;

	double doubleM, iDoubleM;
  double *x2Average, *x2Error;
  RANDOM_TYPE a, seed, randomNumber;

  fDat = fopen("rw2d_ave.dat","w");  // <x^2(t)>
  if (fDat == NULL) {
    printf("Error: can't open the file to store the average values\n");
    exit(MY_EXIT_FAILURE);
  }

  fProb = fopen("rw2d_prob.dat","w"); // (x1, x2) at t = {10, 100, 1000, ..}
  if (fProb == NULL) {
    printf("Error: can't open the file to store the probabilities'\n");
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
  fprintf(fProb, "# a = %Lu m = 2^64 I0 = %Lu\n", a, seed);
  fprintf(fProb, "# Number of steps made by the traveler: %d\n",
	  numberOfSteps);
  fprintf(fProb, "# Number of samples: %d\n", numberOfSamples);

  if (sizeof(RANDOM_TYPE) < 8) {
    printf("Error: RANDOM_TYPE must be at least 8 bytes,"
	   " but it is  %d\n", sizeof(RANDOM_TYPE));
    exit(MY_EXIT_FAILURE);
  }

  x2Average = calloc(numberOfSteps, sizeof(double));
  if (x2Average == NULL) {
    printf("Error: the calloc for x2Average failed\n");
    exit(MY_EXIT_FAILURE);
  }
  x2Error = calloc(numberOfSteps, sizeof(double));
  if (x2Error == NULL) {
    printf("Error: the calloc for x2Error failed\n");
    exit(MY_EXIT_FAILURE);
  }

  /* let's find out which power of 10 of the number of step we can store */
  if(numberOfSteps < 10){
    printf("Error: numberOfSteps is too small for this analysis\n");
    exit(MY_EXIT_FAILURE);
  }
  numberOfPowers = 1;
  maxPower = 10;
  do {
    numberOfPowers++;
    maxPower *= 10;
  } while (maxPower <= numberOfSteps);

  numberOfPowers--;
  maxPower /= 10;
  allPowers = malloc(sizeof(long)*numberOfPowers);

  thisPower = 10;
  for (i = 0; i < numberOfPowers; i++) {
    allPowers[i] = thisPower - 1;
    thisPower *= 10;
  }

  randomNumber = seed;

  for (j = 0; j < numberOfSamples; j++) { // each sample is a complete random walk of a numberOfSteps
    position.x1 = 0;
    position.x2 = 0;
    k = 0;
    for (i = 0; i < numberOfSteps; i++) {
      double r, x2, x4;
      randomNumber = a * randomNumber;
      r = (double)randomNumber * iDoubleM;
      if(r < 0.25) {
	      position.x1 += 1;  // eastward direction
      }
			else if (r < 0.5) {
	      position.x1 -= 1;  // westward direction
      }
			else if(r < 0.75) {
	      position.x2 += 1;  // northward direction
      }
			else {
	      position.x2 -= 1;  // southward direction
      }
      x2 = position.x1 * position.x1 + position.x2 * position.x2;
      x4 = x2 * x2;
      x2Average[i] += x2;
      x2Error[i] += x4;
      if (i == allPowers[k]) { // if step is a power of k we store the position (x1, x2)
	      k++;
	      fprintf(fProb, "S %ld T %ld X1 %ld X2 %ld\n", j, i, position.x1, position.x2);
      }
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
  fclose(fProb);
	printf("Step = %ld, <x^2> = %lg, <delta(x^2)> = %lg\n", i, x2Average[i - 1], x2Error[i - 1]);
}
