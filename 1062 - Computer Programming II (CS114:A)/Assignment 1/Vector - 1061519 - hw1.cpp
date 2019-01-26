//
//  Vector - 1061519 - hw1.cpp
//  Hw1
//  Vector Test Program
//
//  Created by Tomy Hsieh on 2018/2/27.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include "Vector.h"

//  Constructor
vector::vector( unsigned int n ) {
    if( n == 0 ) {
        myFirst = myLast = myEnd = nullptr;
    } else {
        myFirst = new int[n]();
        myLast = myEnd = myFirst + n;
    }
}

//  Destructor
vector::~vector() {
    if( myFirst != nullptr ) {
        delete[] myFirst;
    }
}

unsigned int vector::size() { return ( myLast - myFirst ); }
unsigned int vector::capacity() { return ( myEnd - myFirst ); }

void vector::push_back( const int val ) {
    if (capacity() > size()) {
        myFirst[size()] = val;
        myLast += 1;
    } else {
        this->resize(size()+1);
        myFirst[size()-1] = val;
    }
}

void vector::pop_back() {
    if(size() > 0) {
        --myLast;
        *myLast = int();
    }
}


void vector::resize(unsigned int n) {
//    stackoverflow.com/questions/5232198/about-vectors-growth/5232477#5232477
//    nadeausoftware.com/articles/2012/10/c_c_tip_how_detect_compiler_name_and_version_using_compiler_predefined_macros
    #if defined(__GNUC__) || defined(__GNUG__) //GNU GCC/G++
        const float COMPILER_GROWTH_FECTOR = 2;
    #endif
    #if defined(_MSC_VER) //Microsoft Visual Studio
        const float COMPILER_GROWTH_FECTOR = 1.5;
    #endif
    int *tempPtr = myFirst;
    int orgSize = size();
    int newCap = (n <= capacity()) ? capacity() : (n <= capacity()*COMPILER_GROWTH_FECTOR) ? capacity() * COMPILER_GROWTH_FECTOR : n;
    myFirst = new int [newCap]();
    for (int i=0; i<newCap; i++) {
        myFirst[i] = (i < orgSize) ? tempPtr[i] : 0;
    }
    delete [] tempPtr;
    myLast = myFirst + n;
    myEnd = myFirst + newCap;
}

// Determines if two vectors are equal.
bool vector::equal(std::vector< int > &v) {
    if(capacity() != v.capacity() || size() != v.size()) {
        return false;
    }
    for(unsigned int i=0; i < size(); i++) {
        if(myFirst[i] != v[i]) { return false; }
    }
    return true;
}
