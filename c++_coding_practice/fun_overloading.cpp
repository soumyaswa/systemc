/************************************ NOTE  ******************************************************************
 * Function Overloading
With function overloading, multiple functions can have the same name with different parameters*/

#include <iostream>
using namespace std;

/*int int_fun(int x, int y) {
  return x + y;
}

float float_func(float x, float y) {
  return x + y;
}

double double_func(double x, double y) {
  return x + y;
}

int main() {
  int n1 = int_fun(3, 5);
  float n2 = float_func(2.1521111111, 6.2600000001);
  double n3 = double_func(2.1521111111, 6.2600000010);
  cout << "Int: " << n1 << "\n";
  cout << "Float: " << n2 << "\n";
  cout << "Double: " << n3 << "\n";
  return 0;
}*/

//*************************************************************************************************************************************************************
//****************************************************               NOTE               ***********************************************************************
//*************************************************************************************************************************************************************
//******************************************          DIFFERENCE BETWEEN FLOAT AND DOUBLE         *************************************************************
//*************************************************************************************************************************************************************
/*In C++, float and double are both used to store floating-point numbers. Floating-points values are real numbers, for eg: 1801.0, -4.258, or 0.08244. These two data types differ from each other in many ways. Now, understand how the float differs from the  C++ double.

Float: The C++ float type is a primitive data type that holds floating values up to 7 digits. 

Double: The C++ double is also a primitive data type that is used to store floating-point values up to 15 digits*/


int main()
{
    // initialize float and double variables
    float var1 = 1.1426F;       // the float value should end with an 'f'
    double var2 = 1.1426576; 
    // print the size of the float variable and the value of the long double variable
    cout << "The float datatype takes " << sizeof(var1) << " bytes in the memory." << "\t \t The value stored in the variable is: " << var1 <<"\n";
    // print the size of the long double variable and the value of the long double variable
    cout << "The long double datatype takes " << sizeof(var2) << " bytes in the memory."<< "\t \t the value stored in the variable is: " << var2 << "\n"; 
    return 0;

}
