//
//  Vector.h
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

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

  const VecIterator &operator=(const VecIterator &right) {
    if (&right != this) {
      ptr = right.ptr;
    }
    return *this;
  }

  // Operators
  bool operator==(const VecIterator &right) const { return ptr == right.ptr; }
  bool operator!=(const VecIterator &right) const { return ptr != right.ptr; }
  T &operator*() const { return *ptr; }
  T *operator->() const { return ptr; }

  VecIterator &operator++() {
    ++ptr;
    return *this;
  }

private:
  T *ptr = nullptr;
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
public:
  using iterator = VecIterator<T>;

  vector();
  vector(const vector &x) { *this = x; }
  ~vector();

  const vector &operator=(const vector &x);
  T &operator[](unsigned int n) { return *(myFirst + n); }
  const T &operator[](unsigned int n) const { return *(myFirst + n); }

  iterator begin() const { return iterator(myFirst); }
  iterator end() const { return iterator(myLast); }
  unsigned int size() const { return (myLast - myFirst); }
  unsigned int capacity() const { return (myEnd - myFirst); }

  void resize(unsigned int n);
  void push_back(const T val);

private:
  T *myFirst = nullptr;
  T *myLast = nullptr;
  T *myEnd = nullptr;
};

//   #######
//   #       #    # #    #  ####  ##### #  ####  #    #  ####
//   #       #    # ##   # #    #   #   # #    # ##   # #
//   #####   #    # # #  # #        #   # #    # # #  #  ####
//   #       #    # #  # # #        #   # #    # #  # #      #
//   #       #    # #   ## #    #   #   # #    # #   ## #    #
//   #        ####  #    #  ####    #   #  ####  #    #  ####

template <typename T>
vector<T>::vector() : myFirst(nullptr), myLast(nullptr), myEnd(nullptr) {}

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
    myFirst[i] = (i < orgSize) ? tempPtr[i] : T();
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

#endif
