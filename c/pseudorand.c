#include <stdio.h>
#include <stdlib.h>

/* Pseudo-random number generation */
int main(int argc, char *argv[]) {
  int seed = 123; // default value

  if (argc == 2)
    seed = atoi(argv[1]);

  srand(seed);
  int r = rand();
  printf("Seed: %d, Pseudo-random number: %d", seed, r);
}
