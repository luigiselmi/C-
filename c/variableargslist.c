#include <stdarg.h>
#include <stdio.h>

void minprintf(char *fmt, ...);

/* Implemets a simplified version of printf() to show how to define
   functions with variable arguments list.
*/
int main() {
   minprintf("Two arguments: %s, and %d\n", "Rome", 123);
   minprintf("Three arguments: %s, %d, and %f\n", "Rome", 123, 12.45);
}
/* Simplified printf() */
void minprintf(char *fmt, ...) {
   va_list ap; // pointer to the arguments without a name
   char *p, *sval;
   int ival;
   double dval;

   va_start(ap, fmt); // points ap to the 1st unnamed argument

   for (p = fmt; *p; p++) {
      if (*p != '%') {
         putchar(*p);
         continue;
      }
      switch (*++p) {
         case 'd':
            ival = va_arg(ap, int); //va_arg(ap, <type>) increments ap and returns an argument of type <type>
            printf("%d", ival);
            break;
         case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
         case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
               putchar(*sval);
            break;
         default:
            putchar(*p);
            break;
      }
   }
   va_end(ap); // clean up
}
