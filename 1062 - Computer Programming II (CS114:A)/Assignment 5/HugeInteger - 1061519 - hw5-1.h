//
//  HugeInteger - 1061519 - hw5-1.h
//  Hw5-1
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/3/27.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef HUGEINTEGER___1061519___HW5_1_H
#define HUGEINTEGER___1061519___HW5_1_H
#include "Vector - 1061519 - hw5.h"

template <typename T> class HugeInteger {

  template <typename Tf>
  friend ostream &operator<<(ostream &output, const HugeInteger<Tf> &hugeInteger);

public:
  
  // Constructors & Destructors
  HugeInteger();
  HugeInteger(const HugeInteger &integerToCopy);
  ~HugeInteger();

  // Overload Operators
  const HugeInteger &operator=(const HugeInteger &right);
  bool operator==(const HugeInteger &right) const;
  bool operator<(const HugeInteger &right) const;
  bool operator<=(const HugeInteger &right) const;

  // Calculation Functions
  HugeInteger operator+(const HugeInteger &op2) const;
  HugeInteger operator-(const HugeInteger &op2) const;
  HugeInteger operator*(const HugeInteger &op2) const;
  HugeInteger operator/(const HugeInteger &op2) const;
  HugeInteger operator%(const HugeInteger &op2) const;

  // prefix Operator
  HugeInteger &operator++();
  HugeInteger &operator--();
  // postfix Operator
  HugeInteger operator++(int);
  HugeInteger operator--(int);

  void convert(vector<T> v);
  bool isZero() const;

private:
  vector<T> integer;
  HugeInteger(unsigned int n);
  void divideByTen();
  void helpIncrement(); // increments a HugeInteger by 1
  void helpDecrement(); // decrements a HugeInteger by 1
};

template <typename T> HugeInteger<T>::HugeInteger() : integer(1) {}
template <typename T> HugeInteger<T>::HugeInteger(unsigned int n) : integer((n > 0) ? n : 1) {}
template <typename T> HugeInteger<T>::HugeInteger(const HugeInteger<T> &integerToCopy) : integer(integerToCopy.integer) {}
template <typename T> HugeInteger<T>::~HugeInteger() {}

template <typename T>
const HugeInteger<T> &HugeInteger<T>::operator=(const HugeInteger<T> &right) {
  if (&right != this) { // avoid self-assignment
    integer = right.integer;
  }
  return *this;
  // const return avoids: ( a1 = a2 ) = a3
  // enables x = y = z, for example
}

template <typename T>
bool HugeInteger<T>::operator==(const HugeInteger<T> &right) const {
  return (integer == right.integer);
}

template <typename T>
bool HugeInteger<T>::operator<(const HugeInteger<T> &right) const {
  if (integer.size() != right.integer.size()) {
    return (integer.size() < right.integer.size());
  }
  else {
    typename vector<T>::iterator it1 = integer.end() - 1;
    typename vector<T>::iterator it2 = right.integer.end() - 1;
    for ( ; it1 >= integer.begin(); it1--, it2--) {
      if (*it1 < *it2) {
        return true;
      }
      else if (*it1 > *it2) {
        return false;
      }
    }
  }
  return false;
}

template <typename T>
bool HugeInteger<T>::operator<=(const HugeInteger<T> &right) const {
  return (*this == right || *this < right);
}

template <typename T> HugeInteger<T> HugeInteger<T>::operator+(const HugeInteger<T> &op2) const {
  unsigned int op1Size = integer.size();
  unsigned int op2Size = op2.integer.size();
  unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

  HugeInteger sum(sumSize);

  typename vector<T>::iterator it1 = integer.begin();
  typename vector<T>::iterator it3 = sum.integer.begin();
  for (; it1 != integer.end(); ++it1, ++it3) {
    *it3 = *it1;
  }

  typename vector<T>::iterator it2 = op2.integer.begin();
  for (it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
    *it3 += *it2;

  for (it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3)
    if (*it3 > 9) {
      *it3 -= 10;
      (*(it3 + 1))++;
    }

  if (*it3 == 0)
    sum.integer.pop_back();

  return sum;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator-(const HugeInteger<T> &op2) const {
  
  //Initializing
  HugeInteger<T> difference(integer.size());
  int TempFuture = 0, Cal, fsubtrahend;
  
  //Do Substraction
  typename vector<T>::iterator it1 = integer.begin();
  typename vector<T>::iterator it2 = op2.integer.begin();
  typename vector<T>::iterator it3 = difference.integer.begin();
  for (; it1 != integer.end(); it1++, it2++, it3++) {
    fsubtrahend = (it2 < op2.integer.end()) ? *it2 : 0;
    Cal = *it1 - fsubtrahend + TempFuture;
    *it3 = (Cal >= 0) ? Cal : Cal + 10;
    TempFuture = (Cal >= 0) ? 0 : -1;
  }
  
  //Size Calibration
  while (*(difference.integer.end() - 1) == 0 && difference.integer.size() != 1) {
    difference.integer.pop_back();
  }
  
  return difference;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator*(const HugeInteger<T> &op2) const {
  
  //Initializing
  HugeInteger product(integer.size() + op2.integer.size() + 1);
  typename vector<T>::iterator it = product.integer.begin();
  for (; it != product.integer.end(); it++) {
    *it = 0;
  }
  
  //Double-Loop Calculate Each Digits
  typename vector<T>::iterator it1 = integer.begin();
  for (; it1 != integer.end(); it1++) {
    typename vector<T>::iterator it2 = op2.integer.begin();
    for (; it2 != op2.integer.end(); it2++) {
      typename vector<T>::iterator it3 = product.integer.begin();
      it3 += (it1 - integer.begin());
      it3 += (it2 - op2.integer.begin());
      *it3 += (*it1) * (*it2);
    }
  }
  
  //Carry-Onnnnnn
  it = product.integer.begin();
  for (; it < product.integer.end(); it++) {
    if (*it >= 10) {
      *(it + 1) += *it / 10;
      *it %= 10;
    }
  }
  
  //Size Calibration
  while (*(product.integer.end() - 1) == 0 && product.integer.size() != 1) {
    product.integer.pop_back();
  }
  
  return product;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator/(const HugeInteger<T> &op2) const {
  
  //Initializing Quotient & Remainder
  HugeInteger quotient(1);
  HugeInteger remainder(integer.size());
  typename vector<T>::iterator it1 = integer.begin();
  typename vector<T>::iterator it2 = remainder.integer.begin();
  for (; it1 != integer.end(); it1++, it2++) {
    *it2 = *it1;
  }
  
  //End Function if Dividend is Smaller
  if (*this < op2) {
    *quotient.integer.begin() = 0;
    return quotient;
  }
  
  //Set Default QuotientSize
  quotient.integer.resize(integer.size() - op2.integer.size());
  
  //Create Buffer
  HugeInteger buffer(integer.size());
  int Shift = integer.size() - op2.integer.size();
  it1 = op2.integer.begin();
  it2 = buffer.integer.begin();
  for ( ; it2 != buffer.integer.end(); it1++, it2++) {
    *it2 = (it2 - buffer.integer.begin() >= Shift) ? *(it1 - Shift) : 0;
  }
  
  //Buffer Calibration & Quotient Cleaning
  if (*this < buffer) {
    buffer.divideByTen();
  }
  else {
    quotient.integer.resize(quotient.integer.size() + 1);
  }
  it1 = quotient.integer.begin();
  for ( ; it1 != quotient.integer.end(); it1++) {
    *it1 = 0;
  }
  
  //Calculate Remainder One Unit at One Time
  it1 = quotient.integer.end() - 1;
  for ( ; it1 >= quotient.integer.begin(); it1--) {
    while (buffer <= remainder) {
      remainder = remainder - buffer;
      (*it1)++;
    }
    //Examine Remainder
    if (remainder.isZero()) {
      return quotient;
    }
    buffer.divideByTen();
  }
  
  return quotient;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator%(const HugeInteger<T> &op2) const {
  HugeInteger quotient = (*this) / op2;
  HugeInteger remainder = (*this) - (quotient * op2);
  return remainder;
}

template <typename T> HugeInteger<T>& HugeInteger<T>::operator++() {
  helpIncrement();
  return *this;
}

template <typename T> HugeInteger<T>& HugeInteger<T>::operator--() {
  helpDecrement();
  return *this;
}

template <typename T> HugeInteger<T> HugeInteger<T>::operator++(int) {
  HugeInteger<T> tmp(*this);
  helpIncrement();
  return tmp;
}

template <typename T> HugeInteger<T> HugeInteger<T>::operator--(int) {
  HugeInteger<T> tmp(*this);
  helpDecrement();
  return tmp;
}

template <typename T> void HugeInteger<T>::convert(vector<T> v) {
  integer.resize(v.size());
  typename vector<T>::iterator it1 = integer.end() - 1;
  typename vector<T>::iterator it2 = v.begin();
  for (; it2 != v.end(); --it1, ++it2)
    *it1 = *it2;
}

template <typename T> bool HugeInteger<T>::isZero() const {
  typename vector<T>::iterator it = integer.begin();
  for (; it != integer.end(); ++it)
    if (*it != 0)
      return false;

  return true;
}

template <typename T> void HugeInteger<T>::divideByTen() {
  typename vector<T>::iterator it = integer.begin() + 1;
  for (; it != integer.end(); ++it)
    *(it - 1) = *it;
  integer.pop_back();
}

template <typename T> void HugeInteger<T>::helpIncrement() {
  typename vector<T>::iterator it = integer.begin();
  (*it)++;
  typename vector<T>::iterator it2 = it;
  for (++it2; it2 != integer.end(); ++it, ++it2) {
    if (*it == 10) {
      *it = 0;
      (*it2)++;
    }
  }

  if ((*it) == 10) {
    *(it) = 0;
    integer.resize(integer.size() + 1);
    it = integer.end();
    --it;
    *it = 1;
  }
}

template <typename T> void HugeInteger<T>::helpDecrement() {
  typename vector<T>::iterator it = integer.begin();
  if (*it > 0) {
    (*it)--;
  } else {
    typename vector<T>::iterator it2 = it+1;
    while (*it2 == 0 && it2 != integer.end()) {
      *it2 = 9;
      it2++;
    }
    (*it2)--;
  }
}

template <typename T>
ostream &operator<<(ostream &output, const HugeInteger<T> &hugeInteger) {
  typename vector<T>::iterator it = hugeInteger.integer.end() - 1;
  for (; it != hugeInteger.integer.begin() - 1; --it)
    if (*it < 10)
      output << *it;

  return output; // enables cout << x << y;
}

#endif
