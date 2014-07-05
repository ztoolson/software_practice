/*
* Zach Toolson
* 4/3/2014
*
* Assignment4 for cs3505 Software Practice II class.
* 
* Header file for a transaction objects.
*/

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;

namespace inventory_report
{
	class Transaction 
	{
		public:
      // Constructor
			Transaction(string upc, int quantity, boost::gregorian::date expire_date);  
      // Destructor
			~Transaction(); 
			
			string upc;			// Variable to keep track of food UPC
      int quantity;
      boost::gregorian::date expire_date;
	};	
}

#endif
