#include <stdio.h>
#include <string.h> // strcpy(), strcmp(),

#define MAX_LINES 5000  // max number of lines

char *pline[MAX_LINES];  // pointer to the text lines

int readlines(char *pline[], int maxlines);
void writelines(char *pline[], int nlines);
void qsort(char *v[], int left, int right);

/* sorts lines in the standard input. The program is terminated
   when a EOF character is written in the standard input i.e. Ctrl + D */
int main() {
  int nlines; // number of lines read
  if ((nlines = readlines(pline, MAX_LINES)) >= 0) {
    qsort(pline, 0, nlines - 1);
    writelines(pline, nlines);
    return 0;
  }
  else {
    printf("Error: too many lines of input to sort.\n");
    return 1;
  }
}

#define MAX_LEN 1000 // max length of a line
int get_line(char *, int);
char *alloc(int);

/* Reads lines from the standard input */
int readlines(char *pline[], int maxlines) {
  int len, nlines;
  char *p, line[MAX_LEN];

  nlines = 0;
  while ((len = get_line(line, MAX_LEN)) > 0)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0'; // removes the new line
      strcpy(p, line);
      pline[nlines++] = p;
    }
  return nlines;
}
/* Writes the lines in the standard output */
void writelines(char *pline[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", pline[i]);
}
/* reads a line from the standard input and returns its length */
int get_line(char s[], int maxlength) {

  int i, c;

  for (i = 0; i < maxlength - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n') {
    s[i] = c;
    ++i;
  }

  s[i] = '\0'; // end of the char array
  return i;
}
/* Sorts an array of strings using the Quicksort algorithm */
void qsort(char *v[], int left, int right) {
  int last;
  void swap(char *v[], int i, int j);

  if(left >= right) // return if the array contains less than two elements
    return;

  swap(v, left, (left + right) / 2);
  last = left;
  for (int i = left + 1; i <= right; i++)
    if(strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);

  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}
/* swaps two elements in the array */
void swap(char *v[], int i, int j) {
  char *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

#define ALLOC_SIZE 10000          // number of memory locations of type char
static char allocbuf[ALLOC_SIZE]; // memory locations of type char managed by alloc()
static char *palloc = allocbuf;   // next available memory location

/* Returns a pointer to an array  of chars */
char *alloc(int n) {
  if (allocbuf + ALLOC_SIZE - palloc) { // allocbuf is the address of the 1st element
    palloc += n;
    return palloc - n;
  }
  else {
    return 0; // there is no available space
  }

}
/* Frees the memory pointed by the pointer parameter.
   This function is not used here, it is here for completeness.
*/
void afree(char *p) {
  if (p>= allocbuf && p < allocbuf + ALLOC_SIZE)
    palloc = p;
}
