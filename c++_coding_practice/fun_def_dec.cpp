#include <iostream>
using namespace std;


//----------here the function decleration is after the function int main so geting the error------------
/*int main() {
  myFunction();
  return 0;
}

void myFunction() {
  cout << "I just got executed!";
}*/

//ERROR message: 
//fun_def_dec.cpp: In function ‘int main()’:
//fun_def_dec.cpp:5:3: error: ‘myFunction’ was not declared in this scope
//5 |   myFunction();
//


// ------ resolve this with-----------------
void myFunction();              // function decleration
int main() {
  myFunction();
  myFunction();
  return 0;
}

void myFunction() {                    //function defination
  cout << "I just got executed! \n";     
}
