//
//  main.cpp
//  Midterm 2
//  Huge Integer Division with Struct and Dynamic Memory Allocation
//
//  Created by Tomy Hsieh on 2017/12/3.
//  Copyright © 2017年 Tomy Creative Studio. All rights reserved.
//
//  Code remains unchanged comparing to submitted version.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ios;
using std::ofstream;

// HugeInteger class definition
class HugeInteger {
public:
  // enable user to input a positive huge integer
  void input(istream &inFile);

  // output the specified huge integer
  void output(ostream &outFile);

  // return true if and only if all digits are zero
  bool isZero();

  // return true if and only if current object == hugeInt2
  bool equal(HugeInteger &hugeInt2);

  // arrayEqual is a recursive function
  // return true if and only if elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last
  // ]
  bool arrayEqual(HugeInteger &hugeInt2, unsigned int last);

  // return true if and only if current object < hugeInt2
  bool less(HugeInteger &hugeInt2);

  // arrayLess is a recursive function
  // return true if and only if elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
  bool arrayLess(HugeInteger &hugeInt2, unsigned int last);

  // request the current object to reduce its array to fit its size
  void shrink_to_fit();

  // sum = current object + adder
  void addition(HugeInteger &adder, HugeInteger &sum);

  // current object -= subtrahend
  // provided that the current object is greater than or equal to the subtrahend
  void subtraction(HugeInteger &subtrahend);

  // quotient = current object / divisor; remainder = current object % divisor
  // provided that the divisor is not equal to 0
  void division(HugeInteger &divisor, HugeInteger &quotient,
                HugeInteger &remainder);

  // current object /= 10
  void divideByTen();

  void reset();

  unsigned int size =
      1; // the number of digits of the integer; it can never be zero
  int *elems = new int[1](); // used to store a nonnegative integer, one digit
                             // per element
};                           // end class HugeInteger

// enable user to input a positive huge integer
void HugeInteger::input(istream &inFile) {
  char numericString[200];

  inFile >> numericString;

  size = strlen(numericString);
  if (size > 0) {
    delete[] elems;
    elems = new int[size];
    for (unsigned int i = 0; i < size; i++)
      elems[size - i - 1] = numericString[i] - '0';
  }
} // end function input

// output the specified huge integer
void HugeInteger::output(ostream &outFile) {
  if (isZero())
    outFile << 0;
  else
    for (int i = size - 1; i >= 0; i--)
      if (elems[i] < 10)
        outFile << elems[i];
  outFile << endl;
} // end function output

// test if a HugeInteger is zero
bool HugeInteger::isZero() {
  if (size == 1 && elems[0] == 0)
    return true;
  return false;
} // end function isZero

// test if two HugeIntegers are equal
bool HugeInteger::equal(HugeInteger &hugeInt2) {
  if (isZero() && hugeInt2.isZero())
    return true;

  if (size != hugeInt2.size)
    return false;

  return arrayEqual(hugeInt2, size - 1);
} // end function equal

// arrayEqual is a recursive function
// return true if and only if elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
bool HugeInteger::arrayEqual(HugeInteger &hugeInt2, unsigned int last) {

  if (elems[last] != hugeInt2.elems[last]) {
    return false;
  }
  if (last == 0) {
    return true;
  }
  return arrayEqual(hugeInt2, last - 1);
}

// test if one HugeInteger is less than another
bool HugeInteger::less(HugeInteger &hugeInt2) {
  if (isZero() && hugeInt2.isZero())
    return false;

  if (isZero())
    return true;

  if (hugeInt2.isZero())
    return false;

  if (size < hugeInt2.size)
    return true;
  if (size > hugeInt2.size)
    return false;

  return arrayLess(hugeInt2, size - 1);
} // end function less

// arrayLess is a recursive function
// return true if and only if elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
bool HugeInteger::arrayLess(HugeInteger &hugeInt2, unsigned int last) {

  if (elems[last] < hugeInt2.elems[last]) {
    return true;
  }
  if (elems[last] > hugeInt2.elems[last]) {
    return false;
  }
  if (last == 0) {
    return false;
  }
  return arrayLess(hugeInt2, last - 1);
}

// request the current object to reduce its array to fit its size
void HugeInteger::shrink_to_fit() {
  int *buffer = new int[size];
  for (unsigned int i = 0; i < size; i++)
    buffer[i] = elems[i];
  delete[] elems;
  elems = buffer;
}

// sum = current object + adder
void HugeInteger::addition(HugeInteger &adder, HugeInteger &sum) {
  sum.size = (size >= adder.size) ? size + 1 : adder.size + 1;
  delete[] sum.elems;
  sum.elems = new int[sum.size]();

  for (unsigned int i = 0; i < size; i++)
    sum.elems[i] = elems[i];

  for (unsigned int i = 0; i < adder.size; i++)
    sum.elems[i] += adder.elems[i];

  for (unsigned int i = 0; i < sum.size - 1; i++)
    if (sum.elems[i] > 9) // determine whether to carry a 1
    {
      sum.elems[i] -= 10; // reduce to 0-9
      sum.elems[i + 1]++;
    }

  if (sum.elems[sum.size - 1] == 0) {
    sum.size--;
    sum.shrink_to_fit();
  }
} // end function addition

// current object -= subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void HugeInteger::subtraction(HugeInteger &subtrahend) {
  if (equal(subtrahend)) {
    reset();
    return;
  }
  int Cal = 0;
  int Car = 0;
  int fsubstrahend = 0;
  for (int i = 0; i < size; i++) {
    fsubstrahend = (i >= subtrahend.size) ? 0 : subtrahend.elems[i];
    Cal = elems[i] - fsubstrahend + Car;
    Car = (Cal < 0) ? -1 : 0;
    elems[i] = (Cal < 0) ? Cal + 10 : Cal;
  }
  for (int i = size - 1; i >= 0; i--) {
    if (elems[i] == 0) {
      size--;
    }
    if (elems[i] != 0) {
      break;
    }
  }
  shrink_to_fit();
} // end function subtraction

// quotient = current object / divisor; remainder = current object % divisor
// provided that the divisor is not equal to 0
void HugeInteger::division(HugeInteger &divisor, HugeInteger &quotient,
                           HugeInteger &remainder) {
  if (isZero()) {
    quotient.reset();
    remainder.reset();
    return;
  }

  if (less(divisor)) {
    quotient.reset();
    remainder.size = size;
    delete[] remainder.elems;
    remainder.elems = new int[remainder.size];
    for (unsigned int i = 0; i < size; i++) {
      remainder.elems[i] = elems[i];
    }
    return;
  }

  int n = size - divisor.size;
  HugeInteger buffer;
  buffer.size = size;
  buffer.elems = new int[buffer.size];
  for (int i = 0; i < size; i++) {
    buffer.elems[i] = (i < n) ? 0 : divisor.elems[i - n];
  }
  quotient.size = n;
  if (less(buffer)) {
    buffer.divideByTen();
  } else {
    quotient.size++;
  }
  delete[] quotient.elems;
  quotient.elems = new int[quotient.size]();
  // std::fill_n(quotient.elems, quotient.size, 0);
  remainder.size = size;
  delete[] remainder.elems;
  remainder.elems = new int[remainder.size];
  for (unsigned int i = 0; i < size; i++) {
    remainder.elems[i] = elems[i];
  }

  for (int k = quotient.size - 1; k >= 0; k--) {
    while (buffer.equal(remainder) || buffer.less(remainder)) {
      remainder.subtraction(buffer);
      quotient.elems[k]++;
      if (remainder.isZero()) {
        delete[] buffer.elems;
        return;
      }
    }
    buffer.divideByTen();
    remainder.shrink_to_fit();
  }
  delete[] buffer.elems;
} // end function division

// current object /= 10
void HugeInteger::divideByTen() {
  if (size == 1)
    elems[0] = 0;
  else {
    for (unsigned int i = 1; i < size; i++)
      elems[i - 1] = elems[i];
    elems[size - 1] = 0;
    size--;
    shrink_to_fit();
  }
} // end function divideByTen

void HugeInteger::reset() {
  size = 1;
  delete[] elems;
  elems = new int[1]();
}

void perform(ostream &outFile, HugeInteger &hugeInt1, HugeInteger &hugeInt2,
             HugeInteger &hugeInt3, HugeInteger &hugeInt4) {
  hugeInt1.output(outFile);
  hugeInt2.output(outFile);

  if (hugeInt2.isZero()) {
    outFile << "DivideByZero!\n";
    outFile << "DivideByZero!\n";
  } else {
    // hugeInt3 = hugeInt1 / hugeInt2; // hugeInt4 = hugeInt1 % hugeInt2
    hugeInt1.division(hugeInt2, hugeInt3, hugeInt4);
    hugeInt3.output(outFile);
    hugeInt4.output(outFile);
    hugeInt3.reset();
    hugeInt4.reset();
  }

  outFile << endl;
}

int main() {
  system("mode con cols=72");

  ifstream inFile("Test cases.txt", ios::in);

  // exit program if ifstream could not open file
  if (!inFile) {
    cout << "File could not be opened" << endl;
    system("pause");
    exit(1);
  }

  ofstream outFile("Result.txt", ios::out);

  // exit program if ofstream could not open file
  if (!outFile) {
    cout << "File could not be opened" << endl;
    system("pause");
    exit(1);
  }

  HugeInteger hugeInt1;
  HugeInteger hugeInt2;
  HugeInteger hugeInt3;
  HugeInteger hugeInt4;

  for (int i = 0; i < 22; i++) {
    hugeInt1.input(inFile);
    hugeInt2.input(inFile);
    perform(cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
    perform(outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4);
    hugeInt1.reset();
    hugeInt2.reset();
  }

  delete[] hugeInt1.elems;
  delete[] hugeInt2.elems;
  delete[] hugeInt3.elems;
  delete[] hugeInt4.elems;

  inFile.close();
  outFile.close();

  system("pause");
}