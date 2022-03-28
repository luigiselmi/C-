#include <stdio.h>

/* Counts the number of characters passed through the standard input.
  The program is terminated when a EOF character is written in the
  standard input i.e. Ctrl + D */

int main() {

  long numChars = -1;

  while (getchar() != EOF)
    ++numChars;

  printf("%ld\n", numChars);
}
