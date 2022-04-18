#include <stdio.h>

void swap(int *px, int *py);
int str_len(char *s);
void str_copy(char *s, char *t);

/* Shows pointers and use of & and * operators for variables, functions and arrays */
int main() {
  // Pointers to variables
  int x = 1, y = 2, z[10];
  int *pi;  // pointer to an integer (variable or array), contains the address of an integer;
  printf("x = %d, y = %d\n", x, y);
  pi = &x;  // the pointer contains the x address
  printf("x address (pointer) &x = %p\n", pi);
  y = *pi;  // y contains the value pointed by pi (i.e. x=1)
  printf("x = %d, y = %d\n", x, y);
  *pi = 2;  // the integer pointed by pi (x) is assigned a new value
  printf("x = %d, y = %d\n", x, y);
  int *pj = pi;  // the pointer pj points to the same object as pi, i.e. x
  int a = *pj;  // the integer pointed by pj (x) is assigned to a
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
  printf("array c addr = %p, pointer to c = %p\n", c, pc);
  for (int i = 0; i < sizeof(c)/sizeof(c[0]); ++i)
    c[i] = i * i;
  printf("c[3] == *(c + 3) == %d ? %s\n", c[3], c[3] == *(c + 3) ? "True" : "False");

  char source[] = "Hello World";
  int size = str_len(source);
  char target[size];
  str_copy(source, target);
  printf("Source string: \"%s\", target string: \"%s\"\n", source, target);

  char string1 [50] = "";
  char string2 [] = "%lf";
  int n = 15;
  sprintf(string1 , "%c%d%s", string2 [0], n, &string2[1]);
  printf("%s\n", string1);

  double a1, b, *pd;

  a1 = 3.14;
  pd = &a1;
  pd++;
  b = *(pd - 1);
  printf("We get a = %f, b = %f", *pd, b);

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
/* Copies each source character into the target */
void str_copy(char *s, char *t) {
  while (*t++ = *s++);
}
