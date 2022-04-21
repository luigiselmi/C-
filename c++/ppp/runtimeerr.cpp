#include <iostream>
using namespace std;

/* Examples of throwing and catching errors and used-defined exceptions */

double area(double a, double b);
double volume(double a, double b, double c);
class Bad_Input { };

int main() {
  // catch a user defined exception
  cout << "Write height and width of a rectangle to compute its area:\n";
  double r_width, r_height;
  cin >> r_width >> r_height;
  try {
    double a = area(r_width, r_height);
    cout << "The area of the rectangle is " << a << " square meters.\n";
  }
  catch (Bad_Input){
    cerr << "Oops! Bad arguments to area()\n";
    return 1;
  }

  // runtime error (standard library)
  cout << "Write length, depth and height to compute the volume of a parallelepiped:\n";
  double p_length, p_depth, p_height;
  cin >> p_length >> p_depth >> p_height;
  try {
    double v = volume(p_length, p_depth, p_height);
    cout << "The volume of the parallelepiped is " << v << " cubic meters.\n";
  }
  catch (runtime_error &e){
    cerr << "Oops! A runtime error occurred. More specific info follows:\n" << e.what() << "\n"; // writes to standard error
    return 1;
  }

}
double area(double a, double b) {
  if (a <= 0 || b <= 0) throw Bad_Input{};
  return a * b;
}
double volume(double a, double b, double c) {
  if (a <= 0 || b <= 0 || c <= 0) throw runtime_error("Bad input in volume()\n");
  return a * b * c;
}
