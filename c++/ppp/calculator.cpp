#include <iostream>
#include "gui/std_lib_facilities.h"
using namespace std;

int main() {
  cout << "Please, enter an expression (use operators +, -, *, /):\n";
  cout << "End the expression usin a \';\'\n";
  int left_value = 0, right_value;
  int result;

  cin >> left_value;
  if ( ! cin ) cout << "First operand is missing.\n";
  for (char op; cin >> op;) {
    if (op != ';') cin >> right_value;
    if ( ! cin ) cout << "Second operand is missing.\n";
    switch (op) {
      case '+':
        left_value += right_value;
        break;
      case '-':
        left_value -= right_value;
        break;
      case '*':
        left_value *= right_value;
        break;
      case '/':
        left_value /= right_value;
      default:
        cout << "Result: " << left_value << "\n";
    }

  }
  cout << "Result: " << result << "\n";

  return 0;

}
