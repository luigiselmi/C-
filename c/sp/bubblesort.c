#include <stdio.h>

#define MAX_LEN 10 // max number of array's elements
#define NOT_FOUND -1

void sort(int data[], int N);
int binsearch(int x, int v[], int size);

/* Sorts an array using the bubblesort algorithm. */
int main() {
   int data[MAX_LEN];
   int N; // number of data points to be inserted
   int min, max;
   double mean = 0.0;

   printf("Number of data points (< %d): \n", MAX_LEN);
   scanf("%d", &N);

   for (int i = 0; i < N; ++i) {
      printf("Data point %d): ", i);
      scanf("%d", &data[i]);
   }

   sort(data, N);

   for (int i = 0; i < N; ++i)
      printf("%d\n",data[i]);

   printf("Write the number to be searched: \n");
   int x;
   scanf("%d", &x);
   int index = binsearch(x, data, N);
   index != NOT_FOUND ?
      printf("The sought value %d is at index %d of the sorted array.\n", x, index)
      :
      printf("The sought value %d has not been found.\n", x);
}
/* Bubblesort algorithm */
void sort(int data[], int N) {
   int temp;
   for (int i = 0; i < N - 1; i++) {
      for (int j = N - 1; j > i; j--) {
         if (data[j-1] > data[j]) {
            temp = data[j -1];
            data[j-1] = data[j];
            data[j] = temp;
         }
      }
   }
}
/* Searches a value x in the (ordered) input array
   using the binarysearch algorithm. The time complexity
   of the algorithm is log(N) + 1 (log base 2).
*/
int binsearch(int x, int v[], int size) {
  int low = 0, high = size - 1, middle;
  while (low <= high) {
    middle = (low + high) / 2;
    if (x < v[middle])
      high = middle - 1;
    else if (x > v[middle])
      low = middle + 1;
    else
      return middle; // found
  }
  return NOT_FOUND; // not found
}
