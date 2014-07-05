/* This node class is used to build linked lists for the
 * lineset class.
 *
 * Peter Jensen
 * January 17, 2014
 */

#ifndef NODE_H
#define NODE_H

#include<string>

namespace cs3505
{
  /* Node class for holding elements. */
  
  class node
  {
    friend class lineset;   // This allows functions in lineset to access
			    //   private data within this class.
    
  private:
    node(const std::string & element);  // Constructor
    ~node();                            // Destructor

    std::string element;  // Variable to hold the element
    node* next;           // Variable to point to the next node in the list

    
    // Below are a few definitions that I use to make sure I am cleaning
    //   up memory properly.  (Notice that I can switch back to public / private
    //   as many times as I like.)  These are not part of a normal
    //   node, but they are here because they help with debugging.
    // These functions and variables are declared static - they exist in the
    //   class, but not in any particular node object.  (The objects can access
    //   them, of course.)
    
  public:
    static long long constructor_count ();  // A debugging function for Peter
    static long long destructor_count ();   // A debugging function for Peter

  private:
    static long long constructor_calls;  // A debugging variable for Peter
    static long long destructor_calls;   // A debugging variable for Peter  
  };
}

#endif
