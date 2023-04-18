/*************************** References **********************************************************
 * A reference variable is a "reference" to an existing variable, and it is created with the & operator*/


#include <iostream>
//#include <string>
using namespace std;

int main() {
  string food = "Pizza";
  string &meal = food;   ///& operator was used to create a reference variable

  cout << food << "\n";
  cout << meal << "\n";
  return 0;
}

