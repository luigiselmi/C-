/*
  An example of a binary tree that uses a recursive function to
	search for words stored on its nodes. The program reads words
	from a text, compares recursively the word with those in the
	tree in lexical order and creates a new leaf if the word is new.
	Each node has a left pointer to an alphabetically lower word
	and a right pointer to a higher one. Finally the words in the
	tree are printed by recursively navigating the tree.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_STRING_LENGTH 100
#define _SUCCESS 0
#define FAIL -9

FILE *fInput;
char *fInputName = "data/manzoni.dat";

void init(void);
void openFile(void);

struct word{  // structure used to build the binary tree of words
  char *pString;
  struct word *pLeft;
  struct word *pRight;
};

struct token{ // structure returned after reading a lexically complete word
  int end_of_file;
  char *pString; // pointer to the memory space allocated for a string in the text
};

struct token readWord(void);
struct word *addToTree(struct word *, char *);
void printTree(struct word *);

/*****************************************************************************/
int main(void) {
  struct token tok;
  struct word *treeRoot = NULL;

  init();
  openFile();

  tok.end_of_file = 0; // end_of_file = 1 when the end of file is reached
  while(tok.end_of_file != 1){
    tok = readWord();
    treeRoot = addToTree(treeRoot, tok.pString);
  }
  fclose(fInput);
  printTree(treeRoot);
}

void init(void) {
  printf("# Building a binary tree of words\n");
}

void openFile(void) {
  fInput = fopen(fInputName, "r");
  if(fInput == NULL){
    printf("Abort: cannot read the file: %s\n", fInputName);
    exit(FAIL);
  }
  printf("# The file %s has been opened\n", fInputName);
}

/*
  lexical analysis: reads tokens of characters that are interpreted
  as words when separated by a white space. The token is stored in
  a global variable till it is a complete word. The function returns
  a structure, after a word has been read, with an integer to indicate
	whether the end of the file has been reached (1) or not (0) and the
	string that forms a lexically correct word (according to the very
  simple rule used)
*/
struct token readWord(void) {
  int j = 0;
  char txtString[MAX_STRING_LENGTH]; // contains a string read from the text
	int wordComplete = 0; // 1 when a word is complete
  char *pString; // pointer to the memory space allocated for the string
  struct token tok;

  while ( (j < MAX_STRING_LENGTH) && (wordComplete == 0) ) {
    txtString[j] = fgetc(fInput);
    if (txtString[j] == ' ') {
      txtString[j] = '\0';
      wordComplete = 1;
    }
    else if (txtString[j] == '\n') {
      j--;
    }
    else if (txtString[j] == EOF) {
      tok.end_of_file = 1;
      txtString[j] = '\0';
      wordComplete = 1;
    }
    j++;
  }

  // Reserves a character other than \0 to be on the safe side
  if (j >= MAX_STRING_LENGTH - 1) {
    printf("Program stopped: the word is too long.\n");
    printf("Compile the code again with a larger value of MAX_STRING_LENGTH. Now it's  %d.\n",
		                        MAX_STRING_LENGTH);
    exit(FAIL);
  }

  pString = (char *) malloc(strlen(txtString) + 1); // allocates memory space for the string
  if(pString == NULL){
    printf("Program stopped: malloc failed 1\n");
    exit(FAIL);
  }
  strcpy(pString, txtString); // copies the string into the allocated memory space
  tok.pString = pString; // copies the string pointer into the token structure
  //printf("Word of length %d: %s\n", strlen(pString), pString);

  return tok;
}

/*
  This function is called from a loop in the main function every time a word has
  been found in the text. The new word is compared recursively  with the tree nodes'
	words starting from the tree's root node, according to the lexical order. If the
	word is not in the tree a new leaf is created.
*/
struct word* addToTree(struct word* inputWord, char *pString) {
  int stringDifference;
  if (inputWord == NULL) { // creates the node for the new word if there's no one yet
    inputWord = (struct word *) malloc(sizeof(struct word));
    if (inputWord == NULL) {
      printf("Program stopped: malloc failed 1\n");
      exit(FAIL);
    }
    inputWord->pString = pString;
    inputWord->pLeft = NULL;
    inputWord->pRight = NULL;
  }
	else if((stringDifference =     // compare the node's word with the new one
	       strcmp(inputWord->pString, pString)) != 0) {
           if(stringDifference > 0) {
             inputWord->pLeft = addToTree(inputWord->pLeft, pString);
           }
					 else {
             inputWord->pRight = addToTree(inputWord->pRight, pString);
           }
  }
  return inputWord;
}

/*
  Prints recursively the tree in alphabetical order.
*/
void printTree(struct word* inputWord) {
  if (inputWord != NULL) {
    printTree(inputWord->pLeft);
    printf("%s\n",inputWord->pString);
    printTree(inputWord->pRight);
  }
}
