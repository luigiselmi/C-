#include <stdio.h>
#include <ctype.h>  // isalpha()
#include <string.h> // strcmp()

#define MAX_NUM_KEYWORDS  100 //max number of keywords
int getword(char *word, int lim);

struct key {
  char *word;
  int count;
};

struct key keytab[] = { // ordered list of keywords
  "auto", 0,
  "break", 0,
  "case", 0,
  "char", 0,
  "const", 0,
  "continue", 0,
  "default", 0,
  /* ..more keywords..*/
  "unsigned", 0,
  "void", 0,
  "volatile", 0,
  "while", 0
};

#define NUM_KEYS (sizeof keytab / sizeof(struct key))
struct key *binsearch(char *word, struct key *tab, int size);

/* Counts the number of occurrences of keywords. It uses pointers to struct */
int main() {
  char word[MAX_NUM_KEYWORDS];
  struct key *p;

  while (getword(word, MAX_NUM_KEYWORDS) != EOF)
    if (isalpha(word[0]))
      if ((p = binsearch(word, keytab, NUM_KEYS)) != NULL)
        p->count++;

  for (p = keytab; p < keytab + NUM_KEYS; p++)
    if (p->count > 0)
      printf("%4d %s\n", p->count, p->word);

  return 0;
}
/* Searches a word in a (ordered) input array of struct.
   Returns a pointer to a struct if the keyword is found,
   NULL otherwise.
*/
struct key *binsearch(char *word, struct key *tab, int size) {
  int cond;
  struct key *low = &tab[0], *high = &tab[size], *mid;
  while (low < high) {
    mid = low + (high - low) / 2;
    if ((cond = strcmp(word, mid->word)) < 0)
      high = mid;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid; // found
  }
  return NULL; // not found
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
