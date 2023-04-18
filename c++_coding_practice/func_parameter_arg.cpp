#include <iostream>
using namespace std;

/*void myFunction(string frame) {                    
      	cout << "Executing the name: "<< frame << "\n"<< endl;     
}

int main() {
  myFunction("soumya");
  myFunction("swagatika");
  myFunction("Mitul");
  return 0;
}*/

//--NOTE ------
//When a parameter is passed to the function, it is called an argument. So, from the example above: fname is a parameter, while soumya,swagatika and Mitul are arguments.
//


//-------Default parameter value--------------

/*void myFunction(string frame) {                    
      	cout << "Executing the name: "<< frame << "\n"<< endl;     
}
void myFunction1(string country = "India") {                    
      	cout << "Executing the country name: "<< country << "\n"<< endl;     
}


int main() {
  myFunction("soumya");
  myFunction("swagatika");
  myFunction("Mitul");
  myFunction1();
  myFunction1("USA");
  return 0;
}*/


//-------Multiple parameters-------------------

void myFunction(string frame, int age) {                    
      	cout << "Executing the name:  "<< frame << " , " <<" age = "<< age << "\n"<< endl;     
}

int main() {
  myFunction("soumya",21);
  myFunction("swagatika",22);
  myFunction("Mitul", 23);
  return 0;
}
