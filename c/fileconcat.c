#include <stdio.h>
#include <stdlib.h> // exit()

/* Similarly to the unix command cat, prints
   on the standard output the file whose names
   are passed at the command line.
*/
int main(int argc, char *argv[]) {
   FILE *fp;  // pointer to a file
   void filecopy(FILE *source, FILE *target);
   char *prog = argv[0];

   if (argc == 1) // no files to open
      filecopy(stdin, stdout); // stdin and stdout are defined in <stdio.h>
   else
      while (--argc > 0)
         if ((fp = fopen(*++argv, "r")) == NULL) {
            fprintf(stderr, "fileconcat: the file \'%s\' cannot be opened.\n", *argv);
            exit(1);
         }
         else {
            filecopy(fp, stdout);
            fclose(fp);
         }

   if (ferror(stdout)) {
      fprintf(stderr, "%s: error writing on stdout.\n", prog);
      exit(2);
   }

   exit(0);
}
void filecopy(FILE *source, FILE *target) {
   int c;
   while ((c = getc(source)) != EOF)
      putc(c, target);
}
