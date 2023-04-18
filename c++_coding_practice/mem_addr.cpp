#include <iostream>
//#include <string>
using namespace std;

int main() {
  string food = "Pizza";
  string &meal = food;   ///& operator was used to create a reference variable

  cout <<" string of food : " << food << "\n";
  cout <<" memory address of food: "<< &food << "\n";
  cout << " string of meal " << meal << "\n";
  cout <<" memory address of meal: "<<  &meal << "\n";
  return 0;
}

