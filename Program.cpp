#include "BigReal.h"
#include "BigReal.cpp"

#include <iostream>
using namespace std;

int main() {

  cout << "Enter The Operation You Want To Do:\na- Calculation\nb- Relation\n";
  char process; cin >> process;

  while (process != 'a' && process != 'b') {
    cout << "Invalid, Try Again: ", cin>> process;
  }

  // --------------------------------------------------

  if (process == 'a') {
    char op;
    cout << "What Is The Calcuation You Want To Do:\na- Addition\nb- Subtraction\n";
    cin >> op;
    while (op != 'a' && op != 'b') {
      cout << "Invalid, Try Again: "; cin >> op;
    }

    string r1, r2;
    BigReal B1, B2;

    cout << "Enter The First  Number: " , cin >> r1;
    while (!B1.isValid(r1)) {
      cout << "Invalid Number, Try Again: ", cin >> r1;
    }

    B1.set_num(r1);

    cout << "Enter The Second Number: " , cin >> r2;
    while (!B2.isValid(r2)) {
      cout << "Invalid Number, Try Again: ", cin >> r2;
    }

    B2.set_num(r2);

    if (op == 'a') {
      cout << "The Result Is: " << B1 + B2;
    }

    else if (op == 'b') {
      cout << "The Result Is: " << B1 - B2;
    }
  }

  // --------------------------------------------------

  else if (process == 'b') {

    string r1, r2;
    BigReal B1, B2;

    cout << "Enter The First  Number: " , cin >> r1;
    while (!B1.isValid(r1)) {
      cout << "Invalid Number, Try Again: ", cin >> r1;
    }

    B1.set_num(r1);

    char type_com;
    cout << "What Is The Type Of Relation Want To Do:\n-(>) Greater Than\n-(<) Less Than\n-(=) Equality\n";
    cin >> type_com;

    while (type_com != '>' && type_com != '<' && type_com != '=') {
      cout << "Invalid, Try Again: ", cin >> type_com;
    }


    cout << "Enter The Second Number: " , cin >> r2;
    while (!B2.isValid(r2)) {
      cout << "Invalid Number, Try Again: ", cin >> r2;
    }

    B2.set_num(r2);


    if (type_com == '>') {

      if (B1 > B2) {
        cout << "True, The First Number Is Bigger Than The Second Number";
      } else {
        cout << "False";
      }
    }

      else if (type_com == '<') {
        if (B1 < B2) {
          cout << "True, The First Number Is Less Than The Second Number";
        } else {
          cout << "False";
        }
      }

    else if (type_com == '=') {
      if (B1 == B2) {
        cout << "True, The First Number Is Equal To The Second Number";
      }
      else {
        cout << "False";
      }
    }
  }
}