#include <stdio.h>
#include "calc.h"

#define MAX_VAL 100  // max stack depth
static int sp = 0;          // next free position in the stack
static double val[MAX_VAL];  // stack of values

/* Inserts a value at the top of the stack. A stack is a
   Last-In-First-Out (LIFO) container.
*/
void push(double f) {

  if (sp < MAX_VAL)
    val[sp++] = f;
  else
    printf("Error: the stack is full; %g cannot be inserted\n", f);

}

/* Fetches a value from the top of the stack */
double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("Error: the stack is empty\n");
    return 0.0;
  }
}
