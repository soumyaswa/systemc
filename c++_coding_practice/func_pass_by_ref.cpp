/*NOTE======  You can also pass a reference to the function. This can be useful when you need to change the value of the arguments*/

//---------------------swaping of two numbers------------------------------

#include <iostream>
using namespace std;

void swap(int &x, int &y) {                  //&x and &y isthe address of the pointer object
  int z = x;
  x = y;
  y = z;
}

int main() {
  int firstnum = 10;
  int secondnum = 20;

  cout << "Before swap: " << " firstnum = "<< firstnum << " secondnum = "<< secondnum << "\n";
 
  //swap(firstnum, secondnum);
  swap(secondnum , firstnum);

  cout << "After swap: " <<" firstnum = "<< firstnum << " secondnum = "<< secondnum << "\n";
  
  return 0;
}
