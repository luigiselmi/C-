#include <stdio.h>

void shellsort(char v[], int n);
void reverse(char s[], int n);

/* Sorts an array using the shellsort algorithm. The
shellsort algorithm has a time complexity of N^(3/2)
where N is the size of the input array. Shellsort is
efficient for small arrays.*/

int main() {

  char a[] = {'x', 'b', 'a', 'c', 'm', 'd'};
  int size = sizeof(a)/sizeof(a[0]);
  printf("Length = %d\n", size);

  shellsort(a, size);
  for (int i = 0; i < size; ++i)
    printf("%c", a[i]);
  printf("\n");
  reverse(a, size);
  for (int i = 0; i < size; ++i)
    printf("%c", a[i]);
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

/* Reverse the array */
void reverse(char s[], int n) {
  int c, i, j;
  for (i = 0, j = n - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
