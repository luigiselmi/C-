#include <iostream>
using namespace std;

#define MAX_ATTEMPTS 3

void print_sqr(double x);
double square(double x);
bool accept();

int main()
{
  cout<<"Hello, world! \n";
  auto x = 4.0; // type defined by its init value
  print_sqr(x);
  const double sqr = square(x); // constant evaluated at runtime
  if (accept())
    print_sqr(sqr);
}
double square(double x) {
  return x * x;
}
void print_sqr(double x) {
  cout << "The square of " << x << " is " << square(x) << "\n";
}
bool accept() {
  int attempts = 0;
  char answer = 0;
  while (attempts < MAX_ATTEMPTS) {
    cout << "Do you want to proceed (y/n) ?\n";
    cin >> answer;
    if (answer == 'y')
      return true;
    else if (answer == 'n')
      return false;
    else
      cout << "Use only \'y\' or \'n\'.\n";
    ++attempts;
  }
  return false; // in case of wrong answer after MAX_ATTEMPTS
}
