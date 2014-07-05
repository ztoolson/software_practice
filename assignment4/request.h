/*
* Zach Toolson
* 4/3/2014
*
* Assignment4 for cs3505 Software Practice II class.
* 
* Header file for a request object.
*/

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

using namespace std;

namespace inventory_report
{
	class Request 
	{
		public:
      // Constructor
			Request(string upc, string quantity, string warehouse);  
      // Destructor
			~Request(); 
			
			string upc;			// Variable to keep track of food UPC
      string quantity; // quantity requested
      string warehouse; // Warehouse the item is being requested from
	};	
}

#endif
