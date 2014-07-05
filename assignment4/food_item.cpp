/*
* Zach Toolson and Braeden Bodily
* January 31, 2014
*
* Assignment4 for cs3505 Software Practice II class.
* 
* Idea: Represent food items by UPC and name.
*/

#include <iostream>
#include <fstream> 
#include <map>
#include <vector>
#include <ctime>
#include "food_item.h"
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;

namespace inventory_report
{
	/* 
	*  Constructor:
	*  Builds a food item and associates it with a list of warehouses which contain
	*  this food item.
	*/
	FoodItem::FoodItem(string upc, string shelf_life, string food_name)
	{
		this->upc = upc;
		this->shelf_life = shelf_life;
		this->food_name = food_name;
	}
	
	
	/*
	*  Deconstructor
	*/
	FoodItem::~FoodItem()
	{
	}
	
}
