#include <stdio.h>
#include <stdlib.h>  // atof() function
#include "calc.h"
#define MAX_OP 100   // max number of operators and operands

/* Implements a simple calculator using the reverse Polish notation
   i.e. the operators follow their operands. The program is terminated
   when a EOF character is written in the standard input i.e. Ctrl + D
   Compile using the command
   $ cc calcmain.c calcgetop.c calcstack.c calcgetch.c -o calcmain
*/

int main() {

  int type;
  double operand2;
  char s[MAX_OP];

  while ((type = get_op(s)) != EOF) {
    switch (type) {
      case NUMBER:
        push(atof(s));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        operand2 = pop();
        push(pop() - operand2);
        break;
      case '/':
        operand2 = pop();
        if (operand2 != 0.0)
          push(pop() / operand2);
        else
          printf("Error: division by zero\n");
        break;
      case '\n':
        printf("\t%.8g\n", pop());
        break;
      default:
        printf("Error: unknown command\n", s);
        break;
    }
  }
  return 0;
}
