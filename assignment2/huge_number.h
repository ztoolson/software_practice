// Zach Toolson
// January 16, 2014
//
// huge_number class declaration that stored long integers as string.
// Operations that can be performed on huge_numbers are add, subtract,
// multiply, divide, equal, and mod.

#ifndef HUGE_NUMBER_H

#define HUGE_NUMBER_H

#include <string>

class huge_number
{
  private:
    // String variable to hold number representation
    std::string number;

    // Helper Methods
    std::string remove_leading_zeros(std::string str) const;
    bool is_bigger(std::string a, std::string b) const;
    bool is_equal(std::string a, std::string b) const;

    // Methods to perform operators
    std::string add(std::string a, std::string b) const;
    std::string subtract(std::string a, std::string b) const;
    std::string multiply(std::string a, std::string b) const;
    std::string divide(std::string a, std::string b) const;
    std::string mod(std::string a, std::string b) const;

  public:
    // Constructors
    huge_number(); // Default
    huge_number(const std::string str_num_representation); // String Input Constructor
    huge_number(const huge_number& hn_reference); // Copy Constructor

    // Destructor
    ~huge_number();

    // Accessor Method
    std::string get_value() const;

    // Operator Overloading Methods
    const huge_number operator = (const huge_number rhs);
    const huge_number operator + (const huge_number rhs) const;
    const huge_number operator - (const huge_number rhs) const;
    const huge_number operator * (const huge_number rhs) const;
    const huge_number operator / (const huge_number rhs) const;
    const huge_number operator % (const huge_number rhs) const;
};

#endif
