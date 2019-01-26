//
//  HugeInteger - 1061519 - hw7.h
//  Hw7
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/4/17.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef HUGEINTEGER___1061519___HW7_H
#define HUGEINTEGER___1061519___HW7_H

//#include <list>
//using std::list;
//#include <vector>
//using std::vector;

#include <iostream>
using std::ostream;

#include "List - 1061519 - hw7.h"
#include "Vector - 1061519 - hw7.h"

template <typename T> class HugeInteger {
  template <typename Tf>
  friend ostream &operator<<(ostream &output,
                             const HugeInteger<Tf> &hugeInteger);

public:
  HugeInteger(unsigned int n = 0) : integer((n == 0) ? 1 : n) {}
  HugeInteger(const HugeInteger &integerToCopy) : integer(integerToCopy.integer) {}
  ~HugeInteger() {}

  const HugeInteger &operator=(const HugeInteger &right);

  bool operator==(HugeInteger &right) { return (integer == right.integer); }
  bool operator<(HugeInteger &right);
  bool operator<=(HugeInteger &right) {
    return (*this == right || *this < right);
  }

  HugeInteger operator+(HugeInteger &op2);
  HugeInteger operator-(HugeInteger &op2);
  HugeInteger operator*(HugeInteger &op2);
  HugeInteger operator/(HugeInteger &op2);
  HugeInteger operator%(HugeInteger &op2);

  HugeInteger &operator++();   // prefix increment operator
  HugeInteger operator++(int); // postfix increment operator
  HugeInteger &operator--();   // prefix decrement operator
  HugeInteger operator--(int); // postfix decrement operator

  void convert(T &buffer);
  bool isZero();

private:
  T integer;
  void divideByTen();
  void helpIncrement();
  void helpDecrement();
};

template <typename T>
const HugeInteger<T> &HugeInteger<T>::operator=(const HugeInteger<T> &right) {
  if (&right != this) {
    integer = right.integer;
  }
  return *this;
}

template <typename T> bool HugeInteger<T>::operator<(HugeInteger<T> &right) {
  if (integer.size() != right.integer.size()) {
    return (integer.size() < right.integer.size());
  }
  typename T::reverse_iterator it1 = integer.rbegin();
  typename T::reverse_iterator it2 = right.integer.rbegin();
  for (; it1 != integer.rend(); it1++, it2++) {
    if (*it1 != *it2) {
      return (*it1 < *it2);
    }
  }
  return false;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator+(HugeInteger<T> &op2) {
  unsigned int op1Size = integer.size();
  unsigned int op2Size = op2.integer.size();
  unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

  HugeInteger<T> sum(sumSize);
  typename T::iterator it1 = integer.begin();
  typename T::iterator it3 = sum.integer.begin();
  for (; it1 != integer.end(); ++it1, ++it3)
    *it3 = *it1;

  typename T::iterator it2 = op2.integer.begin();
  it3 = sum.integer.begin();
  for (; it2 != op2.integer.end(); ++it2, ++it3)
    *it3 += *it2;

  it3 = sum.integer.begin();
  typename T::iterator it4 = it3;
  for (++it4; it4 != sum.integer.end(); ++it3, ++it4)
    if (*it3 > 9) {
      (*it3) -= 10;
      (*it4)++;
    }

  if (*it3 == 0)
    sum.integer.pop_back();

  return sum;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator-(HugeInteger<T> &op2) {

  // Initializing
  HugeInteger<T> difference(integer.size());
  int TempFuture = 0, Cal, fsubtrahend;

  // Do Substraction
  typename T::iterator it1 = integer.begin();
  typename T::iterator it2 = op2.integer.begin();
  typename T::iterator it3 = difference.integer.begin();
  bool subMeetEnd = false;
  for (; it1 != integer.end(); it1++, it2++, it3++) {
    if (it2 == op2.integer.end() && !subMeetEnd) {
      subMeetEnd = true;
    }
    fsubtrahend = (!subMeetEnd) ? *it2 : 0;
    Cal = *it1 - fsubtrahend + TempFuture;
    *it3 = (Cal >= 0) ? Cal : Cal + 10;
    TempFuture = (Cal >= 0) ? 0 : -1;
  }

  // Size Calibration
  while (*difference.integer.rbegin() == 0 && difference.integer.size() != 1) {
    difference.integer.pop_back();
  }

  return difference;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator*(HugeInteger<T> &op2) {

  // Initializing
  HugeInteger product(integer.size() + op2.integer.size() + 1);
  typename T::iterator it = product.integer.begin();
  for (; it != product.integer.end(); it++) {
    *it = 0;
  }
  
  // Double-Loop Calculate Each Digits
  typename T::iterator it1 = integer.begin();
  typename T::iterator it3 = product.integer.begin();
  for (; it1 != integer.end(); it1++, it3++) {
    typename T::iterator it2 = op2.integer.begin(), it3tmp = it3;
    for (; it2 != op2.integer.end(); it2++, it3++) {
      *it3 += (*it1) * (*it2);
    }
    it3=it3tmp;
  }

  // Carry-Onnnnnn
  it = product.integer.begin();
  for (; it != product.integer.end(); it++) {
    if (*it >= 10) {
      typename T::iterator ittmp = it;
      ittmp++;
      *ittmp += *it / 10;
      *it %= 10;
    }
  }

  // Size Calibration
  while (*product.integer.rbegin() == 0 && product.integer.size() != 1) {
    product.integer.pop_back();
  }

  return product;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator/(HugeInteger<T> &op2) {

  // Initializing Quotient & Remainder
  HugeInteger quotient(1);
  HugeInteger remainder(integer.size());
  typename T::iterator it1 = integer.begin();
  typename T::iterator it2 = remainder.integer.begin();
  for (; it1 != integer.end(); it1++, it2++) {
    *it2 = *it1;
  }

  // End Function if Dividend is Smaller
  if (*this < op2) {
    *quotient.integer.begin() = 0;
    return quotient;
  }

  // Set Default QuotientSize
  quotient.integer.resize(integer.size() - op2.integer.size());
  
  // Create Buffer
  HugeInteger buffer(integer.size());
  int Shift = integer.size() - op2.integer.size();
  it1 = op2.integer.begin();
  it2 = buffer.integer.begin();
  for (int it2cnt = 0; it2 != buffer.integer.end(); it1++, it2++, it2cnt++) {
    typename T::iterator ittmp = it1;
    for (int i=0; i<Shift; i++) {
      ittmp--;
    }
    *it2 = (it2cnt >= Shift) ? *ittmp : 0;
  }

  // Buffer Calibration & Quotient Cleaning
  if (*this < buffer) {
    buffer.divideByTen();
  } else {
    quotient.integer.resize(quotient.integer.size() + 1);
  }
  it1 = quotient.integer.begin();
  for (; it1 != quotient.integer.end(); it1++) {
    *it1 = 0;
  }

  // Calculate Remainder One Unit at One Time
  typename T::reverse_iterator rit1 = quotient.integer.rbegin();
  for (; rit1 != quotient.integer.rend(); rit1++) {
    while (buffer <= remainder) {
      remainder = remainder - buffer;
      (*rit1)++;
    }
    // Examine Remainder
    if (remainder.isZero()) {
      return quotient;
    }
    buffer.divideByTen();
  }

  return quotient;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator%(HugeInteger<T> &op2) {
  HugeInteger<T> quotient = (*this) / op2;
  HugeInteger<T> timed = quotient * op2;
  HugeInteger<T> remainder = (*this) - timed;
  //  HugeInteger remainder = (*this) - (quotient * op2);
  return remainder;
}

template <typename T> HugeInteger<T> &HugeInteger<T>::operator++() {
  helpIncrement();
  return *this;
}

template <typename T> HugeInteger<T> HugeInteger<T>::operator++(int) {
  HugeInteger<T> tmp(*this);
  helpIncrement();
  return tmp;
}

template <typename T> HugeInteger<T> &HugeInteger<T>::operator--() {
  helpDecrement();
  return *this;
}

template <typename T> HugeInteger<T> HugeInteger<T>::operator--(int) {
  HugeInteger<T> tmp(*this);
  helpDecrement();
  return tmp;
}

template <typename T> void HugeInteger<T>::convert(T &buffer) {
  integer.resize(buffer.size());
  typename T::reverse_iterator it1 = integer.rbegin();
  typename T::iterator it2 = buffer.begin();
  for (; it2 != buffer.end(); ++it1, ++it2)
    *it1 = *it2;
}

template <typename T> bool HugeInteger<T>::isZero() {
  for (typename T::iterator it = integer.begin(); it != integer.end(); ++it)
    if (*it != 0)
      return false;

  return true;
}

template <typename T> void HugeInteger<T>::divideByTen() {
  typename T::iterator it1 = integer.begin();
  typename T::iterator it2 = it1;
  for (++it2; it2 != integer.end(); ++it1, ++it2)
    *it1 = *it2;
  integer.pop_back();
}

template <typename T> void HugeInteger<T>::helpIncrement() {
  typename T::iterator it = integer.begin();
  (*it)++;
  typename T::iterator it2 = it;
  for (++it2; it2 != integer.end(); ++it, ++it2)
    if (*it == 10) {
      *it = 0;
      (*it2)++;
    }

  if ((*it) == 10) {
    *it = 0;
    integer.resize(integer.size() + 1);
    it = integer.end();
    --it;
    *it = 1;
  }
}

template <typename T> void HugeInteger<T>::helpDecrement() {
  typename T::iterator it = integer.begin();
  if (*it > 0) {
    (*it)--;
  } else {
    typename T::iterator it2 = it;
    it2++;
    while (*it2 == 0 && it2 != integer.end()) {
      *it2 = 9;
      it2++;
    }
    (*it2)--;
  }
}

template <typename T>
ostream &operator<<(ostream &output, const HugeInteger<T> &hugeInteger) {
  typename T::reverse_iterator it = hugeInteger.integer.rbegin();
  for (; it != hugeInteger.integer.rend(); ++it) {
    if (*it < 10) {
      output << *it;
    }
  }
  return output;
}

#endif
