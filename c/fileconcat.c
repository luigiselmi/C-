#include <stdio.h>

/* Similarly to the unix command cat, prints
   on the standard output the file whose names
   are passed at the command line.
*/
int main(int argc, char *argv[]) {
   FILE *fp;  // pointer to a file
   void filecopy(FILE *source, FILE *target);

   if (argc == 1) // no files to open
      filecopy(stdin, stdout); // stdin and stdout are defined in <stdio.h>
   else
      while (--argc > 0)
         if ((fp = fopen(*++argv, "r")) == NULL) {
            printf("fileconcat: the file %s cannot be opened.\n", *argv);
            return 1;
         }
         else {
            filecopy(fp, stdout);
            fclose(fp);
         }

   return 0;
}
void filecopy(FILE *source, FILE *target) {
   int c;
   while ((c = getc(source)) != EOF)
      putc(c, target);
}
