/* A 'line set' is defined as a set of strings stored
 * in a hashtable that uses chaining to resolve collisions.
 *
 * Peter Jensen
 * January 17, 2014
 */

#include <iostream>
#include <string>
#include "lineset.h"
#include "node.h"

namespace cs3505
{
  /*******************************************************
   * lineset member function definitions
   ***************************************************** */


  /** Constructor:  The parameter indicates the
   *   size of the hashtable that should be used
   *   to keep this set.
   */
  lineset::lineset(int capacity)
  {
    // Do not change or remove the following line.
    //   It must execute for our auditing to be correct.

    lineset::constructor_calls++;

    // Normal constructor tasks below.

    this->capacity = capacity;
    this->count = 0;
    this->table = new node*[capacity];  // Create table (array of node pointers)

    // Make sure the table is clear.  (Not normally cleared on new.)

    for (int i = 0; i < capacity; i++)
      table[i] = NULL;
  }


  /** Copy constructor:  Initialize this set
   *   to contain exactly the same elements as
   *   another set.
   */
  lineset::lineset(const lineset & other)
  {
    // Do not change or remove the following line.
    //   It must execute for our auditing to be correct.

    lineset::constructor_calls++;

    // Normal constructor tasks below.

    // Initialize this object to appear cleaned.

    this->capacity = 0;
    this->count = 0;
    this->table = NULL;

    // Use our overloaded assignment operator to do the work
    //   of copying the parameter's elements into this object.

    *this = other;
  }


  /** Destructor:  release any memory allocated
   *   for this object.
   */
  lineset::~lineset()
  {
    // Do not change or remove the following line.
    //   It must execute for our auditing to be correct.

    lineset::destructor_calls++;

    // Normal destructor tasks below.

    clean();  // This does all the work.
  }


  /** Adds the specified element to this set.  If the element
   *   is already in this set, no action is taken.
   */
  void lineset::add (std::string element)
  {
    // This has been revised slightly from class.  If the
    //   element is not in the linked list (at the correct
    //   table position), I add it to the END of the linked
    //   list.  (I do this because you will use similar
    //   variables and looping in your remove method.)

    // Locate the table entry that would contain it.

    int index = hash(element);

    // Each table entry is the head of a linked list.
    //   Follow it, looking for the element.  Also,
    //   keep track of the last node visited.

    node *current = table[index], *last = NULL;

    while (current != NULL)
    {
      if (current->element == element)  // Does a char-by-char comparison
        return;  // Found it - do nothing - it's already in the set.
      last = current;           // Keep track of current as last visited node
      current = current->next;  // Advance to next node
    }

    // Element does not exist in the set.  Create a
    //   node object to contain it.  (New returns
    //   a pointer to it.)

    current = new node(element);

    // Add the node to our linked list.  Either
    //   add it to the end of the existing list,
    //   or start a new list.

    if (last == NULL)  // No existing list
      table[index] = current;  // The node becomes the head of a list
    else
      last->next = current;  // Add to end of existing list.

    // Keep track of the number of elements successfully added.

    count++;
  }


  /** Removes the specified element from this set.  If the
   *   element is not in the set, no action is taken.
   */
  void lineset::remove (std::string element)
  {
    // Requirement:  When an element is removed, its
    //   enclosing node must be unlinked from that
    //   linked list, and then the node must be deleted
    //   to free up its memory.  The linked list and/or
    //   table must be appropriately updated.

    // If item isn't in the set, don't bother attempting to remove
    if (!contains(element))
      return;
    // Locate the table entry that would contain it.

    int index = hash(element);

    // Each table entry is the head of a linked list.
    //   Follow it, looking for the element.

    node *current = table[index];  // Get the head of the list
    node *previous = NULL; // Saves the previous node 

    // Search the node* linked list for the element 
    while (current != NULL)
    {
      if (current->element == element)  // We found it!! Now time to remove... This does a char by char comparison
      {
        // Check if element is the first item in the node* list. If it is, set the table pointer to look at 
        // currents next element
        if (previous == NULL)
        {
          table[index] = current->next;
        }
        // Not the first item in the list. Update the previous items pointer to skip over current 
        // item before it is removed
        else
        {
          previous->next = current->next;
        }

        // Remove the item now that the pointers are updated. Also decrement the count
        delete current;
        count--;
        return;

      }
      // We did not find the element. Set previous node to the current and then update the
      // current node to the next one in the list
      previous = current;
      current = current->next;

    }
  }


  /** Returns true if the specified element in in this set,
   *   false otherwise.
   */
  bool lineset::contains (std::string element) const
  {
    // Locate the table entry that would contain it.

    int index = hash(element);

    // Each table entry is the head of a linked list.
    //   Follow it, looking for the element.

    node *current = table[index];  // Get the head of the list

    while (current != NULL)
    {
      if (current->element == element)  // Does a char-by-char comparison
        return true;  // Found it.

      current = current->next;  // Advance to next node
    }

    return false;  // Did not find it.
  }


  /** Returns a count of the number of elements
   *   in this set.
   */
  int lineset::size () const
  {
    return count;
  }

  /** This function populates an array of strings with elements from the set.
   * The caller passes an array (by pointer) and a count 'n' to the function.
   * The function copies n unique elements from the set into
   * the array.  (Order does not matter.)  If 'n' is smaller
   * than the number of elements in the set, only 'n' elements are
   * copied into the array in positions [0..n-1].  If 'n' is larger than the number
   * of elements in the set, all the elements in the set are
   * copied into the first positions of the array, and excess positions
   * in the array remain unchanged.
   *
   * It is assumed that the array reference is valid and that n is non-negative.
   */
  void lineset::get_elements(std::string *array, int n) const
  {
    // Make sure that n is not negative
    if (n < 0)
     throw "Cannot return a negative amount of elements"; 

    // Count the number of elements and return them when number_of_items
    // is equal to n
    int number_of_items = 0;

    // Go through the whole set. This is a for loop through all the
    // items in the array. In each item in the array, go through every item
    // unsing a while loop
    for (int i = 0; i < capacity; i++)
    {
      node * current = table[i];

      while (current != NULL)
      {
        // Add every element into the array passed as an arguement
        array[number_of_items] = current->element;

        // Move current to the next element
        current = current->next;

        // Update the number of items 
        ++number_of_items;

        // check if we have gotten n elements from our set
        if (number_of_items == n)
          return;
      }
    }
  }


  /*** assignment operator ***/

  /** this function overloads the assignment operator.  it
   *   clears out this set, builds an empty table, and copies
   *   the entries from the right hand side (rhs) set into
   *   this set.
   */
  const lineset & lineset::operator= (const lineset & rhs)
  {
    // if we are assigning this object to this object,
    //   do nothing.  (this is important!)

    if (this == &rhs)  // compare addresses (not object contents)
      return *this;  // Do nothing if identical

    // Wipe away anything that is stored in this object.

    clean();

    // Create a new set (new table) and populate it with the entries
    //   from the set in rhs.  Use the capacity from rhs.  Hint:
    //   see the first constructor above (but you cannot call it).

    // Requirement:  Do not permanently point to arrays or nodes in rhs.  
    //   When rhs is destroyed, it will delete its array and nodes, 
    //   and we cannot count on their existence.  Instead, you will
    //   create a new array for this object, traverse rhs,
    //   and add one entry to this set for every entry in rhs.
   
    // Get values from rhs and store them into this object
    this->capacity = rhs.capacity;
    this->count = 0;
    this->table = new node*[capacity];

    // Fill the table will NULL values
    for (int i = 0; i < capacity; i++)
      table[i] = NULL;

    // Get all the elements from the rhs
    std::string *rhs_elements = new std::string[rhs.size()];
    rhs.get_elements(rhs_elements, rhs.size());

    // Use the strings from the rhs to fill this set
    for (int j = 0; j < rhs.size(); j++)
      add(rhs_elements[j]);

    // Delete the *rhs_elements array
    delete [] rhs_elements;

    // Done with assignment.

    return *this;
  }


  /*** Private helper functions ***/

  /** Computes a table index for a given string.
   *   If two strings have the same contents, their
   *   hash code (table index) will be identical.
   * The hash code is guaranteed to be in the
   *   range [0..capacity).
   */  
  int lineset::hash (std::string s) const
  {
    // A well-known algorithm for computing string hash codes.
    // Students should not change this algorithm in any way.

    long long hash = 0;
    for (int i = 0; i < s.length(); i++)
      hash = ((hash * 1117) + s[i]) % capacity;

    return static_cast<int>(hash);
  }


  /** Releases any memory that was allocated by
   *   this object.  This effectively destroys the
   *   set, so it should only be called if this object
   *   is destructing, or is being assigned.
   */
  void lineset::clean ()
  {
    // If the object is already clean, do nothing.
    //   (Our representation for a clean object is that
    //   the table pointer is NULL).

    if (table == NULL)  
      return;

    // Delete all the nodes in the table.

    for (int i = 0; i < capacity; i++)
    {
      // Each entry in the table is the head of a linked list.
      // Follow the head to each node and delete the nodes.

      node *current = table[i];

      while (current != NULL)
      {
        // Keep a copy of the next pointer.

        node *temp_next = current->next;

        // Delete the node.  All its storage should be
        //   considered illegal.  (Afterwards, we cannot access
        //   ANYTHING inside of it, not even .next)

        delete current;

        // Advance to the next node.

        current = temp_next;	
      }      
    }

    // The nodes are all deleted.  Just delete the table.

    delete [] table;  // Notice the syntax for deleting an array.

    // We're done freeing up memory, but we should set
    //   our pointer to the array to NULL to indicate to
    //   ourself that it has been deleted.  (This also prevents
    //   us from accidentally using it.)

    table = NULL;

    // Done cleaning up.
  }


  /*******************************************************
   * lineset static definitions:
   *
   *     These are for debugging purposes only.  They help 
   * the programmer audit their memory usage.
   *
   *     Do not change anything below this point.
   ***************************************************** */

  // We haven't covered static class members.  Since static
  // variables are not in objects, we need to define storage
  // for them.  These variables are -here-, not in any object.
  // (This is the ONLY copy of these variables that will exist.)

  long long lineset::constructor_calls = 0;
  long long lineset::destructor_calls = 0;


  /** Returns the number of times any lineset
   *   constructor has been called.
   */
  long long lineset::constructor_count ()
  {
    return lineset::constructor_calls;
  }


  /** Returns the number of times the lineset
   *   destructor has been called.
   */
  long long lineset::destructor_count ()
  {
    return lineset::destructor_calls;
  }



}
