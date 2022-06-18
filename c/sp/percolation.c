/*
  This program finds the connected components in a 2-dimensional
  square lattice. It uses a doubly linked list to store the sites
	that belong to one of the clusters that are found over a square
	lattice.

	Original code:
	https://chimera.roma1.infn.it/SPENG//PROGRAMMI/cap13/cap13_cc_lista.c
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define L 20
#define V L*L
#define MAX_ITER 100

#define RIGHT 0
#define TOP 1
#define LEFT 2
#define BOTTOM 3

typedef unsigned long long RANDOM_TYPE;
typedef char SPIN;

#define MYRAND64  myRand64 = (6364136223846793005ULL * myRand64)
#define MAX_RAND64     0XFFFFFFFFFFFFFFFFULL
RANDOM_TYPE myRand64;
double inverseMaxRand64 = 1.0 / (double) MAX_RAND64;
#define rho 0.593 // ratio of nodes with spin down over the total number of nodes

unsigned long neighbor[V][4]; // 2D array used to hold the state of the (4) nodes
                              // adjacent to any node in the (square) lattice

FILE *fDat;

struct siteCluster{
  SPIN spin;
  struct siteCluster *next;
  struct siteCluster *former;
  struct siteCluster *parent;
  struct siteCluster *son;
} cluster[V];

void init(void);
void initNeighbors(void);
void initRandomSpin(void);
unsigned long siteUpdate(long, long);
void print(void);
void printLatticeState(void);
void printGnuplot(void);

#define FAILURE -1
#define SUCCESS 1

/*****************************************************************************/
int main(void) {
  long i, j;
  unsigned long numClusterChanged; // number of cluster changed after one iteration

	fDat = fopen("output_cc.dat","w");
  if (fDat == NULL) {
    printf("Error: can't open the file with write permissions\n");
    exit(1);
  }

  init();
  initNeighbors();
  initRandomSpin();
  j = 0;
  numClusterChanged = 9999;
  while ( (j < MAX_ITER) && (numClusterChanged != 0) ) {
    j++;
    numClusterChanged = 0;
    for (i = 0; i < V; i++) {
      numClusterChanged += (unsigned long) siteUpdate((long)RIGHT, i);
      numClusterChanged += (unsigned long) siteUpdate((long)BOTTOM, i);
      numClusterChanged += (unsigned long) siteUpdate((long)LEFT, i);
      numClusterChanged += (unsigned long) siteUpdate((long)TOP, i);
    }
    printf("# Number of cluster changes  %ld\n", numClusterChanged);
  }

	print(); // prints the clusters each site belongs to
	printGnuplot(); // prints on a file

	if (numClusterChanged > 0) {
    printf("We could not build the cluster.\n");
    return FAILURE;
  }
	else {
    return SUCCESS;
  }
}
/*
  A node state is compared to one of its nearest neighbors' along
	a direction (top, botton, left, right) and if they are in the
	same state (spin up or down) and belong to two different clusters
	the parent cluster that is lexically lower is copied to the parent
	cluster of node with the higher parent.
*/
unsigned long siteUpdate(long direction, long site) {
  long i, j;
  unsigned long labelChanged = 0UL;
  long lowerSite, upperSite; // sites indexes of lower and upper lexical order
  struct siteCluster *upperHead, *upperTail;
  struct siteCluster *lowerHead, *lowerTail;
  struct siteCluster *scratchSiteCluster;

  unsigned long int n = neighbor[site][direction];
  if ( (cluster[site].spin == cluster[n].spin) &&       // same state
       (cluster[site].parent != cluster[n].parent)) {   // belonging to two different clusters

    /* qui si cambia */
    labelChanged = 1UL;

    /* copieremo dal site con parent piu' piccolo
       a quello con parent piu' grande */
    if (cluster[site].parent < cluster[n].parent) {
      lowerSite = site;
      upperSite = n;
    }
		else {
      lowerSite =  n;
      upperSite = site;
    }

    /* siccome dovremo cambiare i valori conserviamo
       i dati che ci serviranno, come head e tail dei
       due cluster che stiamo fondendo */
    upperHead = cluster[upperSite].parent;
    upperTail = cluster[upperSite].son;
    lowerHead = cluster[lowerSite].parent;
    lowerTail = cluster[lowerSite].son;

    /* il parent del lower cluster viene dato a tutti i siti
       dell'upper cluster */
    scratchSiteCluster = upperHead;
    scratchSiteCluster->parent = lowerHead;
    while (scratchSiteCluster != scratchSiteCluster->next) {
      scratchSiteCluster = scratchSiteCluster->next;
      scratchSiteCluster->parent = lowerHead;
    }

    /* il son dell'upper cluster viene dato a tutti i siti
       del lower cluster */
    scratchSiteCluster = lowerHead;
    scratchSiteCluster->son = upperTail;
    while (scratchSiteCluster != scratchSiteCluster->next) {
      scratchSiteCluster = scratchSiteCluster->next;
      scratchSiteCluster->son = upperTail;
    }

    if (lowerTail->next != lowerTail) {
      printf("Execution stopped: internal error 1\n");
      exit(-9);
    }
    lowerTail->next = upperHead;
    if (upperHead->former != upperHead) {
      printf("Execution stopped: internal error 2\n");
      exit(-9);
    }
    upperHead->former = lowerTail;
  }
  return labelChanged;
}
/*
  Set the random seeds
*/
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
  for (i = 0; i < 1000; i++) { MYRAND64; }
}
/*
  This function is used to store the (4) nearest neighbors of
	each node. The nodes' neighbors are kept in a separate 2D array.
	Each lattice node (x, y) is mapped to an element of the array
	with index value i = x + L * y. The labels of all its neighbors
	(top, bottom, left, right) are computed using the rule
	label = x + L * y.
*/
void initNeighbors(void) {
  long x, y, i;

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
	(x, y) of the lattice and builds a doubly linked list by
	assigning the pointers to the next and previous nodes. It
	also write the pointers to the first and last node of the
	cluster the node is a member of. At initialization each node
	belong to a cluster that contain only that node, so all the
	pointers refers to the node itself and there is one cluster
	for each node.
	Only two states are allowed: spin up (1), or spin down (-1). The initial
	label of each node is also set using the rule
	label = x + L * y, where x is the row and y is the column.
	The probability of spin down is set in a global variable
	(rho) as the ratio of nodes with spin down to the total
	number of nodes.
*/
void initRandomSpin(void) {
  long i, j;

  for (i = 0; i < V; i++) {
    MYRAND64;
    if ((double) myRand64 * inverseMaxRand64 < rho) {
      cluster[i].spin = -1;
    }
    else {
      cluster[i].spin = 1;
    }
  }

  for (i = 0; i < L; i++) {
    for (j = 0; j < L; j++) {
      cluster[j + i * L].next   = cluster + (j + i * L);
      cluster[j + i * L].former = cluster + (j + i * L);
      cluster[j + i * L].parent = cluster + (j + i * L);
      cluster[j + i * L].son    = cluster + (j + i * L);
    }
  }

}
/*
  Prints on standard output the state of each site after the
	initialization.
*/
void printLatticeState(void) {
  long i, j;
  for (j = 0; j < L; j++) {
    printf("-----");
  }
  printf("-\n");
  for (i = 0; i < L; i++) {
    for (j = 0; j < L; j++) {
      printf("| %2d ",cluster[j+i*L].spin);
    }
    printf("|\n");
    for (j = 0; j < L; j++) {
      printf("-----");
    }
    printf("-\n");
  }
  printf("\n");
}
/*
  Prints the square lattice with the final cluster of each node.
*/
void print(void) {
  long i, j;

  for (j = 0; j < L; j++) {printf("------");}
  printf("-\n");
  for (i = 0; i < L; i++) {
    for (j = 0; j < L; j++) {
      //printf("| %2d (%4d) ", cluster[j + i * L].spin, cluster[j + i * L].parent-cluster);
			printf("(%3d) ", cluster[j + i * L].parent - cluster);
    }
    printf("|\n");
    for (j = 0; j < L; j++) {printf("------");}
    printf("-\n");
  }
  printf("\n");

}
/*
  Prints on a file the square lattice with the final
	cluster of each node.
*/
void printGnuplot(void) {

  long i, j;

  for (i = 0; i < L; i++) {
    for (j = 0; j < L; j++)
      fprintf(fDat, "%2d ", cluster[j + i * L].parent - cluster);
    fprintf(fDat, "\n");
  }
  fclose(fDat);
}
