#include <stdio.h>
#include <ctype.h>  // isdigit() function
#include "calc.h"

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
