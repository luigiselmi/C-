#include <stdio.h>

/* Print a table to convert from Fahrenheit to Celsius*/

int main() {
  
  float celsius;

  for (int fahr = 0; fahr <= 300; fahr += 20) {
    celsius = (5.0/9.0) * (fahr - 32.0);
    printf("%3d %6.1f\n", fahr, celsius);
  }
}
