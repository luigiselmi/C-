#include <stdio.h>
#include <ctype.h>  // isalpha(), isspace(), isalnum()
#include <string.h> // strcmp(), strcpy(), strlen()
#include <stdlib.h> // malloc(), free()

#define HASH_SIZE 101  // size of the array of linked lists of struct of type nlist
#define MAX_NUM_WORDS  100 //max number of keywords read from standard input

struct nlist {
   struct nlist *next; // pointer to the next element of the linked list
   char *name;
   char *defn;
};

static struct nlist *hashtab[HASH_SIZE]; // array of pointers to struct of type nlist

int getword(char *word, int lim);
unsigned hash(char *s);

/* Implements a symbol table to store a dictionary,
   a collection of name, value pairs. The hash value
   of a name is used as an index to a linked list that
   contains all the names that have the same hash.
*/
int main() {
  char word[MAX_NUM_WORDS];
  while (getword(word, MAX_NUM_WORDS) != EOF)
    if (isalpha(word[0]))
      printf("Word: %s, Hash: %d\n", word, hash(word));
}
/* Computes the hash of a name then traverses the linked list*/
unsigned hash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASH_SIZE;
}
/* Finds a name in the array of struct of type nlist */
struct nlist *lookup(char *s) {
  struct nlist *np;
  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np; // name found
  return NULL; // name not found
}

char *_strdup(char *s);
/* Inserts a new name and its definition into the dictionary,
   if it is not yet there and returns its pointer.
*/
struct nlist *insert(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) { // name not found
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL; // no space available in memory
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  }
  else //name already in the dictionary -> updates the name definition
    free((void *)np->defn); // deletes the old definition

  if ((np->defn = _strdup(defn)) == NULL)
    return NULL;

  return np;

}
/* Copies the word passed in the standard input in a memory location
   and returns its pointer. To not be confused with a function with the
   same name, strdup(), in <string.h>.
*/
char *_strdup(char *s) {
  char *p;
  p = (char *) malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
}
/* Reads the next word or character from the standard input */
int getword(char *word, int lim) {
  int c, get_ch(void);
  void unget_ch(int);
  char *w = word;

  while (isspace(c = get_ch()));

  if (c != EOF)
    *w++ = c;
  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }
  for ( ; --lim > 0; w++)
    if (!isalnum(*w = get_ch())) {
      unget_ch(*w);
      break;
    }
  *w = '\0';
  return word[0];
}

#define BUF_SIZE 100
static char buf[BUF_SIZE];
static int bufp = 0;

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
