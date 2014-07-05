/*
 * Zach Toolson
 * March 29, 2014 
 *
 * Assignment4 for cs3505 Software Practice II class.
 * 
 * Represent a chain of warehouses and read in a file stating the 
 * data regarding inventory in the transactions.
 */

#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <map>
#include <vector>
#include <ctime>
#include "food_item.h"
#include "warehouse.h"
#include "transaction.h"
#include "request.h"

using namespace std;
using namespace inventory_report;

map<string, FoodItem> food_items; // upc -> FoodItem
map<string, Warehouse*> warehouses; // warehouse_name -> Warehouse
vector<Request> requests;
vector<FoodItem> non_stocked_items;
vector<FoodItem> fully_stocked_items;

/*
 * set the date for all of the warehouses
 */
void set_date(boost::gregorian::date date)
{
  for (map<string, Warehouse*>::iterator it = warehouses.begin(); it  != warehouses.end(); ++it)
  {
    it->second->set_current_day(date);
    
  }
}

/*
 * Process the requst and remove the quantity requested.
 */
void process_request(string upc, string warehouse, string quantity)
{
  // Get warehouse object. Get quantity requested as a number
  Warehouse *w = warehouses.find(warehouse)->second; // Get warehouse from map
  int quant = atoi(quantity.c_str()); // Quantity to remove as an int

  // Update busiest day
  w->increase_transactions(quant);
  
  // Find the item that will expire first from the warehouse, this item will be at the beginning
  int count = 0;
  for(vector<Transaction>::iterator it = w->inventory.begin(); it < w->inventory.end(); ++it)
  {
    // Check to see if this is the right item
    // The first item matched is the one expiring soonest
    if(it->upc == upc)
    {
      // Can this item fulfill the request?
      // If so, update quantity and then be done
      if(quant <= it->quantity)
      {
        it->quantity = it->quantity - quant;
        break;
      }
      // Make sure item isn't already empty
      // Skip this item and check others
      else if (it->quantity <= 0)
      {
        break;
      }
      // Item cannot fulfill request, but can fulfill some
      // Remove all possible items and continue on to the next item. 
      else
      {
        quant = quant - it->quantity;
        it->quantity = 0;
      }
    }
  }
}

/*
 * Reads in the data file and interprests the lines to extract
 * the relevant information. It then proceedes to build all of the
 * warehouse and food objects that will be used for the ordering process.
 *
 * Once the ordering process is done (first it processes the recieves, then
 * the requests are processed) We do some searching amonst the warehouses
 * to determine which items are in every warehoues, and which items aren't
 * in any of the warehouses.
 *
 * Output the results and clean up memory.
 */
int main(int argc, char** argv)
{
  fstream data_file(argv[1]); // load the file from command line

  // Read in the data from the file and determine the line process. 
  // While loop terminates when the End line is read in.
  while(true) 
  {
    string line;

    // Read in the first word of the line
    getline(data_file, line, ' '); 

    /*
     * Determine what the input line is and get relevent data
     * from the line. This parses the file word by word
     */

    // Build the food items and warehouses
    if(line.compare("FoodItem") == 0)
    {
      // Data to store from food item request
      string upc, shelf_life, food_name;


      // Get the UPC Code 
      getline(data_file, line, ':'); // read up to UPC Code:
      getline(data_file, line, ' '); // skip over first space

      getline(data_file, line, ' '); // Gets the UPC CODE!!
      upc = line;

      // Get the shelf life
      getline(data_file, line, ':');
      getline(data_file, line, ' ');

      getline(data_file, line, ' ');
      shelf_life = line;

      // Get the Food Name
      getline(data_file, line, ':');
      getline(data_file, line, ' ');

      getline(data_file, line); // everything till the end of the line is the food name      
      food_name = line;

      // Build the food item
      FoodItem f(upc, shelf_life, food_name);

      // Add food item to the map
      food_items.insert( pair<string, FoodItem>(upc, f) );
    }
    else if(line.compare("Warehouse") == 0)
    {
      string warehouse_name;

      // Get to the warehouse name
      getline(data_file, line, '-');
      getline(data_file, line, ' ');

      getline(data_file, line);
      warehouse_name = line;

      // build and add the warehouse map
      Warehouse *w = new Warehouse(warehouse_name);

      // Add to map of warehouses
      warehouses[warehouse_name] = w;
    }

    // Set the start date to begin transactions
    else if(line.compare("Start") == 0)
    {
      string month, day, year;

      // Move through the line of text to the actual date
      getline(data_file, line, ':');
      getline(data_file, line, ' ');

      // Get the month
      getline(data_file, line, '/');
      month = line;

      // Get the day
      getline(data_file, line, '/');
      day = line;

      // Get the year
      getline(data_file, line);
      year = line;

      // Set variable current day in cental hub   
      string date_format = year + "/" + month + "/" + day;
      boost::gregorian::date start_date(boost::gregorian::from_string(date_format));

      // Set the start date on all the warehouses
      set_date(start_date);
    }

    // Start of orders
    else if(line.compare("Receive:") == 0)
    {
      string upc, warehouse, quantity;

      // Get the upc
      getline(data_file, line, ' ');
      upc = line;

      // Get the quantity
      getline(data_file, line, ' ');
      quantity = line;

      // Get the Warehouse name
      getline(data_file, line);
      warehouse = line;
  
      // Get the FoodItem and Warehouse needed to input the item
      FoodItem f = food_items.find(upc)->second; // Get FoodItem from the map
      Warehouse *w = warehouses.find(warehouse)->second; // Get warehouse from map
      
      int quant = atoi(quantity.c_str()); // Quantity as an int

      // Calculate date of expiration for item recieved
      int d = atoi(f.shelf_life.c_str()); // days to expire
      boost::gregorian::date_duration days_to_add(d);
      boost::gregorian::date expiration_date = w->current_day + days_to_add; // date of expiration

      // Store data in a transaction object and insert into the warehouse inventory
      // Inserts it at the end of the warehouse list
      w->inventory.push_back(Transaction(upc, quant, expiration_date));

      // Update busiest day
      w->increase_transactions(quant);
    }
    else if(line.compare("Request:") == 0)
    {
      string upc, quantity, warehouse;

      // Get the upc string
      getline(data_file, line, ' ');
      upc = line;

      // Get the quantity string
      getline(data_file, line, ' ');
      quantity = line;

      // Get the Warehouse string
      getline(data_file, line);
      warehouse = line;

      //  Add to request list
      requests.push_back(Request(upc, quantity, warehouse));
    }
    else if(line.compare("Next") == 0)
    {
      // process request request_list before changing the next day
      for(vector<Request>::iterator it = requests.begin(); it < requests.end(); ++it)
      {
        process_request(it->upc, it->warehouse, it->quantity);
      }

      // Clear the request_list
      requests.clear();

      getline(data_file, line); // Finish off the line so we can continue reading lines

      // Want to move forward the date by 1 
      boost::gregorian::date_duration one_day(1);
  
      // Update date in all the warehouses and reset transactions. 
      // Also Remove expired or empty inventory from each warehouse
      for (map<string, Warehouse*>::iterator it = warehouses.begin(); it  != warehouses.end(); ++it)
      {
        // Update the date
        it->second->current_day = it->second->current_day + one_day;

        // Reset transactions
        it->second->reset_transactions();

        // Get index for each item that is empty or expired so we can remove
        vector<int> remove_indexes;
        int index_to_remove = 0;

        for(vector<Transaction>::iterator items_it = it->second->inventory.begin(); items_it < it->second->inventory.end(); ++items_it)
        {
          if(items_it->quantity == 0 || it->second->current_day == items_it->expire_date)
          {
            remove_indexes.push_back(index_to_remove);
          }
          index_to_remove++;
        }

        // remove each item in the index
        for(vector<int>::iterator remove_it = remove_indexes.begin(); remove_it < remove_indexes.end(); ++remove_it)
        {
          int index = *remove_it;
          it->second->inventory.erase(it->second->inventory.begin() + index);
        }
      }
    }

    boost::algorithm::trim(line);
    if(line.compare("End") == 0)
    {
      // process request request_list before one last time 
      for(vector<Request>::iterator it = requests.begin(); it < requests.end(); ++it)
      {
        process_request(it->upc, it->warehouse, it->quantity);
      }

      // Find all the non stocked items and fully stocked items between all the warehouses
      for (map<string, FoodItem>::iterator f_it = food_items.begin(); f_it != food_items.end(); ++f_it)
      {
        // Search in every warehouse inventory
        bool is_stocked = false;
        bool fully_stocked = true;

        for (map<string, Warehouse*>::iterator w_it = warehouses.begin(); w_it != warehouses.end(); ++w_it)
        {
          bool contains_inventory =  w_it->second->contains_inventory(f_it->second.upc);
          is_stocked = (is_stocked || contains_inventory); // If any warehouse contains the food item, this will be true
          fully_stocked = (fully_stocked && contains_inventory); // If any warehouse doesn't have the food item, this will be false
        }

        // Add to non stocked list
        if (!is_stocked)
        {
          non_stocked_items.push_back(f_it->second);
        }

        // Add to fully stocked list
        if (fully_stocked)
        {
          fully_stocked_items.push_back(f_it->second);
        }

      }

      // Start outputting report back to user
      cout << "Report by Zach Tolson\n" << endl;

      // Unstock data information
      cout << "Unstocked Products:" << endl;
      // Output Unstocked products data
      for(vector<FoodItem>::iterator it = non_stocked_items.begin(); it < non_stocked_items.end(); ++it)
      {
        cout << it->upc << " " << it->food_name << endl;
      }

      // Fully-stocked products information
      cout << "\nFully-Stocked Products:" << endl;
      // @TODO Get and Output Fully Stocked Data
      for(vector<FoodItem>::iterator it = fully_stocked_items.begin(); it < fully_stocked_items.end(); ++it)
      {
        cout << it->upc << " " << it->food_name << endl;
      }

      // Busiest days
      cout << "\nBusiest Days:" << endl;
      for (map<string, Warehouse*>::iterator it = warehouses.begin(); it  != warehouses.end(); ++it)
      {
        // Format the date
        string date = boost::gregorian::to_iso_extended_string(it->second->busiest_day);
        string year = date.substr(0, 4);
        string month = date.substr(5, 2);
        string day = date.substr(8, 2);
        string busiest_date_formatted = month + "/" + day + "/" + year;
        
        // Output the information
        cout << it->second->name << " " << busiest_date_formatted  <<  " " << it->second->busiest_day_transactions << endl;
      }

      // Free the Warehouse Objects
      for (map<string, Warehouse*>::iterator it = warehouses.begin(); it  != warehouses.end(); ++it)
      {
        Warehouse *w = it->second;
        free(w);
      }
      return 0;
    }

    if(data_file.fail())
    {
      cout << "Failed to read the file" << endl;
      return 0;
    }
  }

}
