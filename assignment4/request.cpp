/*
* Zach Toolson 
* April 3, 2014 
*
* Assignment4 for cs3505 Software Practice II class.
* 
* Request object implementation 
*/

#include <iostream>
#include <fstream> 
#include <map>
#include <vector>
#include <ctime>
#include <string>
#include "request.h"

using namespace std;

namespace inventory_report
{
	/* 
	*  Constructor:
	*  Builds a food item and associates it with a list of warehouses which contain
	*  this food item.
	*/
	Request::Request(string upc, string  quantity, string warehouse)
	{
		this->upc = upc;
    this->quantity = quantity;
    this->warehouse = warehouse;
	}
	
	
	/*
	*  Deconstructor
	*/
	Request::~Request()
	{
	}
	
}
