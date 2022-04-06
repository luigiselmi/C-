#include <stdio.h>
#include <ctype.h>  // isalpha(), isspace(), isalnum()
#include <string.h> // strcmp(), strcpy(), strlen()
#include <stdlib.h> // malloc()

#define MAX_NUM_WORDS  100 //max number of keywords read from standard input

struct tnode {
  char *word;          // pointer to the string
  int count;           // number of occorrences of the word
  struct tnode *left;  // left child node
  struct tnode *right; // right child node
};

int getword(char *word, int lim);
struct tnode *addnode(struct tnode *n, char *w);
void treeprint(struct tnode *n);

/* Builds a binary tree representation of words from the
   standard input.
*/
int main() {
  struct tnode *tree = NULL;
  char word[MAX_NUM_WORDS];

  while (getword(word, MAX_NUM_WORDS) != EOF)
    if (isalpha(word[0]))
      tree = addnode(tree, word);
  printf("\n");

  treeprint(tree); // prints the tree after Ctrl+D

  return 0;

}

struct tnode *talloc(void);
char *_strdup(char *);

/* Adds recursively a node to the binary tree for each new
   word. Returns the node with the updated count of occurrences.
*/
struct tnode *addnode(struct tnode *n, char *w) {
  int cond;
  if (n == NULL) { // adds a new node to the tree
    n = talloc(); // allocates the memory for the new node
    n->word = _strdup(w);
    n->count = 1;
    n->left = n->right = NULL;
  }
  else if ((cond = strcmp(w, n->word)) == 0)
    n->count++;  // known word, increments its count
  else if (cond < 0) // minor word, go to the left sub-tree
    n->left = addnode(n->left, w);
  else
    n->right = addnode(n->right, w);

  return n;
}
/* Allocates the memory for a new node. Returns the pointer
   to the allocated memory space.
*/
struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}
/* Prints the binary tree */
void treeprint(struct tnode *n) {
  if (n != NULL) {
    treeprint(n->left);
    printf("%4d %s\n", n->count, n->word);
    treeprint(n->right);
  }
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
