/*
  Computes the factorial of a number by calling
  recursively a function.
  The program is terminated when a EOF character
  is written in the standard input i.e. "Ctrl + D".
*/
#include <stdio.h>

unsigned long long factorial(unsigned long long n);

int main() {
  unsigned long long n;
  printf("Enter an integer (Ctrl + D to exit):\n");
  while (scanf("%Lu", &n) != EOF)
    printf("%Lu! =  %Lu \n", n, factorial(n));

}
unsigned long long factorial(unsigned long long n) {
  if (n == 0) return 1;
  return (n * factorial(n - 1));
}
