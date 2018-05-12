//
//  Vector - 1061519 - hw3.cpp
//  Hw3
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/3/13.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include "Vector.h"

//Constructor
vector::vector( unsigned int n )
    : myFirst( n == 0 ? nullptr : new int[ n ]() ),
      myLast( n == 0 ? nullptr : myFirst + n ),
      myEnd( n == 0 ? nullptr : myLast ) {}

//Copy Constructor
vector::vector(const vector &x) {
    assign(x);
}

//Destructor
vector::~vector() {
    if ( myFirst != nullptr ) {
        delete[] myFirst;
    }
}

const vector &vector::assign(const vector &x) {
    if (myFirst != nullptr) {
        delete[] myFirst;
    }
    myFirst = (x.myFirst == nullptr) ? nullptr : new int[x.size()]();
    myLast = (x.myLast == nullptr) ? nullptr : myFirst + x.size();
    myEnd = (x.myEnd == nullptr) ? nullptr : myLast;
    iterator it1 = begin();
    iterator it2 = x.begin();
    for ( ; it1 < end(); it1++, it2++) {
        *it1 = *it2;
    }
    return *this;
}

int* vector::begin() const {return myFirst;}
int* vector::end() const {return myLast;}
unsigned int vector::size() const {return int( myLast - myFirst );}
unsigned int vector::capacity() const {return int( myEnd - myFirst );}

void vector::push_back(const int val) {
    resize(size() + 1);
    myFirst[size() - 1] = val;
}

void vector::pop_back() {
    if ( size() > 0 ) {
        --myLast;
        *myLast = int();
    }
}

void vector::resize(unsigned int n) {
#if defined(__GNUC__) || defined(__GNUG__) //GNU GCC/G++
    const float COMPILER_GROWTH_FECTOR = 2;
#elif defined(_MSC_VER) //Microsoft Visual Studio
    const float COMPILER_GROWTH_FECTOR = 1.5;
#endif
    int *tempPtr = myFirst;
    int orgSize = size();
    int newCap = (n <= capacity()) ? capacity() : (n <= capacity() * COMPILER_GROWTH_FECTOR) ? capacity() * COMPILER_GROWTH_FECTOR : n;
    myFirst = new int [newCap]();
    for (int i = 0; i < newCap; i++) {
        myFirst[i] = (i < orgSize) ? tempPtr[i] : 0;
    }
    if (orgSize != 0) {
        delete [] tempPtr;
    }
    myLast = myFirst + n;
    myEnd = myFirst + newCap;
}
