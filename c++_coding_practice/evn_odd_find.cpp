#include <iostream>
using namespace std;

int main() {
  int n;

  cout << "Enter an integer: ";           //for entering a number using this
  cin >> n;

  if ( n % 2 == 0)
    cout << n << " is even."<< "\n";
  else
    cout << n << " is odd."<< "\n";

  return 0;
}


//----------------c code for this --------------------------
/*#include <stdio.h>
int main() {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);

    // true if num is perfectly divisible by 2
    if(num % 2 == 0)
        printf("%d is even.", num);
    else
        printf("%d is odd.", num);
    
    return 0;
}*/

