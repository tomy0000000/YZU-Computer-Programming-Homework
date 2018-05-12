//
//  String - 1061519 - hw2.cpp
//  Hw2
//  String Test Program
//
//  Created by Tomy Hsieh on 2018/2/28.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include "String.h"

char string::getItem(int pos) {
    return (myRes == initSize) ? bx.buf[pos] : bx.ptr[pos];
}

string::string() { bx.buf[0] = '\0'; }

string::string(const string &str) {
    mySize = str.mySize;
    myRes = str.myRes;
    if (myRes == initSize) {
        for (unsigned int i = 0; i <= mySize; i++) {
            bx.buf[i] = str.bx.buf[i];
        }
    }
    else {
        bx.ptr = new char[myRes + 1];
        for (unsigned int i = 0; i <= mySize; i++) {
            bx.ptr[i] = str.bx.ptr[i];
        }
    }
}

string::string(const char *s, unsigned int n) {
    if (n > initSize) {
        #if defined(__clang__) //Clang
            myRes = (myRes == initSize) ? 31 : myRes * 2 + 1;
            myRes = (myRes > ((n / 16) + 1) * 16 - 1) ? myRes : ((n / 16) + 1) * 16 - 1;
        #endif
        #if defined(_MSC_VER) //Microsoft Visual Studio
            myRes = (myRes * 1.5 - 1 > ((n / 16) + 1) * 16 - 1) ? myRes * 1.5 - 1 : ((n / 16) + 1) * 16 - 1;
        #endif
        bx.ptr = new char[myRes + 1];
    }
    char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr);
    for (int i = 0; i < n; i++) {
        tempPtr[i] = s[i];
    }
    mySize = n;
}

string::~string() {
    if (myRes > initSize) {
        delete[] bx.ptr;
    }
}

unsigned int string::size() const { return mySize; }
unsigned int string::capacity() const { return myRes; }

void string::resize(unsigned int n) {
    if (printStr) { cout << "-------------------------------\nRESIZING TO SIZE " << n << endl; }
    if (n > myRes) {
        int orgCap = myRes;
        #if defined(__clang__) //Clang
            // shaharmike.com/cpp/std-string/
            myRes = (myRes == initSize) ? 47 : myRes * 2 + 1;
            myRes = (myRes > ((n / 16) + 1) * 16 - 1) ? myRes : ((n / 16) + 1) * 16 - 1;
        #endif
        #if defined(_MSC_VER) //Microsoft Visual Studio
            myRes = (myRes * 1.5 > ((n / 16) + 1) * 16 - 1) ? myRes * 1.5 : ((n / 16) + 1) * 16 - 1;
        #endif
        char *tempPtr = new char[myRes+1];
        for (int i=0; i<n; i++) {
            tempPtr[i] = (i < mySize) ? ((orgCap == initSize) ? bx.buf[i] : bx.ptr[i]) : '\0';
        }
        if (orgCap > initSize) {
            delete [] bx.ptr;
        }
        bx.ptr = tempPtr;
    } else {
        char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr);
        for (int i = mySize; i < n; i++) {
            tempPtr[i] = '\0';
        }
    }
    mySize = n;
}

void string::clear() {
    if (printStr) { cout << "-------------------------------\nCLEAR STRING\n"; }
    resize(0);
    char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr);
    tempPtr[0] = '\0';
}

void string::push_back(char c) {
    if (printStr) { cout << "-------------------------------\nPUSHBACK WITH " << c << endl; }
    resize(mySize + 1);
    char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr);
    tempPtr[mySize-1] = c;
}

void string::pop_back() { mySize = (mySize > 0) ? mySize-1 : 0; }

string& string::assign(const char *s, unsigned int n) {
    if (printStr) {
        cout << "-------------------------------\nAssign char from " << n << endl;
        for (int i=0; i<strlen(s); i++) {
            cout << s[i];
        }
        cout << endl;
    }
    resize(n);
    char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr);
    for (int i = 0; i < n; i++) {
        tempPtr[i] = s[i];
    }
    return *this;
}

string& string::erase(unsigned int pos, unsigned int len) {
    if (printStr) { cout << "-------------------------------\nERASE FROM " << pos << " WITH LEN OF " << len << endl; }
    char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr);
    for (int i = pos; i < mySize; i++) {
        tempPtr[i] = (i + len < mySize) ? tempPtr[i + len] : '\0';
    }
    resize((pos + len >= mySize) ? pos : mySize - len);
    return *this;
}

unsigned int string::find(char c, unsigned int pos) const {
    const char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr);
    if (pos < mySize) {
        for (unsigned int i = pos; i < mySize; i++) {
            if (c == tempPtr[i]) {
                return i;
            }
        }
    }
    return npos;
}

string string::substr(unsigned int pos, unsigned int len) const {
    const char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr) + pos;
    string subString(tempPtr, (pos + len <= mySize) ? len : mySize - pos);
    return subString;
}

bool string::equal(std::string &str) {
    if (myRes != str.capacity() || mySize != str.size()) {
        return false;
    } else {
        const char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr);
        for (unsigned int i = 0; i < mySize; i++) {
            if (tempPtr[i] != str[i]) {
                return false;
            }
        }
    }
    return true;
}
