#include <iostream>
using namespace std;

double sum(int s);

class Vector {
  private:
    double* elem; // pointer to the elements
    int sz; // the number of elements
  public:
    Vector(int s): elem { new double[s] }, sz {s} { } // constructor
    double& operator[](int i) { return elem[i]; } // element access: subscripting
    int size() { return sz; }
};

int main() {
  // Class
  cout << "Sum elements of a vector: \n";
  double s = sum(5);
  cout << "Result: " << s << "\n";
  enum class Color { red, blue , green };

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
