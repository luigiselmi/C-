#include <unistd.h>
#include <stdio.h>

#define BUFSIZ 1024

/* Low level read and write using the OS system calls.
   It can be used to copy the content of a file into
   another one, e.g.
   $ ./syscalls < sourcefile.txt > targetfile.txt
*/
 int main() {
   char buf[BUFSIZ];
   int n;

   while ((n = read(0, buf, BUFSIZ)) > 0)
    write(1, buf, n);

   return 0;
 }
