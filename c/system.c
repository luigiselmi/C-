#include <stdio.h>
#include <stdlib.h>
/* executes a command available on the file system */
int main() {
  printf("Executing the \'date\' command\n");
  int result = system("date");
  printf("Value returned from the command: %d\n", result);
}
