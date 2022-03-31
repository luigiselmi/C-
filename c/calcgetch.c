#include <stdio.h>

#define BUF_SIZE 100
char buf[BUF_SIZE];
int bufp = 0;

/* Gets a character from the standard input*/
int get_ch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Puts a character back into the input */
void unget_ch(int c) {
  if (bufp >= BUF_SIZE)
    printf("unget_ch: too many characters\n");
  else
    buf[bufp++] = c;
}
