#ifndef BIGREAL_H
#define BIGREAL_H

#include <string>
#include <regex>
using namespace std;

class BigReal {

private:
  char sign = '+';
  string integer, fraction;


public:
  bool isValid(string real);
  BigReal();
  BigReal(string real);
  BigReal (const BigReal& other);
  BigReal& operator=(const BigReal& other);
  void set_num(string real);
  int siz();
  char sig();
  BigReal operator+ (BigReal& BR);
  BigReal operator-(BigReal &BR);
  bool operator<(const BigReal& BR);
  bool operator> (const BigReal& BR);
  bool operator== (BigReal BR);
  friend ostream& operator<<(ostream& os, const BigReal& BR);
};

#endif // BIGREAL_H
