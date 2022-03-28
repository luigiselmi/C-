#include <stdio.h>

#define IN  1  // char inside a word
#define OUT 0  // char outside a word

/* Counts words, number of lines and number of character in the input stream.
   The program is terminated when a EOF character is written in the
   standard input i.e. Ctrl + D */

int main() {

  int c, numLines = 0, numChars = -1, numWords = 0, state = OUT;

  while ((c = getchar()) != EOF) {
    ++numChars;
    if (c == '\n')
      ++numLines;

    if (c == ' ' || c == '\n' || c == '\t') {
      state == OUT;
      ++numWords;
    }
    else if (state == OUT)
      state = IN;

  }

  printf("Lines: %d, Words: %d, Characters: %d\n", numLines, numWords, numChars);
}
