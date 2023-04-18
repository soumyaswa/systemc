/********************************************** pointer ***********************************************
 * A pointer however, is a variable that stores the memory address as its value.

A pointer variable points to a data type (like int or string) of the same type, and is created with the * operator. The address of the variable you're working with is assigned to the pointer*/


#include <iostream>
using namespace std;

int main() {
  string food = "Pizza";  // A string variable
  string* ptr = &food;  // A pointer variable that stores the address of food

    cout<< " Output the value of food : " << food << "\n";
    cout << " Output the memory address of food : "<<&food << "\n";
    cout << " Output the memory address of food with the pointer: "<< ptr << "\n";
  return 0;
}

