#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Number of arguments: %d\n", argc - 1);
  printf("Arguments: ");
  for (int i = 1; i < argc; i++)
    printf("%s%s", argv[i], (i < argc - 1) ? " " : "");
  printf("\n");
  return 0;
}
