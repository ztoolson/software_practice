/*
 * This is a tester similar to the tester written in class.  It reads
 * words from a text file, then adds the words to two sets: A built-in
 * set class, and our lineset class.  After reading the file, it
 * prints out all the words stored in the STL set object.  At the end
 * of the test, it prints out the sizes of both sets to see that they
 * are the same.
 *
 * After the test completes, I make sure the local variables are properly
 * cleaned up.
 *
 * If the comments wrap lines, widen your emacs window.
 *
 * Peter Jensen
 * January 17, 2014
 */

#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include "lineset.h"
#include "node.h"

using namespace std;

// Note:  Our classes were declared in a cs3505 namepsace.
//        Instead of 'using namespace cs3505', I qualify our class names below with cs3505::

int main ()
{
  bool test_passed = true;

  if(test_passed)
  {
    cout << "Test 1: Test the capacity constructor and the add function. This was given in class" << endl;
    // Open up another block.  This way, when the block ends,

    // variables local to the block will be destroyed, but main
    // will still be running.  (Did you know that you can open
    // up a block at any time to control local variable scope and
    // lifetime?)

    {
      // Create the two sets.  Declaring the local variables constructs the objects.

      set<string>      stl_set_of_words;  // The built-in set class - no constructor parameters.

      cs3505::lineset  our_set_of_words(1000);  // Our set class, with a hashtable of 1000 slots.

      // Open the file stream for reading.  (We'll be able to use it just like
      //   the keyboard stream 'cin'.)

      ifstream in("Yankee.txt");

      // Loop for reading the file.  Note that it is controlled
      //   from within the loop (see the 'break').

      while (true)
      {
        // Read a word (don't worry about punctuation)

        string word;
        in >> word;

        // If the read failed, we're probably at end of file
        //   (or else the disk went bad).  Exit the loop.

        if (in.fail())
          break;

        // Word successfully read.  Add it to both sets.

        stl_set_of_words.insert(word);
        our_set_of_words.add(word);
      }

      // Close the file.

      in.close();
      // Check the number of items in each set
      test_passed = (stl_set_of_words.size() == our_set_of_words.size());
      if(!test_passed)
      {
        cout << "Error with size of the sets" <<  endl;
        cout << "Size of stl_set: " << stl_set_of_words.size() << endl;
        cout << "Size of our_set: " << our_set_of_words.size() << endl;
      }

      // Done.  Notice that this code block ends below.  Any local
      // variables declared within this block will be automatically
      // destroyed.  Local objects will have their destructors
      // called.

    }

    // Now that the objects have been destroyed, I will simply call my auditing
    // code to print out how many times constructors have been called, and
    // how many times destructors have been called.  They should exactly match.
    // If not, we have a memory problem.

    test_passed = (cs3505::lineset::constructor_count() == cs3505::lineset::destructor_count());
    if (!test_passed)
    {
      cout << "Error with lineset constructor and descructor count" << endl;
      cout << "constructor count: " << cs3505::lineset::constructor_count() << endl;
      cout << "destructor count: " << cs3505::lineset::destructor_count() << endl;
    }

    test_passed = (cs3505::node::constructor_count() == cs3505::node::destructor_count());
    if (!test_passed)
    {
      cout << "Error with node constructor and destructor count" << endl;
      cout << "constructor count: " << cs3505::node::constructor_count() << endl;
      cout << "destructor count: " << cs3505::node::destructor_count() << endl;
    }
  }

  // Test constructors
  if(test_passed)
  {
    cout << "Test2: Copy constructor" << endl;

    cs3505::lineset original_set(10);

    ifstream in("simple.txt");

    while(true)
    {
      // Read in a word (ignore punctuation
      string word;
      in >> word;

      // If the read failed, we are probably at the end of the file
      if(in.fail())
        break;

      // Add the word to the set
      original_set.add(word);
    }

    // Close the file
    in.close();

    // here is the test on the copy constructor
    cs3505::lineset copy_set(original_set);

    // Copy set should now have same elements as original set
    test_passed = (original_set.size() == copy_set.size()); 
    if(!test_passed)
    {
      cout << "Error with the copy constructor" << endl;
      cout << "Original set size: " << original_set.size() << endl;
      cout << "Copy set size: " << copy_set.size() << endl;
    }

  }

  // Test a basic valid use of remove
  if(test_passed)
  {
    cout << "Test3 Remove a basic word" << endl;
    cs3505::lineset  ls(1000);
  
    // Add word and then check size of line set
    std::string s = "test";
    ls.add(s);

    test_passed = (ls.size() == 1);
    if (!test_passed)
      cout << "Error adding item" << endl;

    // Remove and then recheck size of line set
    ls.remove("test");

    test_passed = (ls.size() == 0);
    if (!test_passed)
      cout << "Error removing the item" << endl;
  }
  
  // Test the contains method during normal use
  if(test_passed)
  {
    cout << "Test 4 Normal use. Test contains, add, remove" << endl;
    cs3505::lineset ls(1000);

    test_passed = (ls.size() == 0);
    if(!test_passed)
      cout << "Added an empty string to the set" << endl;

    ls.add("awesome");

    test_passed = (ls.contains("awesome"));
    if (!test_passed)
      cout << "Element added is not in the set" << endl; 
    test_passed = (!ls.contains("not_here_in_the_list_wow_this_is_long"));
    if (!test_passed)
      cout << "Says element is in list when it shouldn't be" << endl;

    // Remove the item and then check size and contains methods
    ls.remove("awesome");

    test_passed = (ls.size() == 0);
    if (!test_passed)
      cout << "Size is wrong after removing the item" << endl;

    test_passed = (!ls.contains("awesome"));
    if (!test_passed)
      cout << "After removing the item, contains returns the wrong value" << endl;
  }

  if(test_passed)
  {
    cout << "Test 5: Add same item twice" << endl;

    cs3505::lineset ls(1000);

    ls.add("one");
    ls.add("one");

    test_passed = (ls.size() == 1);
    if(!test_passed)
      cout << "Can't add same item twice" << endl;
  }

  if(test_passed)
  {
    cout << "Test6: Operator= method" << endl;

    cs3505::lineset copy(1000);
    int ls_size;
    {
      cs3505::lineset ls(1000);
      
      ifstream in("simple.txt");

      while(true)
      {
        // Read in a word (ignore punctuation
        string word;
        in >> word;

        // If the read failed, we are probably at the end of the file
        if(in.fail())
          break;

        // Add the word to the set
        ls.add(word);
      }

      // Close the file
      in.close();

      // Copy the lineset into copy
      copy = ls;

      // Save the size
      ls_size = ls.size();
    }

    test_passed = (copy.size() == ls_size);
    if(!test_passed)
      cout << "Error copying lineset when deleting the original" << endl;
  }


  if(test_passed)
  {
    cout << "test 7: get_elements" << endl;

    cs3505::lineset ls(1000);

    ifstream in("simple.txt");

    while(true)
    {
      // Read in a word (ignore punctuation
      string word;
      in >> word;

      // If the read failed, we are probably at the end of the file
      if(in.fail())
        break;

      // Add the word to the set
      ls.add(word);
    }

    // Close the file
    in.close();

    string *e = new string[ls.size()];
    ls.get_elements(e, 2);

    for (int i = 0; i < 2; i++)
      if (ls.contains(e[i]) == false)
          cout << "Error with get_elements returning elements not in lineset" << endl;
    delete [] e;
  }
  if(test_passed)
    cout << "Tests Passed" << endl;
  else
    cout << "Tests failed" << endl;

  return 0;
}
