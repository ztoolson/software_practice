/*
* Zach Toolson
* Modified 4/3/2014
* January 31, 2014
*
* Assignment4 for cs3505 Software Practice II class.
* 
* Header file for our food item objects.
*/

#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>

using namespace std;

namespace inventory_report
{
	class FoodItem 
	{
		public:
      // Constructor
			FoodItem(string upc, string shelf_life, string food_name);  
      // Destructor
			~FoodItem(); 
			
			string upc;			// Variable to keep track of food UPC
			string shelf_life;	// String shelf life of food, in days
			string food_name;	// Variable for name of food
	};	
}

#endif
