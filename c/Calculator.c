/* Implements a simple calculator using the reverse Polish notation
   i.e. the operators follow their operands. The program is terminated
   when a EOF character is written in the standard input i.e. Ctrl + D
*/
#include <stdio.h>
#include <stdlib.h>  // atof() function
#include <ctype.h>  // isdigit() function

#define MAX_OP 100   // max number of operators and operands
#define NUMBER '0'   // tells a number has been found

int get_op(char []);
void push(double);
double pop(void);
int get_ch(void);
void unget_ch(int);

#define MAX_VAL 100  // max stack depth
int sp = 0;          // next free position in the stack
double val[MAX_VAL];  // stack of values

#define BUF_SIZE 100
char buf[BUF_SIZE];
int bufp = 0;

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

/* Reads the next operator or numeric operand */
int get_op(char s[]) {

  int i, c;

  while((s[0] = (c = get_ch())) == ' ' || c == '\t')
    ;

  s[1] = '\0';
  if (! isdigit(c) && c != '.')
    return c;  // not a number

  i = 0;
  if (isdigit(c)) // reads the integer part
    while (isdigit(s[++i] = c = get_ch()))
      ;
  if (c == '.') // reads the fractional part
    while (isdigit(s[++i] = c = get_ch()))
      ;
  if (c != EOF)
    unget_ch(c);
  return NUMBER;
}

/* Gets a character from the standard input*/
int get_ch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* Puts a character back into the input */
void unget_ch(int c) {
  if (bufp >= BUF_SIZE)
    printf("unget_ch: too many characters\n");
  else
    buf[bufp++] = c;
}
