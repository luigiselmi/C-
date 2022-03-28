#include <stdio.h>

/* Copy the input to the output. The program is terminated when a EOF
character is written in the standard input, i.e. Ctrl + D */

int main() {
  int c;

  printf("EOF=%d\n", EOF);

  while ((c = getchar()) != EOF)
    putchar(c); // puts the character into the output stream

}
