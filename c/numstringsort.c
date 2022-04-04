#include <stdio.h>
#include <string.h> // strcmp()
#include <stdlib.h>
#define MAX_LINES 5000 // max number of lines
char *pline[MAX_LINES]; // array of pointers to text lines

int readlines(char *pline[], int maxlines);
void writelines(char *pline[], int nlines);
void _qsort(void *v[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *s1, char *s2);

/* Sorts array of numbers or strings using a pointer to a function
   to select the function used for the comparison of a pair of
   elements. Compile using the command
   $ cc numstringsort.c sortlines.c
*/
int main(int argc, char *argv[]) {
  int nlines; //lines read from the standard input
  int numeric = 0; // 0 -> alphbetic order, 1 -> numeric order
  if (argc > 1 && strcmp(argv[1], "-n") == 0)
    numeric = 1;

  if ((nlines = readlines(pline, MAX_LINES)) >= 0) {
    // the selector of the function does not work and the program does not compile
    _qsort((void **) pline, 0, nlines - 1, (int (*)(void *, void *))(numeric ? numcmp : strcmp));
    writelines(pline, nlines);
    return 0;
  }
  else {
    printf("Error: too many lines of input to order\n");
    return 1;
  }
}
/* Sorts an array of strings or an array of numbers using
   the Quicksort algorithm
*/
void _qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
  int last;
  void swap(void *v[], int i, int j);

  if(left >= right) // return if the array contains less than two elements
    return;

  swap(v, left, (left + right) / 2);
  last = left;
  for (int i = left + 1; i <= right; i++)
    if((*comp)(v[i], v[left]) < 0)
      swap(v, ++last, i);

  swap(v, left, last);
  _qsort(v, left, last - 1, comp);
  _qsort(v, last + 1, right, comp);
}
void swap(void *v[], int i, int j) {
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* A function to compare two numbers */
int numcmp(char *s1, char *s2) {
  double v1, v2;
  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}
