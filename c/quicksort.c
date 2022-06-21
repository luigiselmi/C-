/*
   Implementation of the quicksort algorithm to sort an array.
   The time complexity for quicksort is NlogN and it works inplace,
   that is, it doesn't require an auxiliary array.
 */

#include <stdio.h>

void qsort(int v[], int left, int right);
void print(int v[], int size);

int main() {
  //int s[] = {1, 9, 5, 2, 7, 6, 3, 4, 8, 0};
  int s[] = {'z', 'p', 'a', 'r', 'b', 'e', 'c', 'q', 'm', 'n'};
  int size = sizeof(s) / sizeof(s[0]);
  print(s, size);
  qsort(s, 0, size - 1);
  print(s, size);
}
void qsort(int v[], int left, int right) {
  int last;
  void swap(int v[], int i, int j);

  if(left >= right)
    return;

  swap(v, left, (left + right) / 2);
  last = left;
  for (int i = left + 1; i <= right; i++)
    if(v[i] < v[left])
      swap(v, ++last, i);

  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}
void swap(int v[], int i, int j) {
  int temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
void print(int v[], int size) {
  for (int i = 0; i < size; ++i)
    printf("%c", v[i]);
  printf("\n");
}
