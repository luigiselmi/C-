#include <stdio.h>
#define MAXLINELENGTH 1000

int getLine(char line[], int maxlength);
int strindex(char s[], char t[]);

char pattern[] = "ould"; // substring to be found

/* Prints the lines that contain a substring. The program is terminated
   when a EOF character is written in the standard input i.e. Ctrl + D.
   The value returned by the main() function can be printed using the command
   $ echo $?
*/
int main() {

  char line[MAXLINELENGTH];
  int found = 0;

  while(getLine(line, MAXLINELENGTH) > 0)
    if (strindex(line, pattern) >= 0) {
      printf("%s", line);
      found++;
    }

  return found;
}

/* Reads a line from the standard input, copies the characters
  in the array parameter and returns its length. */
int getLine(char s[], int maxlength) {

  int i = 0, c;

  while (--maxlength > 0 && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;

  if (c == '\n')
    s[i++] = c;

  s[i] = '\0'; // end of the char array

  return i;
}

/* Returns the start index of a substring */
int strindex(char s[], char t[]) {

  int i, j, k;

  for (i = 0; s[i] != '\0'; i++) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ; // null instruction
    if (k > 0 && t[k] == '\0')
      return i;
  }

  return -1;
}
