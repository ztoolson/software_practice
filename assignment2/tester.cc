#include <iostream>
#include <string>
#include "huge_number.h"

using namespace std;

/*
 * Very simple tester used to make sure assignment compiles
 */
int main()
{
  string a = "1234";
  string b = "456"; 
  huge_number h(a);
  huge_number i(b);

  huge_number copy(h);

  huge_number z;
  
  z = h * i - h; 
}
