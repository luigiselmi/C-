#include <stdio.h>

#define MAX_NUM_COLS 10

void insert_data(double a[][MAX_NUM_COLS], double b[], int n); // nm of columns must be specified before hand
void print_data(double a[][MAX_NUM_COLS], double b[], int n);
void triangle(double A[][MAX_NUM_COLS], double b[], int n);
void solve(double A[][MAX_NUM_COLS], double b[], double x[], int n);
void print_solution(double x[], int n);

/* Solves a system of linear equations, matrixx = b, by Gaussian elimination
   In this example we see how multdimensional arrays can be passed as argument
   to a function.
*/
int main() {

  int n; // number of linear equations

  printf("Insert the rank of the linear system (< %d):\n", MAX_NUM_COLS);
  scanf("%d", &n);

  if (n > MAX_NUM_COLS) {
    printf("Only %d columns are allowed.\n", MAX_NUM_COLS);
    return -1;
  }

  double A[n][MAX_NUM_COLS], b[n], x[n];
  insert_data(A, b, n);
  print_data(A, b, n);

  triangle(A, b, n);
  solve(A, b, x, n);
  print_data(A, b, n);
  print_solution(x, n);

}
/* Inserts the matrix coefficients and the known values */
void insert_data(double A[][MAX_NUM_COLS], double b[], int n) {
  printf("\nInsert the matrix coefficients:\n");
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      printf("A[%d, %d]=", i, j);
      scanf("%lf", &A[i][j]); // the format %lf is required for double precision
    }

  printf("\nInsert the known values:\n");
  for (int i = 0; i < n; i++) {
    printf("b[%i] = ", i);
    scanf("%lf", &b[i]);
  }

}
/* Prints the matrix coefficients and the known values */
void print_data(double A[][MAX_NUM_COLS], double b[], int n) {
  printf("\n");
  // prints the matrix
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      printf("%.2f ", A[i][j]);
    printf("\n");
  }

  printf("\n");
  for (int i = 0; i < n; ++i)
    printf("%.2f\n", b[i]);
}
/* Transforms the input matrix into a triangular matrix */
void triangle(double A[][MAX_NUM_COLS], double b[], int n) {
  int i, j, k;
  double c;

  // divide the i-th equation by its diagonal element
  for (i = 0; i < n; ++i) {
    c = A[i][i];
    for (j = i; j < n; j++) {
      A[i][j] /= c;
    }
    b[i] /= c;
    // subtract the normalized equation from the others
    for (k = i + 1; k < n; k++) {
      c = A[k][i];
      for (j = i; j < n; j++) {
        A[k][j] -= A[i][j] * c;
      }
      b[k] -= c * b[i];
    }
  }

}
/* Once the matrix is in triangular form it can be inverted so that
   x = A(^-1)b
*/
void solve(double A[][MAX_NUM_COLS], double b[], double x[], int n) {
  int i, k;
  double s;
  x[n] = b[n] / A[n][n];
  for (k = n - 1; k >= 0; k--) {
    s = 0.;
    for (i = k + 1; i < n; i++) {
      s += A[k][i] * x[i];
    }
    x[k] = b[k] - s;
  }
}
void print_solution(double x[], int n) {
  printf("\nThe solution x of the linear system is:\n");
  for (int i = 0; i < n; i++)
    printf("x[%d]=%.2f\n", i, x[i]);
}
