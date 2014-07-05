/*
 * Author: Zach Toolson
 * 4/3/2014
 *
 * A warehouse will be able to add and remove items from inventory.
 */


#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <map>
#include <vector>
#include "transaction.h"

using namespace std;

namespace inventory_report
{
	class Warehouse
	{
		public:
      // Constructor
      Warehouse(string name);
      // Destructor
			~Warehouse(); 
			
      // Inventory
      vector<Transaction> inventory;
      
      // Hold the current day of the warehouse
      boost::gregorian::date current_day;
      boost::gregorian::date busiest_day;
      int busiest_day_transactions;
      int current_day_transactions;
      string name;

			void set_current_day(boost::gregorian::date day);
      bool contains_inventory(string upc);
      void increase_transactions(int num_of_transactions);
      void reset_transactions();
	};	
}

#endif
