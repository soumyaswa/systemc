/*----------- NOTE==== The void keyword, used in the previous examples, indicates that the function should not return a value. If you want the function to return a value, you can use a data type (such as int, string, etc.) instead of void, and use the return keyword inside the --------------*/


#include <iostream>
using namespace std;

/*int myFunction(int x) { 
        cout << "valure of x is = "<< x << "\n";		
      	
		return 5 + x;


        
}

int main() {
	cout<<"the return value is = " <<myFunction(3)<< "\n" << endl ;
	 return 0;
}*/

//---------------returns the sum of a function with two parameters:---------------------------

int sum(int x , int y) { 
        cout << "valure of x is =  " << x << " value of y is =  " << y << "\n";		
      	
		return x + y;


        
}

int main() {
        //cout << sum(3 ,5 ) ;
	//another way to do the above line is 
	int z = sum(3,5);                                               //store the result in a variable
	//cout << "  = the return value  " << "\n" << endl ;
	cout << "the return value =  " << z << "\n" << endl ;
	 return 0;
}
