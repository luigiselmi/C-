#include <stdio.h>

/* Counts the number of digits, spaces and other characters in the standard input.
  The program is terminated when a EOF character is written in the
  standard input i.e. Ctrl + D */

int main() {

  int c, numSpaces = -1, numOther = 0;
  int numDigit[10]; // number of digits: '0', '1', '2'..

  for (int i = 0; i < 10; ++i)
    numDigit[i] = 0;

  while ((c = getchar()) != EOF)
    if (c >= '0' && c <= '9')
      ++numDigit[c - '0'];
    else if (c == ' ' || c == '\n' || c == '\t')
      ++numSpaces;
    else
      ++numOther;

  printf("Digits = ");
  for (int i = 0; i < 10; ++i)
    printf(" %d", numDigit[i]);

  printf(", Spaces = %d, Others = %d", numSpaces, numOther);
}
