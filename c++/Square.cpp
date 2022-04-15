#include <iostream>
using namespace std;

const int v1[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

void print_square(double x);
void copy_fct();
double read_and_sum(int s);
bool accept();

int main()
{
  if (accept())
  {
    print_square(2.0);
    copy_fct();
    double sum = read_and_sum(5);
    cout << sum;
  }
}

double square(double x) {
  return x * x;
}

void print_square(double x) {
  cout << "the square of " << x << " is " << square(x) << "\n";
}
/* Copies an array's values into another */
void copy_fct() {

  int v2[10];
  for (int i = 0; i < 10; i++)
    v2[i] = v1[i];

  for (int x: v2) // range-for loop
    cout << x << "\n";
}

struct Vector {
  int size;
  double* elem;
};

void vector_init(Vector& v, int s) {
  v.elem = new double[s];
  v.size = s;
}

double read_and_sum(int s) {
  Vector v;
  vector_init(v, s);
  for (int i = 0; i < s; i++)
    cin >> v.elem[i];  // read elements from standard input
  double sum = 0.0;
  for (int i = 0; i < s; i++)
    sum += v.elem[i];
  return sum;
}

bool accept() {
  cout << "Do you want to proceed (y or n)?\n";
  char answer = 0;
  cin >> answer;
  if (answer == 'y') return true;
  return false;
}
