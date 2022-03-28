#include <stdio.h>

/* Print a table to convert from Celsius to Fahrenheit*/

int main() {
  float fahr, celsius, step;
  float lowerC, upperC;

  lowerC = 0.0;
  upperC = 100.0;
  step = 10.0;

  celsius = lowerC;
  while (celsius <= upperC) {
    fahr = (9.0/5.0) * celsius + 32.0;
    printf("%3.1f %10.1f\n", celsius, fahr);
    celsius += step;
  }
}
