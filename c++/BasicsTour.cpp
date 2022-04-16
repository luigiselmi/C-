#include <iostream>
using namespace std;

double sum(int s);
void test(int s);

constexpr double MAX_SIZE = 3;

class Vector {
  private:
    double* elem; // pointer to the elements
    int sz; // the number of elements
  public:
    Vector(int s) {
      if (s < 0) throw length_error{"Size cannot be negative."};
      elem = new double[s];
      sz = s;
    }
    double& operator[](int i) { return elem[i]; } // element access: subscripting
    int size() { return sz; }
};

int main() {
  // Class
  cout << "Computes the sum of a vector's values: \n";
  double s = sum(MAX_SIZE);
  cout << "Result: " << s << "\n";
  enum class Color { red, blue , green };

  // Error handling
  test(-5);

  // Enumeration
  Color x = Color::red;
  Color y = Color::green;
  if (x == y)
    cout << "Same color\n";
  else
    cout << "Different color\n";

  enum class TrafficLight { green, yellow, red };

  TrafficLight light = TrafficLight::red;
  if (light == TrafficLight::green)
    cout << "You can go !\n";
  else
    cout << "Don't move !\n";

  //++light;

  if (light == TrafficLight::green)
    cout << "You can go !\n";
  else
    cout << "Don't move !\n";

}
double sum(int s) {
  Vector v(s);
  double sum = 0.0;
  cout << "Write " << s << " integers\n";
  for (int i = 0; i < v.size(); ++i) {
    cin >> v[i];
    sum += v[i];
  }
  return sum;
}
void test(int s) {
  try {
    cout << "Size = " << s << "\n";
    Vector v(s);
  }
  catch (std::length_error) {
    cout << "Error: size cannot be negative!\n";
  }
  catch (std::bad_alloc) {
    cout << "No memory available.\n"; // handle memory exhaustion
  }
}
/*
TrafficLight& operator++(TrafficLight& t) {
  switch (t) {
    case TrafficLight::green:
      return TrafficLight::yellow;
    case TrafficLight::yellow:
      return TrafficLight::red;
    case TrafficLight::red:
      return TrafficLight::green;
  }
}
*/
