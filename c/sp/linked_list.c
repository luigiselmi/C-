/*
  An example of linked list
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 100

#define INVERSE_LIST 0
#define DIRECT_LIST 1

#define MY_SUCCESS 0
#define _FAILURE -9

FILE *fInput;
char *fInputName = "data/manzoni.dat";

//int listType = INVERSE_LIST;
int listType = DIRECT_LIST;
char myString[MAX_STRING_LENGTH];

void init(void);
void openFile(void);
int readWord(void);
void buildInverseList(void);
void buildDirectList(void);
void printInverseList(void);
void printDirectList(void);

/* creiamo il puntatore che indica la lista
   e visto che all'inizio la lista e' vuota
   lo inizializziamo a NULL */

struct word{
  char *pointerToString;
  struct word *pointerToNextWord;
} *wordList = NULL;

struct word *pointerStart;

/*****************************************************************************/
int main(void) {
  int myEnd = 0;

  init();
  openFile();

  while(myEnd != 1){ // myEnd = 1 when the end of file is reached
    myEnd = readWord();
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
  lexical analysis: reads words one by one till the end of the input file.
*/
int readWord(void) {
  char myFlag = 1; // myFlag = 0 when a word is complete
  int j, myEnd = 0; // myEnd = 1 when the end of file is reached
  j = 0;
  while ( (j < MAX_STRING_LENGTH) && (myFlag == 1) ) {
    myString[j] = fgetc(fInput); // reads a character from the stream
    if (myString[j] == ' ') {
      myString[j] = '\0';
      myFlag = 0;
    }
    else if (myString[j] == '\n') { // remove end of line
      j--;
    }
    else if(myString[j] == EOF){
      myEnd = 1;
      myString[j] = '\0';
      myFlag = 0;
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
  printf("Word of length %ld: %s\n", strlen(myString), myString);
  return myEnd;
}

/*****************************************************************************/
void buildInverseList(void) {
  char *scratchPointer;
  struct word *wordScratchPointer, *pointerCheck;

  for (pointerCheck = wordList; pointerCheck != NULL; ) {
    if(strcmp(pointerCheck -> pointerToString, myString) == 0)
      return;
    pointerCheck = pointerCheck -> pointerToNextWord;
  }

  scratchPointer = (char *) malloc(strlen(myString));
  if (scratchPointer == NULL) {
    printf("Execution stopped: failed malloc 1 in c_l_i\n");
    exit(_FAILURE);
  }

  wordScratchPointer = wordList;
  wordList = (struct word *) malloc(sizeof(struct word));
  if (wordList == NULL) {
    printf("Execution stopped: failed malloc 2 in c_l_i\n");
    exit(_FAILURE);
  }
  strcpy(scratchPointer, myString);
  wordList -> pointerToString = scratchPointer;
  wordList -> pointerToNextWord = wordScratchPointer;
}

/*****************************************************************************/
void buildDirectList(void) {
  char *scratchPointer;
  struct word *wordScratchPointer, *pointerCheck;

  for (pointerCheck = pointerStart; pointerCheck != NULL; ) {
    if(strcmp(pointerCheck -> pointerToString, myString) == 0) return;
    pointerCheck = pointerCheck -> pointerToNextWord;
  }

  scratchPointer = (char *) malloc(strlen(myString));
  if (scratchPointer == NULL) {
    printf("Execution stopped: failed malloc 1 in c_l_d\n");
    exit(_FAILURE);
  }

  wordScratchPointer = wordList;
  wordList = (struct word *) malloc(sizeof(struct word));
  if (wordList == NULL) {
    printf("Execution stopped: failed malloc 2 in c_l_d\n");
    exit(_FAILURE);
  }
  strcpy(scratchPointer,myString);
  wordList -> pointerToString = scratchPointer;
  wordList -> pointerToNextWord = NULL;
  if (wordScratchPointer != NULL)
    wordScratchPointer -> pointerToNextWord = wordList;
  if (wordScratchPointer == NULL) pointerStart = wordList;
}

/*****************************************************************************/
void printInverseList(void) {
  struct word *wordScratchPointer = wordList;
  do {
    printf("%s\n", wordScratchPointer -> pointerToString);
    wordScratchPointer = wordScratchPointer -> pointerToNextWord;
  } while(wordScratchPointer != NULL);
}

/*****************************************************************************/
void printDirectList(void) {
  struct word *wordScratchPointer = pointerStart;
	do {
    printf("%s\n", wordScratchPointer -> pointerToString);
    wordScratchPointer = wordScratchPointer -> pointerToNextWord;
  } while (wordScratchPointer -> pointerToNextWord != NULL);

  printf("%s\n", wordScratchPointer -> pointerToString);
}
