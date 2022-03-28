#include <stdio.h>
#define MAXLINELENGTH 1000

int getLine(char line[], int maxline);
void copy(char from[], char to[]);

/* Prints the longest line in a text. The program is terminated
   when a EOF character is written in the standard input i.e. Ctrl + D */
int main() {

  int len; // length of the current line
  int max = 0; // max length so far
  char line[MAXLINELENGTH];
  char longest[MAXLINELENGTH];

  while ((len = getLine(line, MAXLINELENGTH)) > 0)
    if (len > max) {
      max = len;
      copy(line, longest);
    }

  if (max > 0) // at least one line in the standard input
    printf("Longest line: %s\nLength: %d", longest, max - 1);

  return 0;
}

/* reads a line from the standard input and returns its length */
int getLine(char s[], int maxlength) {

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

/* copies the 1st char array into the 2nd one */
void copy(char from[], char to[]) {
  int i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
