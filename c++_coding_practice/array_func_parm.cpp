

#include <iostream>  
using namespace std;  
const int N=10;

void myFunction(int myNumbers[N]) {
  for (int i = 0; i < N; i++) {  
    cout   <<"array index : [ "<<  i  << " ] " << "\t" <<" the array elements : "<< myNumbers[i] << "\n";    
  } 
}

int main() {  
  int myNumbers[N] = {10, 20, 30, 40, 50};  
  myFunction(myNumbers);
  return 0;
}  

