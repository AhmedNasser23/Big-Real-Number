#include "BigReal.h"
#include <bits/stdc++.h>
using namespace std;

bool dot(char c) {
  return c == '.';
}

// Set_Num
void BigReal::set_num(string real) {

  // Check There Is (Dot) Or Not If There Isn't (Dot) Make Fraction Part = "0"
  int n = 0;
  n = count_if(real.begin(), real.end(), dot);
  if (n==0) real+=".0";

  // Check If The Real Isn't Valid
  if (isValid(real)) {

    // Make Sign = '+' If The First Char Isn't Equal '+' Or '-'
    if (real[0] != '+' && real[0] != '-') {
      sign = '+';
    }

    // Make Sign = '-' If The First Char Is '-' And Remove First Char
    if (real[0] == '-') {
      sign = '-';
      real.erase(real.begin());
    }

    // Make Sign = '+' If The First Char Is '+' And Remove First Char
    if (real[0] == '+') {
      sign = '+';
      real.erase(real.begin());
    }

    // Separate The Integer Part And Fraction Part
    integer = real.substr(0, real.find("."));
    fraction = real.substr(real.find(".") + 1, real.length() - 1);
  }

  bool test1 = false, test2 = false;
  int idx1 = 0, idx2 = 0;
  for (int i = 0; i < fraction.length(); i++) {
    if (fraction[i] != '0') {
      test1 = true;
      idx1 = i;
    }
  }

  // if find any char expect 0 will make it as it is
  if (test1) {
    fraction = fraction.substr(0, idx1 + 1);
  }

    // if didn't find any char expect 0 will make it "0" not "0000000"
  else {
    fraction = "0";
  }

  // check if all Integer part is zeors

  if (integer[0] == '0') {
    for (int k = 0; k < integer.length(); k++) {
      if (integer[k] != '0') {
        idx2 = k;
        test2 = true;
        break;
      }
    }
    // will make integer equal integer from the first number founed to the end
    if (test2) {
      integer = integer.substr(idx2, integer.length() - 1);
    }

    // if didn't find any number expect 0 will make it zero
    else {
      integer = "0";
    }
  }
}

// ------------------------------------------------------

// IsValid  Function

bool BigReal::isValid(string real){
  return (regex_match(real, regex("[+-]?\\d*.?\\d+")));
}

// ------------------------------------------------------

// Parameteraize Constructor
BigReal::BigReal(string real) {
  this->set_num(real);
}

// ---------------------------------------------------------------

// Default Constructor
BigReal::BigReal() {
  sign = '+';
  integer = "0";
  fraction = "0";
}

// ---------------------------------------------------------------

// Operator +
BigReal BigReal::operator+(BigReal &BR) {

  // Make An Object That Will Return At The End
  BigReal Result;

  // Make String For The Result For Fraction And Integer
  string Result_fraction = Result.fraction;
  string Result_integer  = Result.integer;

  Result_fraction = "";
  Result_integer = "";

  string fra_part_obj = fraction;   // Fraction Part For The Object That Call Operator+
  string fra_part_BR = BR.fraction;// Fraction Part For The Object That Will Be Passed For Operator+

  string int_part_obj = integer;   // Integer Part For The Object That Call Operator+
  string int_part_BR = BR.integer;// Integer Part For The Object That Will Be Passed For Operator+


  if (fra_part_BR.length() > fra_part_obj.length()) {

    // will make the two fraction parts with  the same length
    while (fra_part_obj.length() != fra_part_BR.length()) {
      fra_part_obj += "0";
    }
  }

  else if (fra_part_BR.length() < fra_part_obj.length()) {

    // will make the two fraction parts with the same length
    while (fra_part_obj.length() != fra_part_BR.length()) {
      fra_part_BR += "0";
    }
  }

  if (int_part_BR.length() > int_part_obj.length()) {

    // make the two integer parts with the same length
    while (int_part_obj.length() != int_part_BR.length()) {
      int_part_obj = "0" + int_part_obj;
    }
  } else if (int_part_BR.length() < int_part_obj.length()) {

    // will make two integer parts with the same length
    while (int_part_obj.length() != int_part_BR.length()) {
      int_part_BR = "0" + int_part_BR;
    }
  }

  char carry = '0';

  if (sign == '-' && BR.sign == '-') {
    Result.sign = '-';
  }

  else if (sign == '+' && BR.sign == '+') {
    Result.sign = '+';
  }

  else if (sign != BR.sign) {
    this->operator-(BR);
    Result.integer = this->operator-(BR).integer;
    Result.fraction = this->operator-(BR).fraction;
    return Result;
  }

  // loop for each char from end to begin
  for (int i = fra_part_obj.length() - 1; i >= 0; i--) {

    // check if the result bigger than or equal 10
    if (((fra_part_BR[i] - 48) + (fra_part_obj[i] - 48) + (carry - 48)) >= 10) {

      // store result at temporary string
      string num = to_string(((fra_part_BR[i] - 48) + (fra_part_obj[i] - 48) + (carry - 48)));

      // give the Result_fraction second part [0 1 2 3 4 5 6 7 8 9]
      Result_fraction += num[1];

      // make carry equal 1
      carry = '1';
    }

      // if the result less than 10
    else {
      Result_fraction += to_string(((fra_part_BR[i] - 48) + (fra_part_obj[i] - 48) + (carry - 48)));
      carry = '0';
    }
  }

  // then reverse the result because we add from the right not from the left
  reverse(Result_fraction.begin(), Result_fraction.end());

  // loop for each char from end to begin
  for (int i = int_part_obj.length() - 1; i >= 0; i--) {

    // check if the result greater than or eqaul 10
    if (((int_part_BR[i] - 48) + (int_part_obj[i] - 48) + (carry - 48)) >= 10) {

      // store result at temporary string
      string num = to_string(((int_part_BR[i] - 48) + (int_part_obj[i] - 48) + (carry - 48)));

      // give the Result_fraction second part [0 1 2 3 4 5 6 7 8 9]
      Result_integer += num[1];

      // make carry equal 1
      carry = '1';
    }

      //if the result less than 10
    else {
      Result_integer += to_string(((int_part_BR[i] - 48) + (int_part_obj[i] - 48) + (carry - 48)));
      carry = '0';
    }
  }
  // then reverse the result because we add from the right not from the left
  reverse(Result_integer.begin(), Result_integer.end());

  // check if there is carry at the end and add it to the result and make it equal 0
  if (carry == '1') {
    Result_integer = '1' + Result_integer;
    carry = '0';
  }

  // check if all fraction part is zeors

  bool test1 = false, test2 = false;
  int idx1 = 0, idx2 = 0;
  for (int i = 0; i < Result_fraction.length(); i++) {
    if (Result_fraction[i] != '0') {
      test1 = true;
      idx1 = i;
    }
  }

  // if find any char expect 0 will make it as it is
  if (test1) {
    Result.fraction = Result_fraction.substr(0, idx1 + 1);
  }

    // if didn't find any char expect 0 will make it "0" not "0000000"
  else {
    Result.fraction = "0";
  }

  // check if all Integer part is zeors

  if (Result_integer[0] == '0') {
    for (int k = 0; k < Result_integer.length(); k++) {
      if (Result_integer[k] != '0') {
        idx2 = k;
        test2 = true;
        break;
      }
    }
    // will make Result.integer equal Result_integer from the first number founed to the end
    if (test2) {
      Result.integer = Result_integer.substr(idx2, Result_integer.length() - 1);
    }

      // if didn't find any number expect 0 will make it zero
    else {
      Result.integer = "0";
    }
  }
  else {
    Result.integer = Result_integer;
  }
  return Result;
}


// ---------------------------------------------------------------

// Operator ==
bool BigReal::operator==(BigReal BR) {


  // if two number have different sign
  if (BR.sign != sign) {
    return false;
  }

  string int_part_obj = integer;    // integer part for the object that call operator==
  string int_part_BR  = BR.integer; // integer part for the object that will be passed to operator==


  string fra_part_obj = fraction;   // fraction part for the object that call operator==
  string fra_part_BR  = BR.fraction;// fraction part for the object that will be passed to operator==


  bool test1 = false, test2 = false, test3 = false, test4 = false;
  int idx1 = 0, idx2 = 0, idx3 = 0, idx4 = 0;

  // check if all numbers are equal for fraction part of object that call operator==
  for (int i = 0; i < fra_part_obj.length(); i++) {
    if (fra_part_obj[i] != '0') {
      test1 = true;
      idx1 = i;
    }
  }

  // if founded number expect 0 will make substring from 0 to this idx1+1
  if (test1) {
    fra_part_obj = fra_part_obj.substr(0, idx1+1);
  }

    // if didn't find number expect 0 will make it only "0"
  else {
    fra_part_obj = "0";
  }

  // ----------------------------------------------------------------------

  // check if all numbers are equal for fraction part of object that will be passed to the operator==
  for (int i = 0; i < fra_part_BR.length(); i++) {
    if (fra_part_BR[i] != '0') {
      test2 = true;
      idx2 = i;
    }
  }

  // if founded number expect 0 will make substring from 0 to this idx2+1
  if (test2) {
    fra_part_BR = fra_part_BR.substr(0, idx2+1);
  }

    // if didn't find number expect 0 will make it only "0"
  else {
    fra_part_BR = "0";
  }


  // ----------------------------------------------------------------------

  // check if all numbers are equal for integer part of object that call operator==
  for (int k = 0; k < int_part_obj.length(); k++) {
    if (int_part_obj[k] != '0') {
      idx3 = k;
      test3 = true;
      break;
    }
  }

  // if founded number expect 0 will make substring from this idx3 to the end
  if (test3) {
    int_part_obj = int_part_obj.substr(idx3, int_part_obj.length() - 1);
  }

    // if didn't find number expect 0 will make it only "0"
  else {
    int_part_obj = "0";
  }

  // ------------------------------------------------

  // check if all numbers are equal for integer part of object that will be passed to the operator==
  for (int k = 0; k < int_part_BR.length(); k++) {
    if (int_part_BR[k] != '0') {
      idx4 = k;
      test4 = true;
      break;
    }
  }

  // if founded number expect 0 will make substring from this idx4 to the end
  if (test4) {
    int_part_BR = int_part_BR.substr(idx4, int_part_BR.length() - 1);
  }

    // if didn't find number expect 0 will make it only "0"
  else {
    int_part_BR = "0";
  }

  // check if all parts are equal
  if (fra_part_BR == fra_part_obj && int_part_BR == int_part_obj) {
    return true;
  }

  else {
    return  false;
  }
}

// ------------------------------------------------------

// Size
int BigReal::siz() {
  return integer.length() + fraction.length() + 1;
}

// ------------------------------------------------------

// Sign
char BigReal::sig() {
  return sign;
}

// ------------------------------------------------------

// Friend function to overload the << operator
ostream& operator<<(ostream& os, const BigReal& BR) {

  // Output the sign
  os << (BR.sign == '-' ? "-" : "+");

  // Output the integer part
  os << BR.integer;

  os << "." << BR.fraction;

  return os;
}

// ------------------------------------------------------

// Operator >
bool BigReal::operator>(const BigReal& BR) {
  // The > operator is the inverse of the < operator
  return !(*this < BR) && !(*this == BR);
}

// ------------------------------------------------------

//Operator <
bool BigReal::operator<(const BigReal& BR) {
  // Check if the signs are different
  if (sign == '+' && BR.sign == '-') {
    return false;  // Positive numbers are greater than negative ones
  }
  if (sign == '-' && BR.sign == '+') {
    return true;  // Negative numbers are less than positive ones
  }

  string int_part_obj = integer;
  string int_part_BR = BR.integer;
  string fra_part_obj = fraction;
  string fra_part_BR = BR.fraction;

  // Remove leading zeros in the integer part
  int_part_obj.erase(0, int_part_obj.find_first_not_of('0'));
  int_part_BR.erase(0, int_part_BR.find_first_not_of('0'));

  // If the signs are the same, compare the integer parts
  if (sign == '+') {
    if (int_part_obj.length() < int_part_BR.length()) {
      return true;
    }
    if (int_part_obj.length() > int_part_BR.length()) {
      return false;
    }
    if (int_part_obj < int_part_BR) {
      return true;
    }
    if (int_part_obj > int_part_BR) {
      return false;
    }
  } else {
    if (int_part_obj.length() < int_part_BR.length()) {
      return false;
    }
    if (int_part_obj.length() > int_part_BR.length()) {
      return true;
    }
    if (int_part_obj < int_part_BR) {
      return false;
    }
    if (int_part_obj > int_part_BR) {
      return true;
    }
  }

  // If the integer parts are equal, compare the fraction parts
  int max_fraction_length = max(fra_part_obj.length(), fra_part_BR.length());
  fra_part_obj.resize(max_fraction_length, '0');
  fra_part_BR.resize(max_fraction_length, '0');

  if (fra_part_obj < fra_part_BR) {
    return true;
  }

  return false;
}

// ---------------------------------------------------------------


// Operator +
BigReal BigReal::operator-(BigReal &BR) {

  // Make an object that will return at the end
  BigReal Result;

  // Make string for the result for fraction and integer
  string Result_fraction = Result.fraction;
  string Result_integer  = Result.integer;

  Result_fraction = "";
  Result_integer  = "";

  string fra_part_obj = fraction;   // Fraction Part For The Object That Call Operator-
  string fra_part_BR  = BR.fraction;// Fraction Part For The Object That Will Be Passed For Operator-

  string int_part_obj = integer;   // Integer Part For The Object That Call Operator-
  string int_part_BR  = BR.integer;// Integer Part For The Object That Will Be Passed For Operator-


  if (fra_part_BR.length() > fra_part_obj.length()) {

    // will make the two fraction parts with  the same length
    while (fra_part_obj.length() != fra_part_BR.length()) {
      fra_part_obj += "0";
    }
  }

  else if (fra_part_BR.length() < fra_part_obj.length()) {

    // will make the two fraction parts with the same length
    while (fra_part_obj.length() != fra_part_BR.length()) {
      fra_part_BR += "0";
    }
  }

  if (int_part_BR.length() > int_part_obj.length()) {

    // make the two integer parts with the same length
    while (int_part_obj.length() != int_part_BR.length()) {
      int_part_obj = "0" + int_part_obj;
    }
  } else if (int_part_BR.length() < int_part_obj.length()) {

    // will make two integer parts with the same length
    while (int_part_obj.length() != int_part_BR.length()) {
      int_part_BR = "0" + int_part_BR;
    }
  }

  // will make result sign = (+) if int_part_obj > int_part_BR
  // else will make result sign = (-)
  if (this->sign == '+' && BR.sign == '+') {
    // the first int part of obj that call operator is greater than int part of (BR)
    if (int_part_obj >= int_part_BR && fra_part_obj >= fra_part_BR) {
      Result.sign = '+';
    }
    else {
      Result.sign = '-';
    }
  }

  // will call (+operator) -> x--y = x+y but will make sign for BR = (+)
  else if (this->sign == '+'  && BR.sign == '-') {
    BR.sign = '+';
    this->operator+(BR);
    Result.integer  = this->operator+(BR).integer;
    Result.fraction = this->operator+(BR).fraction;
    return Result;
  }

  // will call (+operator) -> (-x)-(+y) = -x-y but will make sign for BR = (-)
  else if (this->sign == '-' && BR.sign == '+') {
    BR.sign = '-';
    this->operator+(BR);
    Result.integer  = this->operator+(BR).integer;
    Result.fraction = this->operator+(BR).fraction;
    Result.sign  = '-';
    return Result;
  }

  // will make result sign = (-) if int_part_obj > int_part_BR
  // else will make result sign = (+)
  else if (this->sign == '-' && BR.sign == '-') {
    // the first int part of obj that call operator is greater than int part of (BR)
    if (int_part_obj >= int_part_BR && fra_part_obj >= fra_part_BR) {
      Result.sign = '-';
    }
    else {
      Result.sign = '+';
    }
  }

  // find the greater from two integer parts and the smaller
  string mx_int = max(int_part_BR, int_part_obj);
  string mn_int = min(int_part_BR, int_part_obj);

  // find the greater from two fraction parts and the smaller
  string mx_fra = max(fra_part_BR, fra_part_obj);
  string mn_fra = min(fra_part_BR, fra_part_obj);

  // will loop for two fraction parts
  for (int i = mx_fra.length() - 1; i >= 0; i--) {

    // if the result negative
    if (( (mx_fra[i] - 48) - (mn_fra[i] - 48) ) < 0 ) {

      // will borrow from the next degit
      Result_fraction += (to_string((mx_fra[i] - 48 + 10) - (mn_fra[i] - 48) ));
      mx_fra[i-1]--;
    }
    else {
      Result_fraction += (to_string((mx_fra[i] - 48) - (mn_fra[i] - 48) ));
    }
  }

  // will reverse because we add from the right
  reverse(Result_fraction.begin(), Result_fraction.end());

  // will loop for two integer parts
  for (int i = mx_int.length()-1; i>=0;i--) {

    // if the result negative
    if (( (mx_int[i] - 48) - (mn_int[i] - 48) ) < 0 ) {

      // will borrow from the next degit
      Result_integer += (to_string((mx_int[i] - 48 + 10) - (mn_int[i] - 48) ));
      mx_int[i-1]--;
    }
    else {
      Result_integer += (to_string((mx_int[i] - 48) - (mn_int[i] - 48) ));
    }
  }

  // will reverse because we add from the right
  reverse(Result_integer.begin(), Result_integer.end());


  // check if all fraction part is zeors
  bool test1 = false, test2 = false;
  int idx1 = 0, idx2 = 0;
  for (int i = 0; i < Result_fraction.length(); i++) {
    if (Result_fraction[i] != '0') {
      test1 = true;
      idx1 = i;
    }
  }

  // if find any char expect 0 will make it as it is
  if (test1) {
    Result.fraction = Result_fraction.substr(0, idx1 + 1);
  }

    // if didn't find any char expect 0 will make it "0" not "0000000"
  else {
    Result.fraction = "0";
  }

  // check if all Integer part is zeors
  if (Result_integer[0] == '0') {
    for (int k = 0; k < Result_integer.length(); k++) {
      if (Result_integer[k] != '0') {
        idx2 = k;
        test2 = true;
        break;
      }
    }
    // will make Result.integer equal Result_integer from the first number founed to the end
    if (test2) {
      Result.integer = Result_integer.substr(idx2, Result_integer.length() - 1);
    }

      // if didn't find any number expect 0 will make it zero
    else {
      Result.integer = "0";
    }
  }
  else {
    Result.integer = Result_integer;
  }
  return Result;
}

// ---------------------------------------------------------------

// Copy Constructor
BigReal::BigReal(const BigReal& other) {
  sign = other.sign;
  integer = other.integer;
  fraction = other.fraction;
}

// ---------------------------------------------------------------


// Assignment Operator
BigReal& BigReal::operator=(const BigReal& other) {
  if (this != &other) {  // Check for self-assignment
    sign = other.sign;
    integer = other.integer;
    fraction = other.fraction;
  }
  return *this;  // Return a reference to the modified object
}
