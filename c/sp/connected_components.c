/*
  This program finds the connected components in a 2-dimensional
	square lattice. L is the number of nodes per row and per column
	so that the total (volume) number is LxL. Each node of the lattice
	has a label and a state, kept in two separate 2D arrays. At the
	beginning each node is initialized with a unique label and then
	its state is randomly set as spin down (-1) or spin up (+1).
	The number of nodes that may take the state spin down is set through
	the density. After the initialization is completed, the program
	finds the connected component, that is the nodes that have the
	same state and are neighbors. Each node state is compared to its
	neighbors and if they are in the same state (spin up or down) the
	label of the node that is lexically lower is copied to the node
	with the higher label so that they both have the same lower label.
	The program loops several times through all the nodes in the lattice
	till there are labels that are changed and when there are no changes
	it prints the lattice with the state and the final label of each
	node that can be used to identify the connected components.
	There is a maximum number of loops in case the algorithm cannot
	find all the connected components.

	Original source code:
	https://chimera.roma1.infn.it/SPENG//PROGRAMMI/cap13/cap13_cc_local.c
*/
#include <stdio.h>
#include <math.h>

#define L 10
#define V L*L
#define MAX_ITER 100
#define rho 0.5 // ratio of nodes with spin down over the total number of nodes

#define RIGHT 0
#define TOP 1
#define LEFT 2
#define BOTTOM 3

typedef unsigned long long RANDOM_TYPE;
typedef char SPIN;

#define MYRAND64  myRand64 = (6364136223846793005ULL * myRand64)
#define MAX_RAND64     0XFFFFFFFFFFFFFFFFULL
RANDOM_TYPE myRand64;
double inverseMaxRand64 = 1.0 / (double)MAX_RAND64;

#define SPIN_UP 1       // two possible states of a node
#define SPIN_DOWN -1

unsigned long neighbor[V][4]; // 2D array used to hold the labels of all the nodes

struct siteCluster{
  SPIN spin;
  unsigned int label;
} cluster[V];

void init(void);
void initNeighbors(void);
void initRandomSpin(void);
unsigned long siteUpdate(long, long);
void printLattice(void);

#define FAILURE -1
#define SUCCESS 1

/*****************************************************************************/
int main(void) {
  long i, j;
  unsigned long numLabelsChanged;

  init();
  initNeighbors();
  initRandomSpin();
  j = 0;
  numLabelsChanged = 9999;
  while ( (j < MAX_ITER) && (numLabelsChanged != 0) ) {
    j++;
    numLabelsChanged = 0;
    for (i = 0; i < V; i++) {
      numLabelsChanged += (unsigned long) siteUpdate((long) RIGHT, i);
      numLabelsChanged += (unsigned long) siteUpdate((long) BOTTOM, i);
      numLabelsChanged += (unsigned long) siteUpdate((long) LEFT, i);
      numLabelsChanged += (unsigned long) siteUpdate((long) TOP, i);
    }
    printf("# Number of labels changed %ld\n", numLabelsChanged);
  }
  printLattice();
  if (numLabelsChanged > 0) {
    printf("I have not been able to build the cluster\n");
    return FAILURE;
  }
	else {
    return SUCCESS;
  }
}
/*****************************************************************************/
unsigned long siteUpdate(long direction, long site) {
  unsigned long labelChanged = 0;

  unsigned long int n = neighbor[site][direction];
  if (cluster[site].spin == cluster[n].spin) {
    if (cluster[site].label < cluster[n].label) {
      labelChanged = 1;
      cluster[n].label = cluster[site].label;
    }
    else if (cluster[site].label > cluster[n].label) {
      labelChanged = 1;
      cluster[site].label = cluster[n].label ;
    }
  }
  return labelChanged;
}

/*
  This function is used to initialize the label of all the nodes
	in the lattice. The labels are kept in a separate 2D array.
	Each lattice node (x, y) is mapped to an element of the array
	with index value i = x + L * y. The labels of all its neighbors
	(top, bottom, left, right) are computed using the rule label = x + L * y.
*/
void initNeighbors(void) {
  long x, y;

  for (x = 0; x < L; x++) {
    long xp, xm;
    xp = x + 1;
    if (x == L - 1) xp = 0;
    xm = x - 1;
    if (x == 0) xm = L - 1;
    for (y = 0; y < L; y++) {
      long yp, ym;
      yp = y + 1;
      if(y == L - 1) yp = 0;
      ym = y - 1;
      if (y == 0) ym = L - 1;
      neighbor[x + L * y][RIGHT]  = xp + L *  y;
      neighbor[x + L * y][TOP]    =  x + L * yp;
      neighbor[x + L * y][LEFT]   = xm + L *  y;
      neighbor[x + L * y][BOTTOM] =  x + L * ym;
    }
  }
}

/*
  This function randomly initializes the state of each node
	(x, y) of the lattice. Only two states are allowed: spin
	up (1), or spin down (-1). The initial label of each node
	is also set using the rule label = x + L * y, where x is
	the row and y is the column. The probability of spin down
	is set in a global variable (rho) as the ratio of nodes
	with spin down to the total number of nodes.
*/
void initRandomSpin(void)
{
  long i, j;
  // set the state
  for(i = 0; i < V; i++){
    MYRAND64;
    if((double)myRand64 * inverseMaxRand64 < rho){
      cluster[i].spin = SPIN_DOWN;
    }
    else{
      cluster[i].spin = SPIN_UP;
    }
  }
  // set the initial label
  for(i = 0; i < L; i++){
    for(j = 0; j < L; j++){
      cluster[j + i * L].label   = j + i * L;
    }
  }

}

/*****************************************************************************/
void init(void) {

  int randomSeed;
  long i;

  printf("# L = %d\n", L);
  printf("# Please input random seed _ \n");
  fflush(stdout);
  scanf("%d", &randomSeed);
  printf("# randomSeed = %d\n", randomSeed);
  fflush(stdout);

  myRand64 = (RANDOM_TYPE) randomSeed;
  for (i = 0; i < 1000; i++) {MYRAND64;}
}
/*
  Prints the square lattice with state and final label of each node.
*/
void printLattice(void) {

  long i, j;

  for(j = 0; j < L; j++){printf("-----------");}
  printf("-\n");
  for(i = 0; i < L; i++){
    for(j = 0; j < L; j++){
      printf("| %2d (%4d) ",
	     cluster[j + i * L].spin,
	     cluster[j + i * L].label);
    }
    printf("|\n");
    for(j = 0; j < L; j++){printf("-----------");}
    printf("-\n");
  }
  printf("\n");
}
