#include <stdio.h>

void swap(int *px, int *py);
int str_len(char *s);

/* Shows pointers and use of & and * operators for variables, functions and arrays */
int main() {
  // Pointers to variables
  int x = 1, y = 2, z[10];
  int *pi;  // pointer to an integer (variable or array), contains the address of an integer;
  printf("x = %d, y = %d\n", x, y);
  pi = &x;  // the pointer contains the x address
  printf("&x = %d\n", pi);
  y = *pi;  // y contains the value pointed by ip (i.e. x=1)
  printf("x = %d, y = %d\n", x, y);
  *pi = 2;  // the integer pointed by ip (x) is assigned a new value
  printf("x = %d, y = %d\n", x, y);
  int *pj = pi;  // the pointer iq points to the same object as ip, x
  int a = *pj;  // the integer pointed by iq (x) is assigned to a
  printf("a = %d\n", a);

  // Pointers to function's arguments
  x = 3, y = 5;
  printf("x = %d, y = %d\n", x, y);
  swap(&x, &y);
  printf("swap x = %d, y = %d\n", x, y);

  // Pointers and arrays
  int c[10];
  int *pc;
  pc = &c[0]; // same as pc = c
  printf("c addr = %d, pointer to c = %d\n", c, pc);
  for (int i = 0; i < sizeof(c)/sizeof(c[0]); ++i)
    c[i] = i * i;
  printf("c[3] == *(c + 3) ? %s\n", c[3] == *(c + 3) ? "True" : "False");
  char s[] = "hello";
  printf("length of \"%s\" = %d\n", s, str_len(s));

}

void swap(int *px, int *py) {
  int temp;
  temp = *px; // temps contains the value of the object pointed by px
  *px = *py; // swap values
  *py = temp; // copy the value into the object pointed by py
}

int str_len(char *s) {
  int i;
  for (i = 0; *s != '\0'; i++, s++);
  return i;
}
