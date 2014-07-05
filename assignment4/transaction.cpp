/*
* Zach Toolson 
* January 31, 2014
*
* Assignment4 for cs3505 Software Practice II class.
* 
* transaction for a recieve request 
*/

#include <iostream>
#include <fstream> 
#include <map>
#include <vector>
#include <ctime>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "transaction.h"

using namespace std;

namespace inventory_report
{
	/* 
	*  Constructor:
	*  Builds a food item and associates it with a list of warehouses which contain
	*  this food item.
	*/
	Transaction::Transaction(string upc, int  quantity, boost::gregorian::date expire_date)
	{
		this->upc = upc;
    this->quantity = quantity;
    this->expire_date = expire_date;
	}
	
	
	/*
	*  Deconstructor
	*/
	Transaction::~Transaction()
	{
	}
	
}
