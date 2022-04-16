#include <stdio.h>

#define MAX_LEN 10 // max number of array's elements

void sort(int data[], int N);

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
