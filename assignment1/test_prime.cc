#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;


int main(int argc, char* argv[])
{
  // Check the number of parameters
  if (argc != 2)
  {
    cout << "Wrong number of arguements" << endl;
    return 0; //ends program
  }

  int prime;
  prime = atoi(argv[1]);
    
  bool is_prime;
  if (prime <= 1)
  {
    cout << "composite" << endl;
    return 0;
  }

  for (int i = 2; i < prime; i++)
  {
    if (prime % i == 0)
    {
      cout << "composite" << endl;
      return 0;
    }
  }

  cout << "prime" << endl;
}
