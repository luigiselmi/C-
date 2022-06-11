/*
  This program is used to show the usage of the union
	variable type. A union is used to represent a variable
	that can be of different types. Its sintax is like a
	struct but it may have only one value at each time and
	the size of the variable is equal to the number of bytes
	of its largest member.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MY_SUCCESS 1
#define MY_FAILURE -9

#define MY_SEED 5467891

#define EXP_SPEED 0
#define EXP_JET 1
#define EXP_ERROR 2
#define EXP_RANDOM 3

union experimentData{
  double speed;
  int num;
  char *errorMessage;
};

char *experimentError[3] = {
  "Slow Trigger", "Boundary Detection",
  "Memory Fault"
};

unsigned long int numExperimentOutput[3] = {0};
unsigned long int setExperiment(unsigned long int experimentNumber);
union experimentData experimentBody(unsigned long int experimentOutput);
void analyzeExperiment(unsigned long int experimentOutput, union experimentData newData);
void myEnd(unsigned long int experimentNumber);
double averageSpeed = 0.0;
unsigned long hystogramNumber[5] = {0};

/**************************************************/
int main(void)
{
  unsigned long int experimentOutput = 1;
  unsigned long int experimentNumber = 0;

  srand(MY_SEED);
  while (experimentOutput < 4) {
    union experimentData scratchData;
    experimentNumber++;
    experimentOutput = setExperiment(experimentNumber);
    scratchData = experimentBody(experimentOutput);
    analyzeExperiment(experimentOutput, scratchData);
  }
  myEnd(experimentNumber);
}

/**************************************************/
void analyzeExperiment(unsigned long int experimentOutput, union experimentData newData) {
  if (experimentOutput == EXP_SPEED) {
    averageSpeed += newData.speed;
  }
  if (experimentOutput == EXP_JET) {
    hystogramNumber[newData.num]++;
  }
  if (experimentOutput == EXP_ERROR) {
    printf("Experiment failed: %s\n", newData.errorMessage);
  }
}

/**************************************************/
void myEnd(unsigned long int experimentNumber) {

  int i;
  experimentNumber--;

  printf("  ---> Total number of experiments: %u\n", experimentNumber);
  printf("  ---> Experiments with one particle: %u\n", numExperimentOutput[EXP_SPEED]);
  if (numExperimentOutput[EXP_SPEED] > 0) {
    printf("  -----> average speed = %g\n", averageSpeed /= numExperimentOutput[EXP_SPEED]);
  }
  printf("  --------> Experiments with multiple particles: %u\n", numExperimentOutput[EXP_JET]);
  for (i = 0; i < 5; i++) {
    printf("  Number of experiments with %d particles = %d\n",
	   i + 2, hystogramNumber[i]);
  }
  printf("  --------> Experiments with error: %u\n", numExperimentOutput[EXP_ERROR]);
}

/**************************************************/
union experimentData experimentBody(unsigned long int experimentOutput) {

  union experimentData myData;
  double oneThird = 1./3., twoThirds = 2./3.;

  if (experimentOutput == EXP_SPEED) {
    double a = (double)rand() / (double)RAND_MAX;
    myData.speed = 10.0 * a;
    printf("Speed detected in this experiment = %g\n", myData.speed);
  }
  else if (experimentOutput == EXP_JET) {
    double a = (double)rand()/(double)RAND_MAX;
    myData.num = (int)(5.0 * a);
    if (myData.num > 4) {
      myData.num = 4;
    }
    printf("Number of particles counted in this experiment = %d\n", myData.num + 2);
  }
  else if (experimentOutput == EXP_ERROR) {
    double a = (double)rand() / (double)RAND_MAX;
    if (a < oneThird) {
      myData.errorMessage = experimentError[0];
    } else if (a < twoThirds) {
      myData.errorMessage = experimentError[1];
    } else {
      myData.errorMessage = experimentError[2];
    }
  }
  printf("\n");
  return myData;
}

/**************************************************/
unsigned long int setExperiment(unsigned long int experimentNumber) {

  unsigned long int experimentOutput;
  double oneThird = 1./3., twoThirds = 2./3.;

  printf("  Choice of type of result of an experiment\n");
  printf("  For an experiment with result one particle, type 0\n");
  printf("  For an experiment with result multiple particles, type 1\n");
  printf("  For an experiment with result an error, type 2\n");
  printf("  For an experiment with a random, type 3\n");
  printf("  To exit the program, type 4\n");

  scanf("%ld", &experimentOutput);

  printf("  ----> For the experiment numero %u we have chosen an output of type %u\n",
	  experimentNumber, experimentOutput);

  if (experimentOutput > 4) {
    printf("Error: type of output undefined\n");
    exit(MY_FAILURE);
  }

  if (experimentOutput == EXP_RANDOM) {
    double a = (double)rand() / (double)RAND_MAX;
    if (a < oneThird) {
      experimentOutput = EXP_SPEED;
    } else if (a < twoThirds) {
      experimentOutput = EXP_JET;
    } else {
      experimentOutput = EXP_ERROR;
    }

		printf("  ----> For the experiment number %u rand() has been chosen an output of type %u\n",
	    experimentNumber, experimentOutput);
  }

  numExperimentOutput[experimentOutput]++;

  return experimentOutput;
}
