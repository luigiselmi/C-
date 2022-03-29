#include <stdio.h>

int atoi(char s[]);
int lower(int c);

/* Implements some functions to show the C data types properties */

int main() {
  printf("Number * 2 = %d\n", atoi("12") * 2);
  printf("Lower case A: %c\n", lower('A'));
}

/* Converts an integer represented as a string (char array) into a number */
int atoi(char s[]) {
  int n = 0;
  for (int i = 0; s[i] > '0' && s[i] <= '9'; ++i)
    n = 10 * n + s[i] - '0';
  return n;
}

/* Converts a char into its lower case representation */
int lower(int c) {
  int result = c;
  if (c >= 'A' && c <= 'Z')
    result = c + 'a' - 'A';
  return result;
}
