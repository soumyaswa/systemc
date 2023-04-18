#include <iostream>
using namespace std;

/*void myFunction() {
  cout << "I just got executed! \n";
}

int main() {
  myFunction();
  return 0;
}*/

//-----------A function can be called multiple times:----------------------------
//
void myFunction() {
  cout << "I just got executed! \n";
}

int main() {
  myFunction();
  myFunction();
  myFunction();
  return 0;
}

