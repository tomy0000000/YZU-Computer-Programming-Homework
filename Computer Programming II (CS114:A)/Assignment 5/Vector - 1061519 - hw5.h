//
//  Vector - 1061519 - hw5.h
//  Hw5
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/3/27.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef VECTOR___1061519___HW5_H
#define VECTOR___1061519___HW5_H

template <typename T> class vector {
  template <typename Tf> friend bool operator==(const vector<Tf> &lhs, const vector<Tf> &rhs);
  template <typename Tf> friend bool operator!=(const vector<Tf> &lhs, const vector<Tf> &rhs);

public:
  using iterator = T*;
  
  // Constructors & Destructors
  vector(unsigned int n = 0);
  vector(const vector &x);
  ~vector();

  // Assignment Operator
  const vector &operator=(const vector &x);

  // Pointers & Attributes
  iterator begin() const;
  iterator end() const;
  unsigned int size() const;
  unsigned int capacity() const;
  
  // Some Gears
  void push_back(const T val);
  void pop_back();
  void resize(unsigned int n);

private:
  T *myFirst = nullptr;
  T *myLast = nullptr;
  T *myEnd = nullptr;
};

template <typename T> vector<T>::vector(unsigned int n)
    : myFirst(n == 0 ? nullptr : new T[n]()),
      myLast(n == 0 ? nullptr : myFirst + n), myEnd(n == 0 ? nullptr : myLast) {}

template <typename T> vector<T>::vector(const vector &x) {
    *this = x;
}

template <typename T> vector<T>::~vector() {
  if (myFirst != nullptr) {
    delete[] myFirst;
  }
}

template <typename T> const vector<T>& vector<T>::operator=(const vector &x) {
    if (myFirst != nullptr) {
        delete[] myFirst;
    }
    myFirst = (x.myFirst == nullptr) ? nullptr : new T [x.size()]();
    myLast = (x.myLast == nullptr) ? nullptr : myFirst + x.size();
    myEnd = (x.myEnd == nullptr) ? nullptr : myLast;
    iterator it1 = begin();
    iterator it2 = x.begin();
    for ( ; it1 < end(); it1++, it2++) {
        *it1 = *it2;
    }
    return *this;
}

template <typename T> T* vector<T>::begin() const { return myFirst; }
template <typename T> T* vector<T>::end() const { return myLast; }
template <typename T> unsigned int vector<T>::size() const { return unsigned(myLast - myFirst); }
template <typename T> unsigned int vector<T>::capacity() const { return unsigned(myEnd - myFirst); }

template <typename T> void vector<T>::push_back(const T val) {
    resize(size() + 1);
    myFirst[size() - 1] = val;
}

template <typename T> void vector<T>::pop_back() {
    if ( size() > 0 ) {
        --myLast;
        *myLast = T();
    }
}

template <typename T> void vector<T>::resize(unsigned int n) {
#if defined(__GNUC__) || defined(__GNUG__) //GNU GCC/G++
    const float COMPILER_GROWTH_FECTOR = 2;
#elif defined(_MSC_VER) //Microsoft Visual Studio
    const float COMPILER_GROWTH_FECTOR = 1.5;
#endif
    T* tempPtr = myFirst;
    int orgSize = size();
    int newCap = (n <= capacity()) ? capacity() : (n <= capacity() * COMPILER_GROWTH_FECTOR) ? capacity() * COMPILER_GROWTH_FECTOR : n;
    myFirst = new T [newCap]();
    for (int i = 0; i < newCap; i++) {
        myFirst[i] = (i < orgSize) ? tempPtr[i] : 0;
    }
    if (orgSize != 0) {
        delete [] tempPtr;
    }
    myLast = myFirst + n;
    myEnd = myFirst + newCap;
}


template <typename T> bool operator==(const vector<T> &lhs, const vector<T> &rhs) {
    if(lhs.size() != rhs.size()) {
        return false;
    }
    T* it1 = lhs.begin();
    T* it2 = rhs.begin();
    for(; it1 != lhs.end(); it1++, it2++) {
        if(*it1 != *it2) {
            return false;
        }
    }
    return true;
}

template <typename T> bool operator!=(const vector<T> &lhs, const vector<T> &rhs) { return !(lhs == rhs); }

#endif
