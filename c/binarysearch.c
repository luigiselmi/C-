#include <stdio.h>

void shellsort(char v[], int n);
int binsearch(char x, char v[], int size);

/* Search for a character in a sorted array. The input
   array is sorted using the shellsort algorithm. The
   shellsort algorithm has a time complexity of N^(3/2)
   where N is the size of the input array. Shellsort is
   efficient for small arrays. 
*/
int main() {
  char a[] = {'x', 'b', 'a', 'c', 'm', 'd'};
  int size = sizeof(a)/sizeof(a[0]);
  printf("Length = %d\n", size);
  shellsort(a, size);
  for (int i = 0; i < size; ++i)
    printf("%c", a[i]);
  printf("\n");
  char x = 'm';
  int found = binsearch(x, a, size);
  printf("Is %c in the array ? %s\n", x, found > 0 ? "True" : "False");
}
/* The Shell algorithm to sort an array */
void shellsort(char v[], int n) {
  int gap, i, j, temp;
  for (gap = n / 2; gap > 0; gap /= 2)
    for (i = gap; i < n; i++)
      for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
        temp = v[j];
        v[j] = v[j + gap];
        v[j + gap] = temp;
      }
}
/* Searches a value x in the (ordered) input array */
int binsearch(char x, char v[], int size) {
  int low = 0, high = size - 1, mid;
  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else
      return mid; // found
  }
  return -1; // not found
}
