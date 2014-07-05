// Zach Toolson
// January 16, 2014
//
// huge_number class represents large integers that cannot be stored in
// int, or long data type in c++. Able to perform addition, subtraction,
// miltiplication, division, and mod between huge_numbers.

#include "huge_number.h"
#include <iostream>
#include <string>
#include <stdexcept>

/*
 * Default Constructor. Automatically set huge_number to 0
 */
huge_number::huge_number() 
{
  this->number = "0";
}

/*
 * Constructor that takes in a string and converts to huge_number
 *
 * Preconditions:
 *  No negative numbers
 *  String must only have digits E.G "123" is valid while "a543" is not valid
 */
 * 
huge_number::huge_number(const std::string s)
{
  this->number = remove_leading_zeros(s);
}

/*
 * Copy constructor that copies a huge_number input
 */
huge_number::huge_number(const huge_number & h)
{
  this->number = h.get_value();
}

/*
 * Destructor
 */
huge_number::~huge_number()
{
}

/*
 * Return the value of the huge number as a string
 */
std::string huge_number::get_value() const
{
  return number;
}

/*
 * Assignment operator. Allows the huge_number to copt another huge_number
 *
 * Example: huge_number z("12");
 *          huge_number x = z;
 *          huge_number z = x * y - x; // where x and y are huge_number class
 */
const huge_number huge_number:: operator = (const huge_number rhs)
{
  this->number = rhs.number;

  return *this;
}

/*
 * Overloads the + operator to allow <huge_number> + <huge_number> to be valid and perform
 * the addition operator on the two huge_number's.
 *
 * Example: huge_number x = a + b; // where a and b are huge_number
 */
const huge_number huge_number::operator + (const huge_number rhs) const
{
  std::string result = add(this->number, rhs.number);

  return huge_number(add(this->number, rhs.number));
}

/*
 * Overloads the - operator to allow <huge_number> - <huge_number> to be valid and perform
 * the subtraction operator on the two huge_number's.
 */
const huge_number huge_number::operator - (const huge_number rhs) const
{
  return huge_number(subtract(this->number, rhs.number));
}

/*
 * Overloads the * operator to allow <huge_number> * <huge_number> to be valid and perform
 * the multiplication operator on the two huge_number's.
 */
const huge_number huge_number::operator * (const huge_number rhs) const
{
  return huge_number(multiply(this->number, rhs.number));
}

/*
 * Overloads the / operator to allow <huge_number> / <huge_number> to be valid and perform
 * the division operator on the two huge_number's.
 */
const huge_number huge_number::operator/ (const huge_number rhs) const
{
  return huge_number(divide(this->number, rhs.number));
}

/*
 * Overloads the % operator to allow <huge_number> % <huge_number> to be valid and perform
 * the modulo operator on the two huge_number's.
 */

const huge_number huge_number::operator% (const huge_number rhs) const 
{
  return huge_number(mod(this->number, rhs.number));
}

/*
 * Private helper method that remove's all leading zero's from a huge_number.
 *
 * Example:
 *    huge_number z("00123");
 *    z = remove_leading_zeros(z);
 *    // z will then be 123 after the method call
 */
std::string huge_number::remove_leading_zeros(std::string str) const
{
  // Remove the leading zero's from str
  while(str.length() > 0 && str[0] == '0')
    str.erase(0, 1);

  // If there are no numbers left, the number is a zero
  if (str.length() == 0)
    str = "0";

  return str;
}

/*
 * Returns true is string a is bigger than string b.
 *
 * Precondition:
 *    a and b both are string representations of numbers
 */
bool huge_number::is_bigger(std::string a, std::string b) const
{
  // Just to be safe, remove the leading zeros from both inputs
  a = remove_leading_zeros(a);
  b = remove_leading_zeros(b);

  if (a.length() > b.length())
  {
    return true;
  }
  // Check all digits for equality
  else if(a.length() == b.length())
  {
    for (int i = 0; i < a.length(); i++)
    {
      if (a[i] != b[i])
        return a[i] > b[i];
    }
  }
  else
  {
    return false;
  }
}

/*
 * Returns a boolean is string a is equals to string b.
 *
 * Precondition:
 *    a and b are number representation stored in strings. 
 */
bool huge_number::is_equal(std::string a, std::string b) const
{
  // Remove leading zero's
  a = remove_leading_zeros(a);
  b = remove_leading_zeros(b);

  bool result = true;
  // Check if each element of both a and b are equal
  if (a.length() == b.length())
  {
    for (int i = 0; i < a.length(); i++)
    {
      if (a[i] != b[i])
        result = false;
    }
  }
  else
  {
    result = false;
  }

  return result;
}

/*
 * Adds two string representations of numbers and returns a string.
 *
 * Example: add("12", "20"); will return "32".
 */
std::string huge_number::add(std::string a, std::string b) const
{
  // Build up a string to contain the result
  std::string result = "";

  // Work from right to left
  int a_pos = a.length() - 1;
  int b_pos = b.length() - 1;
  int carry = 0;


  // Loop, adding columns from right to left until no digits remain
  while (a_pos >= 0 || b_pos >= 0 || carry > 0)
  {
    // Get the digit from each string, or 0 if no digits left to get
    // Note: this will decrement a_pos and b_pos after the end of the each while loop iteration
    int a_digit = a_pos >= 0 ? a[a_pos--] - '0' : 0;
    int b_digit = b_pos >= 0 ? b[b_pos--] - '0' : 0;

    // Calculate the digit sum
    int sum = a_digit + b_digit + carry;
    carry = sum / 10;
    sum = (sum % 10) + '0';

    // Put sum into the new string (at the left side)
    result.insert(0, 1, static_cast<char>(sum));
  }

  // Strip out any leading 0's from result
  result = remove_leading_zeros(result);

  return result;
}

/*
 * Subtracts two string representations of numbers and returns a string.
 *
 * Example:
 *    subtract("20", "5"); will return "15"
 */
std::string huge_number::subtract(std::string a, std::string b) const
{
  // Build up a string to hold the result
  std::string result = "";

  a = remove_leading_zeros(a);
  b = remove_leading_zeros(b);

  // If b is larger than a, the result will be negative.
  // This huge_number implementation does not deal with negative numbers,
  // return a "0" if this is the case
  if (is_bigger(b, a))
    return "0";

  // Work from right to left
  int a_pos = a.length() - 1;
  int b_pos = b.length() - 1;

  // At this point, we know that a is longer or the same length as b, and is larger
  // Work from right to left and perform subtraction on each digit
  while (a_pos >= 0)
  {
    // Get the value from the b column. If empty, the value is 0
    int b_digit = b_pos >= 0 ? b[b_pos] - '0' : 0;

    int diff = (a[a_pos] - '0') - b_digit;

    // Check if a borrow is needed
    if (diff < 0)
    {
      // Adjust the subtraction to account for borrow
      diff += 10;
      // Decrement for the borrow
      a[a_pos - 1] -= 1; 
    }

    // Turn back into ASCII number
    diff += '0'; 

    // Update the result
    result.insert(0, 1, static_cast<char>(diff));

    // Update column to subtract from
    a_pos--;
    b_pos--;
  }

  // Clear leading zeros on result
  result = remove_leading_zeros(result);

  return result;
}

/*
 * Multiplies two string representations of numbers and returns a string.
 *
 * Example:
 *    multiply("20", "5"); will return "100"
 */
std::string huge_number::multiply(std::string a, std::string b) const
{
  // Build up a string to contain the result
  std::string result = "0";
  
  // Position for b to perform multiplication. Work from left to right
  int b_pos = 0;

  while (b_pos < b.length())
  {
    // Multiply the result by 10, to perform result of proper column
    result.append("0");
    
    // Get the value of the b_digit. Also update position of b after while loops finishs iteration
    int b_digit = b[b_pos++] - '0';
    
    // Perform multiplication by addition for just the column. 
    for(int i = 0; i < b_digit; i++)
      result = add(result, a);
  }

  // String out and leading 0's from our result
  result = remove_leading_zeros(result);

  return result;
}

/*
 * Divides two string representations of numbers and returns a string.
 *
 * Note: This is integer division
 *
 * Example:
 *    divide("20", "5"); will return "4"
 */
std::string huge_number::divide (std::string a, std::string b) const
{
  // Remove leading zero's
  a = remove_leading_zeros(a);
  b = remove_leading_zeros(b);

  // Divide by zero is an illegal operation
  if (b == "0")
    throw std::runtime_error("Divide by zero exception");

  // String to contain result of division
  std::string result = "";

  // Variables used for division algorithm and smaller divisions that happen
  // through the long division process
  std::string divide_number = "";
  std::string remainder = "0";
  std::string quotient = "0";
  std::string sub_a = "";

  while(a.length() > 0)
  {
    // Get first digit from remaining numerator
    sub_a = a.substr(0, 1);

    // Erase the number we just got from a, to follow long division like in 
    // middle school
    a.erase(0, 1);

    divide_number = divide_number.append(sub_a);

    // Perform division with divide_number as numerator
    quotient = "0";
    remainder = divide_number;

    while(is_bigger(remainder, b) || remainder == b)
    {
      quotient = add(quotient, "1");
      remainder = subtract(remainder, b);
    }

    // Update result
    result.append(quotient);

    // Save the remainder for next iteration
    divide_number = remainder;
  }

  return remove_leading_zeros(result);
}

/*
 * Performs modulo operation on two string representations of numbers and returns a string.
 *
 * Example:
 *    divide("21", "5"); will return "1"
 */
std::string huge_number::mod(std::string a, std::string b) const
{
  // Remove leading zero's
  a = remove_leading_zeros(a);
  b = remove_leading_zeros(b);

  // Divide by zero is an illegal operation
  if (b == "0")
    throw std::runtime_error("Divide by zero exception");

  // String to contain result of division
  std::string result = "";

  // Variables used for division algorithm and smaller divisions that happen
  // through the long division process
  std::string divide_number = "";
  std::string remainder = "";
  std::string quotient = "";
  std::string sub_a = "";

  while(a.length() > 0)
  {
    // Get first digit from remaining numerator
    sub_a = a.substr(0, 1);

    // Erase the number we just got from a, to follow long division like in 
    // middle school
    a.erase(0, 1);

    divide_number = divide_number.append(sub_a);
    
    // Perform division with divide_number as numerator
    quotient = "0";
    remainder = divide_number;

    while(is_bigger(remainder, b) || remainder == b)
    {
      quotient = add(quotient, "1");
      remainder = subtract(remainder, b);
    }

    // Update result
    result.append(quotient);

    // Save the remainder for next iteration
    divide_number = remainder;
  }

  return remove_leading_zeros(remainder);
}
