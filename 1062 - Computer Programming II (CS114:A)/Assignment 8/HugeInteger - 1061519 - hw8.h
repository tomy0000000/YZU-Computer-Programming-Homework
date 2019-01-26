//
//  HugeInteger - 1061519 - hw8.h
//  Hw8
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/5/8.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef HUGEINTEGER___1061519___HW8_H
#define HUGEINTEGER___1061519___HW8_H

//#include <list>
//using std::list;

#include <iostream>
using std::ostream;

#include "List - 1061519 - hw8.h"

template <typename T>
class HugeInteger : public list<T> {
  template <typename Tf>
  friend ostream &operator<<(ostream &output, const HugeInteger<Tf> &hugeInteger);

public:
  HugeInteger() : list<T>(1) {}
  HugeInteger(const HugeInteger &integerToCopy) : list<T>(integerToCopy) {}
  ~HugeInteger() {}

  const HugeInteger &operator=(const HugeInteger &right);
  const HugeInteger &operator=(const list<T> &right);

  bool operator<(const HugeInteger &right) const;
  bool operator>(const HugeInteger &right) const;
  bool operator==(const HugeInteger &right) const;
  bool operator<=(const HugeInteger &right) const;
  bool operator>=(const HugeInteger &right) const;

  HugeInteger operator+(const HugeInteger &op2) const;
  HugeInteger operator-(const HugeInteger &op2) const;
  HugeInteger operator*(const HugeInteger &op2) const;
  HugeInteger operator/(const HugeInteger &op2) const;
  HugeInteger operator%(const HugeInteger &op2) const;

  HugeInteger &operator++();
  HugeInteger &operator--();
  HugeInteger operator++(int);
  HugeInteger operator--(int);

  bool isZero();

private:
  HugeInteger(unsigned int n) : list<T>((n > 0) ? n : 1) {}
  void divideByTen(); // divides a HugeInteger by 10
  void helpIncrement(); // increments a HugeInteger by 1
  void helpDecrement(); // decrements a HugeInteger by 1
};

//   #######
//   #       #    # #    #  ####  ##### #  ####  #    #  ####
//   #       #    # ##   # #    #   #   # #    # ##   # #
//   #####   #    # # #  # #        #   # #    # # #  #  ####
//   #       #    # #  # # #        #   # #    # #  # #      #
//   #       #    # #   ## #    #   #   # #    # #   ## #    #
//   #        ####  #    #  ####    #   #  ####  #    #  ####

template <typename T>
const HugeInteger<T> &HugeInteger<T>::operator=(const HugeInteger<T> &right) {
  if (&right != this) {
    list<T>::operator=(right);
  }
  return *this;
}

template <typename T>
const HugeInteger<T> &HugeInteger<T>::operator=(const list<T> &right) {
  if (&right != this) {
    list<T>::operator=(right);
  }
  return *this;
}

template <typename T>
bool HugeInteger<T>::operator<(const HugeInteger<T> &right) const {
  if (list<T>::size() != right.list<T>::size()) {
    return (list<T>::size() < right.list<T>::size());
  }
  typename list<T>::reverse_iterator it1 = list<T>::rbegin();
  typename list<T>::reverse_iterator it2 = right.list<T>::rbegin();
  for ( ; it1 != list<T>::rend(); it1++, it2++) {
    if (*it1 != *it2) {
      return (*it1 < *it2);
    }
  }
  return false;
}

template <typename T>
bool HugeInteger<T>::operator>(const HugeInteger<T> &right) const {
  return (right < *this);
}

template <typename T>
bool HugeInteger<T>::operator==(const HugeInteger<T> &right) const {
  if (list<T>::size() != right.list<T>::size()) {
    return false;
  }
  typename list<T>::reverse_iterator it1 = list<T>::rbegin();
  typename list<T>::reverse_iterator it2 = right.list<T>::rbegin();
  for ( ; it1 != list<T>::rend(); it1++, it2++) {
    if (*it1 != *it2) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool HugeInteger<T>::operator<=(const HugeInteger<T> &right) const {
  return (*this == right || *this < right);
}

template <typename T>
bool HugeInteger<T>::operator>=(const HugeInteger<T> &right) const {
  return (*this == right || *this > right);
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator+(const HugeInteger<T> &op2) const {
  unsigned int op1Size = list<T>::size();
  unsigned int op2Size = op2.list<T>::size();
  unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

  HugeInteger<T> sum(sumSize);
  typename list<T>::iterator it1 = list<T>::begin();
  typename list<T>::iterator it3 = sum.list<T>::begin();
  for (; it1 != list<T>::end(); ++it1, ++it3)
    *it3 = *it1;

  typename list<T>::iterator it2 = op2.begin();
  it3 = sum.begin();
  for (; it2 != op2.end(); ++it2, ++it3)
    *it3 += *it2;

  it3 = sum.begin();
  typename list<T>::iterator it4 = it3;
  for (++it4; it4 != sum.end(); ++it3, ++it4)
    if (*it3 > 9) {
      (*it3) -= 10;
      (*it4)++;
    }

  if (*it3 == 0) {
    sum.pop_back();
  }

  return sum;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator-(const HugeInteger<T> &op2) const {
  
  // Initializing
  HugeInteger<T> difference(list<T>::size());
  int TempFuture = 0, Cal, fsubtrahend;
  
  // Do Substraction
  typename list<T>::iterator it1 = list<T>::begin();
  typename list<T>::iterator it2 = op2.list<T>::begin();
  typename list<T>::iterator it3 = difference.list<T>::begin();
  bool subMeetEnd = false;
  for (; it1 != list<T>::end(); it1++, it2++, it3++) {
    if (it2 == op2.list<T>::end() && !subMeetEnd) {
      subMeetEnd = true;
    }
    fsubtrahend = (!subMeetEnd) ? *it2 : 0;
    Cal = *it1 - fsubtrahend + TempFuture;
    *it3 = (Cal >= 0) ? Cal : Cal + 10;
    TempFuture = (Cal >= 0) ? 0 : -1;
  }
  
  // Size Calibration
  while (*difference.list<T>::rbegin() == 0 && difference.list<T>::size() != 1) {
    difference.list<T>::pop_back();
  }
  
  return difference;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator*(const HugeInteger<T> &op2) const {
  
  // Initializing
  HugeInteger product(list<T>::size() + op2.list<T>::size() + 1);
  typename list<T>::iterator it = product.list<T>::begin();
  for (; it != product.list<T>::end(); it++) {
    *it = 0;
  }
  
  // Double-Loop Calculate Each Digits
  typename list<T>::iterator it1 = list<T>::begin();
  typename list<T>::iterator it3 = product.list<T>::begin();
  for (; it1 != list<T>::end(); it1++, it3++) {
    typename list<T>::iterator it2 = op2.list<T>::begin(), it3tmp = it3;
    for (; it2 != op2.list<T>::end(); it2++, it3++) {
      *it3 += (*it1) * (*it2);
    }
    it3=it3tmp;
  }
  
  // Carry-Onnnnnn
  it = product.list<T>::begin();
  for (; it != product.list<T>::end(); it++) {
    if (*it >= 10) {
      typename list<T>::iterator ittmp = it;
      ittmp++;
      *ittmp += *it / 10;
      *it %= 10;
    }
  }
  
  // Size Calibration
  while (*product.list<T>::rbegin() == 0 && product.list<T>::size() != 1) {
    product.list<T>::pop_back();
  }
  
  return product;
}

template <typename T>
HugeInteger<T> HugeInteger<T>::operator/(const HugeInteger<T> &op2) const {
  
  // Initializing Quotient & Remainder
  HugeInteger quotient(1);
  HugeInteger remainder(list<T>::size());
  typename list<T>::iterator it1 = list<T>::begin();
  typename list<T>::iterator it2 = remainder.list<T>::begin();
  for (; it1 != list<T>::end(); it1++, it2++) {
    *it2 = *it1;
  }
  
  // End Function if Dividend is Smaller
  if (*this < op2) {
    *quotient.list<T>::begin() = 0;
    return quotient;
  }
  
  // Set Default QuotientSize
  quotient.list<T>::resize(list<T>::size() - op2.list<T>::size());
  
  // Create Buffer
  HugeInteger buffer(list<T>::size());
  int Shift = list<T>::size() - op2.list<T>::size();
  it1 = op2.list<T>::begin();
  it2 = buffer.list<T>::begin();
  for (int it2cnt = 0; it2 != buffer.list<T>::end(); it1++, it2++, it2cnt++) {
    typename list<T>::iterator ittmp = it1;
    for (int i=0; i<Shift; i++) {
      ittmp--;
    }
    *it2 = (it2cnt >= Shift) ? *ittmp : 0;
  }
  
  // Buffer Calibration & Quotient Cleaning
  if (*this < buffer) {
    buffer.divideByTen();
  } else {
    quotient.list<T>::resize(quotient.list<T>::size() + 1);
  }
  it1 = quotient.list<T>::begin();
  for (; it1 != quotient.list<T>::end(); it1++) {
    *it1 = 0;
  }
  
  // Calculate Remainder One Unit at One Time
  typename list<T>::reverse_iterator rit1 = quotient.list<T>::rbegin();
  for (; rit1 != quotient.list<T>::rend(); rit1++) {
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
HugeInteger<T> HugeInteger<T>::operator%(const HugeInteger<T> &op2) const {
  HugeInteger quotient = (*this) / op2;
  HugeInteger timed = quotient * op2;
  HugeInteger remainder = (*this) - timed;
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

template <typename T>
bool HugeInteger<T>::isZero() {
  for (typename list<T>::iterator it = list<T>::begin(); it != list<T>::end(); ++it)
    if (*it != 0)
      return false;

  return true;
}

template <typename T>
void HugeInteger<T>::divideByTen() {
  typename list<T>::iterator it1 = list<T>::begin();
  typename list<T>::iterator it2 = it1;
  for (++it2; it2 != list<T>::end(); ++it1, ++it2)
    *it1 = *it2;
  list<T>::pop_back();
}

template <typename T>
void HugeInteger<T>::helpIncrement() {
  typename list<T>::iterator it = list<T>::begin();
  (*it)++;
  typename list<T>::iterator it2 = it;
  for (++it2; it2 != list<T>::end(); ++it, ++it2)
    if (*it == 10) {
      *it = 0;
      (*it2)++;
    }

  if ((*it) == 10) {
    *it = 0;
    list<T>::resize(list<T>::size() + 1);
    it = list<T>::end();
    --it;
    *it = 1;
  }
}

template <typename T>
void HugeInteger<T>::helpDecrement() {
  typename list<T>::iterator it = list<T>::begin();
  for (; *it == 0; ++it)
    *it = 9;

  (*it)--;
}

template <typename Tf>
ostream &operator<<(ostream &output, const HugeInteger<Tf> &hugeInteger) {
  typename list<Tf>::reverse_iterator it = hugeInteger.list<Tf>::rbegin();
  for (; it != hugeInteger.list<Tf>::rend(); ++it) {
    if (*it < 10) {
      output << *it;
    }
  }
  return output;
}

#endif
