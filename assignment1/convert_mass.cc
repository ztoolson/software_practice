#include <iostream>

using namespace std;

int main()
{
  double weight_lbs;

  while(true)
  {
    cout << "Enter your weight in pounds: ";
    cin >> weight_lbs;

	  if(cin.good()) //valid number
	  {
	    double weight_kg = weight_lbs / 2.20462;

	    // To get the double to two decimal precision, multiply weight_kg by 100
	    // and then divide the result by 100
	    weight_kg =(int)(weight_kg * 100);
	    weight_kg = (float) (weight_kg / 100.00);

	    cout << "Your weight in kilograms is: " <<  weight_kg << endl;
	    break;
	  }
	  else // Non valid number, prompt user again for valid input
	  {
	    cout << "Invalid Input. Please enter a numberic value." <<  endl;
	    cin.clear();
      cin.ignore(100000, '\n');
	  }
  }
}

