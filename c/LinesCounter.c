#include <stdio.h>

/* Counts the number of lines in the input stream.
   The program is terminated when a EOF character is written in the
   standard input i.e. Ctrl + D*/

int main() {

  int c, numLines = 0;

  while ((c = getchar()) != EOF)
    if (c == '\n')
      ++numLines;

  printf("Number of lines: %d\n", numLines);

}
