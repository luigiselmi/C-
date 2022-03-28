#include <stdio.h>

/* Print a table to convert from Fahrenheit to Celsius */

int main() {
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  fahr = 0.0;
  while (fahr <= upper) {
    celsius = (5.0/9.0) * (fahr - 32.0);
    printf("%3.0f %10.1f\n", fahr, celsius);
    fahr += step;
  }
}
