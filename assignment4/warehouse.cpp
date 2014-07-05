/*
 *
 */

#include <iostream>
#include <fstream> 
#include <map>
#include <vector>
#include <ctime>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "warehouse.h"
#include "transaction.h"

using namespace std;

namespace inventory_report
{
  /*
   * Constructor
   *
   * Set the name of the warehouse
   */
  Warehouse::Warehouse(string n)
  {
    this->name = n;
  }

	/*
	*  Deconstructor
	*/
	Warehouse::~Warehouse()
	{
	}

  /*
   * Set the current day of the warehouse
   */
	void Warehouse::set_current_day(boost::gregorian::date day)
	{
		this->current_day = day;
    this->busiest_day = day;
    this->busiest_day_transactions = 0;
    this->current_day_transactions = 0;
	}

  /*
   * Returns true if the item is in the inventory, otherwise returns 
   * false
   */
  bool Warehouse::contains_inventory(string upc)
  {
    bool in_inventory = false;

    // Iterate over all the inventory
    for(vector<Transaction>::iterator it = this->inventory.begin(); it < this->inventory.end(); ++it)
    {
      if(upc == it->upc)
        in_inventory = true;
    }

    return in_inventory;
  }

  /*
   * Increase the transactions for that day.
   */
  void Warehouse::increase_transactions(int num_of_transactions)
  {
    cout <<  "Increase transaction: " << num_of_transactions << endl;
    // Increase the transactions
    this->current_day_transactions += num_of_transactions;
    
    // Is today the busiest day, if so update busiest day information
    if (this->current_day_transactions >= this->busiest_day_transactions)
    {
      this->busiest_day_transactions = this->current_day_transactions;
      this->busiest_day = this->current_day;
    }
  }

  /*
   * Reset the current transactions to 0, this will happen on a next day
   */
  void Warehouse::reset_transactions()
  {
    this->current_day_transactions = 0;
  }
	
	
	
}
