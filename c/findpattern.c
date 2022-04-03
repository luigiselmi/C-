#include <stdio.h>
#include <string.h> // strstr()

#define MAX_LINE 1000
int get_line(char s[], int maxlength);

/* Finds the lines that contain the pattern passed as argument
   Prints the line that contain or not the pattern and its number
   according to the options x and n passed at the command line
*/
int main(int argc, char *argv[]) {

  char line[MAX_LINE]; // array of strings
  long lineno = 0;  // number of the line containing the pattern
  int c, except = 0, number = 0, found = 0;

  while (--argc > 0 && (*++argv)[0] == '-')
    while (c = *++argv[0])
      switch (c) {
        case 'x':
          except = 1; // print the line that does not contain the pattern
          break;
        case 'n':
          number = 1; // print the number of the line that contains the pattern
          break;
        default:
          printf("find: option %c not allowed\n", c);
          argc = 0;
          found = -1;
          break;
      }

  if (argc != 1)
    printf("Usage: find -x -n pattern\n");
  else
    while (get_line(line, MAX_LINE) > 0) {
      lineno++;
      if ((strstr(line, *argv) != NULL) != except) {
        if (number)
          printf("%ld:", lineno);
        printf("%s", line);
        found++;
      }
    }

    return found;
}

/* Reads a line from the standard input, copies the characters
  in the array parameter and returns its length. */
int get_line(char s[], int maxlength) {

  int i = 0, c;

  while (--maxlength > 0 && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;

  if (c == '\n')
    s[i++] = c;

  s[i] = '\0'; // end of the char array

  return i;
}
