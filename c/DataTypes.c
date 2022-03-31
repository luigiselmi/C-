#include <stdio.h>
#include <ctype.h>

int atoi(char s[]);
int lower(int c);
int squeeze(char s[], int c);
void printd(int n);

/* Implements some functions to show the C data types properties */

int main() {
  printf("Number \"12\" * 2 = %d\n", atoi("12") * 2);
  printf("Lower case A: %c\n", lower('A'));
  printf("Is \'3\' a digit ? %s\n", isdigit('1') ? "True" : "False");
  char s[9] = "chaccacah";
  int num_chars_left = squeeze(s, 'c');
  char t[num_chars_left]; // creates a new array without the removed chars
  for (int i = 0; i < num_chars_left; ++i)
    t[i] = s[i];
  printf("Removes \'c\' from \"chaccacah\": %s\n", t);
  printf("New size = %d\n", num_chars_left);
  printf("Shifted \'a\': %d %d\n", 'a', 'a' >> 1);
  printf("Print a number as chars: -12345: %c\n");
  printd(-12345);
}

/* Converts an integer represented as a string (char array) into a number */
int atoi(char s[]) {
  int n = 0;
  for (int i = 0; s[i] > '0' && s[i] <= '9'; ++i)
    n = 10 * n + s[i] - '0';
  return n;
}
/* Converts the digits of a number in characters. It is based on recursion.
   The characters are written in the standard output.
*/
void printd(int n) {
  if (n < 0) {
    putchar('-');
    n = -n;
  }
  if (n / 10)
    printd(n / 10);  // recursive call
  putchar(n % 10 + '0');
}

/* Converts a char into its lower case representation */
int lower(int c) {
  int result = c;
  if (c >= 'A' && c <= 'Z')
    result = c + 'a' - 'A';
  return result;
}

/* Removes the character from the string. The length of the array
   does not change. Returns the number of characters left.*/
int squeeze(char s[], int c) {
  int i, j, jumps = 0;
  for (i = j = 0; s[i] != '\0'; i++)
    if (s[i] != c)
      s[j++] = s[i];
    else
      ++jumps;
  s[j] = '\0';
  return j - jumps - 1;
}
