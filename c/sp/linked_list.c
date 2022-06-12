/*
  An example of linked list. The program opens a file
  and parses the text reading words separated by a white
  space. Each word is put in a structure with a pointer
  to the next word. The program can be configured to build
  a list of words in the same order as they appear in the
  text or in an inverse order.
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 100

#define INVERSE_LIST 0
#define DIRECT_LIST 1

#define _SUCCESS 0
#define _FAILURE -9

FILE *fInput;
char *fInputName = "data/manzoni.dat";

//int listType = INVERSE_LIST;
int listType = DIRECT_LIST;
char token[MAX_STRING_LENGTH]; // set of characters used to store words when complete

void init(void);
void openFile(void);
int readWord(void);
void buildInverseList(void);
void buildDirectList(void);
void printInverseList(void);
void printDirectList(void);

struct word{
  char *pString;
  struct word *pNext;
} *wordList = NULL;

struct word *pFirst;

/*****************************************************************************/
int main(void) {
  int end_of_file = 0;
  init();
  openFile();

  while(end_of_file != 1){ // end_of_file = 1 when the end of file is reached
    end_of_file = readWord();
    switch(listType){
    case INVERSE_LIST:
      buildInverseList();
      break;
    case DIRECT_LIST:
      buildDirectList();
      break;
    default:
      printf("Execution stopped: index type unknown %d %d.\n", INVERSE_LIST, listType);
      exit(_FAILURE);
    }
  }
  fclose(fInput);

  switch(listType){
  case INVERSE_LIST:
    printInverseList();
    break;
  case DIRECT_LIST:
    printDirectList();
    break;
  default:
    printf("Execution stopped: index type unknown %d %d.\n", INVERSE_LIST, listType);
    exit(_FAILURE);
  }
}

/*****************************************************************************/
void init(void) {
  switch (listType) {
    case INVERSE_LIST:
      printf("# Creating an inverse index\n");
      break;
    case DIRECT_LIST:
      printf("# Creating an index\n");
      break;
    default:
      printf("Error: index type unknown %d.\n", listType);
      exit(_FAILURE);
  }
}

/*****************************************************************************/
void openFile(void) {
  fInput = fopen(fInputName,"r");
  if(fInput==NULL){
    printf("Abort: cannot open the file with read permissions: %s\n", fInputName);
    exit(_FAILURE);
  }

  printf("# The input file is open: %s\n", fInputName);
}

/*
  lexical analysis: reads tokens of characters that are interpreted
  as words when separated by a white space. The token is stored in
  a global variable till it is a complete word. The function returns
  an integer, after a word has been read, to indicate whether the end
  of the file has been reached (1) or not (0).
*/
int readWord(void) {
  char wordComplete = 0; // 1 when a word is complete
  int j, end_of_file = 0; // end_of_file = 1 when the end of file is reached
  j = 0;
  while ( (j < MAX_STRING_LENGTH) && (wordComplete == 0) ) {
    token[j] = fgetc(fInput); // reads a character from the stream
    if (token[j] == ' ') {
      token[j] = '\0';
      wordComplete = 1;
    }
    else if (token[j] == '\n') { // remove end of line
      j--;
    }
    else if(token[j] == EOF){
      end_of_file = 1;
      token[j] = '\0';
      wordComplete = 1;
    }
    j++;
  }
  /* per sicurezza mi sto riservando un carattere in piu' oltre
    al terminatore \0 */
  if (j >= MAX_STRING_LENGTH - 1) {
    printf("Execution stopped: the word was tool long.\n");
    printf("Compile again with a larger value of MAX_STRING_LENGTH. The current value is %d.\n", MAX_STRING_LENGTH);
    exit(_FAILURE);
  }
  //printf("Word of length %ld: %s\n", strlen(token), token);
  return end_of_file;
}

/*
  This function is called from a loop in the main function every time a word has
  been found in the text. The function checks whether the token is already in the
  list, and if not it allocates the memory space for the new word element. The new
  word is put on the top of the list so that when it's printed the list appears
  to be the inverse of the original text.
*/
void buildInverseList(void) {
  char *pString; // pointer to the memory reserved for the next word
  struct word *pTempWordList; // pointer to the current word list
  struct word *pStringCheck; // pointer used to navigate the word list

  // loops into the word list to check whether the string is already there
  for (pStringCheck = wordList; pStringCheck != NULL; ) {
    if(strcmp(pStringCheck -> pString, token) == 0)
      return;
    pStringCheck = pStringCheck -> pNext;
  }

  pString = (char *) malloc(strlen(token)); // allocates the memory space to store the string
  if (pString == NULL) {
    printf("Execution stopped: failed malloc 1 in c_l_i\n");
    exit(_FAILURE);
  }

  pTempWordList = wordList;
  wordList = (struct word *) malloc(sizeof(struct word)); // allocate the memory space for the word structure
  if (wordList == NULL) {
    printf("Execution stopped: failed malloc 2 in c_l_i\n");
    exit(_FAILURE);
  }
  strcpy(pString, token); // copies the value of the token into the memory space allocated to store it
  wordList -> pString = pString;  // set the pointer to the word
  wordList -> pNext = pTempWordList; // set the pointer to the next word element
}

/*
  This function is the same as the buildInverseList() function but
  words are put at the end of the list so that when it's printed the
  words are printed in the same order as in the original text.
*/
void buildDirectList(void) {
  char *pString; // pointer to the memory reserved for the next word
  struct word *pTempWordList; // pointer to the current word list
  struct word *pStringCheck; // pointer used to navigate the word list

  // loops into the word list to check whether the string is already there
  for (pStringCheck = pFirst; pStringCheck != NULL; ) {
    if(strcmp(pStringCheck -> pString, token) == 0) return;
    pStringCheck = pStringCheck -> pNext;
  }

  pString = (char *) malloc(strlen(token)); // allocates the memory space to store the string
  if (pString == NULL) {
    printf("Execution stopped: failed malloc 1 in c_l_d\n");
    exit(_FAILURE);
  }

  pTempWordList = wordList;
  wordList = (struct word *) malloc(sizeof(struct word));
  if (wordList == NULL) {
    printf("Execution stopped: failed malloc 2 in c_l_d\n");
    exit(_FAILURE);
  }
  strcpy(pString, token);
  wordList -> pString = pString;
  wordList -> pNext = NULL;
  if (pTempWordList != NULL) pTempWordList -> pNext = wordList;
  if (pTempWordList == NULL) pFirst = wordList;
}

/*****************************************************************************/
void printInverseList(void) {
  struct word *pTempWordList = wordList; // pointer to the current word list
  do {
    printf("%s\n", pTempWordList -> pString);
    pTempWordList = pTempWordList -> pNext;
  } while(pTempWordList != NULL);
}

/*****************************************************************************/
void printDirectList(void) {
  struct word *pTempWordList = pFirst;
	do {
    printf("%s\n", pTempWordList -> pString);
    pTempWordList = pTempWordList -> pNext;
  } while (pTempWordList -> pNext != NULL);

  printf("%s\n", pTempWordList -> pString);
}
