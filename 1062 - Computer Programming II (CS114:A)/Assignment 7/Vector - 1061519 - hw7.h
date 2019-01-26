//
//  Vector - 1061519 - hw7.h
//  Hw7
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/4/17.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef VECTOR___1061519___HW7_H
#define VECTOR___1061519___HW7_H

//   ###
//    #  ##### ###### #####
//    #    #   #      #    #
//    #    #   #####  #    #
//    #    #   #      #####
//    #    #   #      #   #
//   ###   #   ###### #    #

template <typename T>
class VecIterator {
public:
  // Constructors & Destructors
  VecIterator(T *p = nullptr) : ptr(p) {}
  VecIterator(const VecIterator &iteratorToCopy) : ptr(iteratorToCopy.ptr) {}
  ~VecIterator() {}

  // const return avoids: ( a1 = a2 ) = a3
  const VecIterator &operator=(const VecIterator &right) {
    if (&right != this) // avoid self-assignment
      ptr = right.ptr;
    return *this; // enables x = y = z, for example
  }

  // Operators
  bool operator==(const VecIterator &right) const { return ptr == right.ptr; }
  bool operator!=(const VecIterator &right) const { return ptr != right.ptr; }
  T &operator*() const { return *ptr; }
  VecIterator &operator+=(const int &op2) { ptr += op2; }
  VecIterator &operator-=(const int &op2) { ptr -= op2; }
  VecIterator &operator++() {
    ++ptr;
    return *this;
  }
  VecIterator &operator--() {
    --ptr;
    return *this;
  }
  VecIterator operator++(int) {
    VecIterator tmp(*this);
    ptr++;
    return tmp;
  }
  VecIterator operator--(int) {
    VecIterator tmp(*this);
    ptr--;
    return tmp;
  }

private:
  T *ptr;
};

//   ######                   ###
//   #     # ###### #    #     #  ##### ###### #####
//   #     # #      #    #     #    #   #      #    #
//   ######  #####  #    #     #    #   #####  #    #
//   #   #   #      #    #     #    #   #      #####
//   #    #  #       #  #      #    #   #      #   #
//   #     # ######   ##      ###   #   ###### #    #

template <typename T>
class ReverseVecIterator {
public:
  // Constructors & Destructors
  ReverseVecIterator(T *p = nullptr) : ptr(p) {}
  ReverseVecIterator(const ReverseVecIterator &iteratorToCopy)
      : ptr(iteratorToCopy.ptr) {}
  ~ReverseVecIterator() {}

  // Operators
  bool operator==(const ReverseVecIterator &right) const {
    return ptr == right.ptr;
  }
  bool operator!=(const ReverseVecIterator &right) const {
    return ptr != right.ptr;
  }
  T &operator*() const { return *ptr; }
  ReverseVecIterator &operator++() {
    --ptr;
    return *this;
  }
  ReverseVecIterator &operator--() {
    ++ptr;
    return *this;
  }
  ReverseVecIterator operator++(int) {
    ReverseVecIterator tmp(*this);
    ptr--;
    return tmp;
  }
  ReverseVecIterator operator--(int) {
    ReverseVecIterator tmp(*this);
    ptr++;
    return tmp;
  }
  const ReverseVecIterator &operator=(const ReverseVecIterator &right) {
    if (&right != this) {
      ptr = right.ptr;
    }
    return *this;
  }

private:
  T *ptr;
};

//   #     #
//   #     # ######  ####  #####  ####  #####
//   #     # #      #    #   #   #    # #    #
//   #     # #####  #        #   #    # #    #
//    #   #  #      #        #   #    # #####
//     # #   #      #    #   #   #    # #   #
//      #    ######  ####    #    ####  #    #

template <typename T>
class vector {
  template <typename Tf>
  friend bool operator==(const vector<Tf> &lhs, const vector<Tf> &rhs);

  template <typename Tf>
  friend bool operator!=(const vector<Tf> &lhs, const vector<Tf> &rhs);

public:
  using iterator = VecIterator<T>;
  using reverse_iterator = ReverseVecIterator<T>;

  vector(unsigned int n = 0);
  vector(const vector &x);
  ~vector(); // Destroys the vector.

  const vector &operator=(const vector &x); // assignment operator

  iterator begin() const { return iterator(myFirst); }
  iterator end() const { return iterator(myLast); }
  reverse_iterator rbegin() const { return reverse_iterator(myLast - 1); }
  reverse_iterator rend() const { return reverse_iterator(myFirst - 1); }

  unsigned int size() const { return (myLast - myFirst); }
  unsigned int capacity() const { return (myEnd - myFirst); }
  void resize(unsigned int n);
  void push_back(const T val);
  void pop_back();

private:
  T *myFirst = nullptr;
  T *myLast = nullptr;
  T *myEnd = nullptr;
};

template <typename T>
vector<T>::vector(unsigned int n)
    : myFirst(n == 0 ? nullptr : new T[n]()),
      myLast(n == 0 ? nullptr : myFirst + n), myEnd(n == 0 ? nullptr : myLast) {
}

template <typename T>
vector<T>::vector(const vector<T> &x) {
  *this = x;
}

template <typename T>
vector<T>::~vector() {
  if (myFirst != nullptr) {
    delete[] myFirst;
  }
}

template <typename T>
const vector<T> &vector<T>::operator=(const vector<T> &x) {
  if (myFirst != nullptr) {
    delete[] myFirst;
  }
  myFirst = (x.myFirst == nullptr) ? nullptr : new T[x.size()]();
  myLast = (x.myLast == nullptr) ? nullptr : myFirst + x.size();
  myEnd = (x.myEnd == nullptr) ? nullptr : myLast;
  iterator it1 = begin();
  iterator it2 = x.begin();
  for (; it1 != end(); it1++, it2++) {
    *it1 = *it2;
  }
  return *this;
}

template <typename T>
void vector<T>::resize(unsigned int n) {
#if defined(__GNUC__) || defined(__GNUG__) // GNU GCC/G++
  const float COMPILER_GROWTH_FECTOR = 2;
#elif defined(_MSC_VER) // Microsoft Visual Studio
  const float COMPILER_GROWTH_FECTOR = 1.5;
#endif
  T *tempPtr = myFirst;
  int orgSize = size();
  int newCap = (n <= capacity()) ? capacity()
                                 : (n <= capacity() * COMPILER_GROWTH_FECTOR)
                                       ? capacity() * COMPILER_GROWTH_FECTOR
                                       : n;
  myFirst = new T[newCap]();
  for (int i = 0; i < newCap; i++) {
    myFirst[i] = (i < orgSize) ? tempPtr[i] : 0;
  }
  if (orgSize != 0) {
    delete[] tempPtr;
  }
  myLast = myFirst + n;
  myEnd = myFirst + newCap;
}

template <typename T>
void vector<T>::push_back(const T val) {
  resize(size() + 1);
  myFirst[size() - 1] = val;
}

template <typename T>
void vector<T>::pop_back() {
  if (size() > 0) {
    myLast--;
    *myLast = T();
  }
}

template <typename T>
bool operator==(const vector<T> &lhs, const vector<T> &rhs) {
  if (lhs.size() != rhs.size()) {
    return false;
  }
  typename vector<T>::iterator it1 = lhs.begin();
  typename vector<T>::iterator it2 = rhs.begin();
  for (; it1 != lhs.end() && it2 != rhs.end(); it1++, it2++) {
    if (*it1 != *it2) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool operator!=(const vector<T> &lhs, const vector<T> &rhs) {
  return !(lhs == rhs);
}

#endif
