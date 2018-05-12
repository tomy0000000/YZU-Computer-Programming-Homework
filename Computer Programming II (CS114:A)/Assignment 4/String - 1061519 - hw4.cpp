//
//  String - 1061519 - hw4.cpp
//  Hw4
//  C++ Non-Keyword Identifiers Printer
//
//  Created by Tomy Hsieh on 2018/3/18.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include "String.h"

std::ostream &operator<<( std::ostream &output, string &str ) {
    char *tempPtr = ((str.myRes == string::initSize) ? str.bx.buf : str.bx.ptr);
    for (size_t i = 0; i < str.mySize; i++) {
        output << tempPtr[i];
    }
    return output; // enables cout << x << y;
}

bool operator==( const string &lhs, const string &rhs )
{ return ( lhs.compare( rhs ) == 0 ); }

bool operator!=( const string &lhs, const string &rhs )
{ return ( lhs.compare( rhs ) != 0 ); }

string::string() { bx.buf[ 0 ] = '\0'; }

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

string::string(const char * s, size_t n) {
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

string & string::operator=(const string & str) {
    char *ptr1 = ((myRes == initSize) ? bx.buf : bx.ptr);
    const char *ptr2 = ((str.myRes == initSize) ? str.bx.buf : str.bx.ptr);
    if (printStr) {
        cout << "-------------------------------\n=STRING FROM\n";
        for (int i=0; i<str.size(); i++) {
            cout << ptr2[i];
        }
        cout << endl;
    }
    resize(str.size());
    for (int i = 0; i < str.size(); i++) {
        ptr1[i] = ptr2[i];
    }
    return *this;
}
char & string::operator[](size_t pos)
{ return (myRes == initSize) ? bx.buf[pos] : bx.ptr[pos]; }

char* string::begin() { return (myRes == initSize) ? bx.buf : bx.ptr; }
char* string::end() { return begin() + mySize; }
size_t string::size() const { return mySize; }
size_t string::capacity() const { return myRes; }

size_t string::find(char c, size_t pos) const {
    const char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr);
    if (pos < mySize) {
        for (size_t i = pos; i < mySize; i++) {
            if (c == tempPtr[i]) {
                return i;
            }
        }
    }
    return npos;
}

int string::compare(const string & str) const {
    const char *ptr1 = ((myRes == initSize) ? bx.buf : bx.ptr);
    const char *ptr2 = ((str.myRes == initSize) ? str.bx.buf : str.bx.ptr);
    for (int i=0; i<((size() < str.size()) ? size() : str.size()); i++) {
        if (ptr1[i] < ptr2[i]) {
            return -1;
        } else if (ptr1[i] > ptr2[i]) {
            return 1;
        }
    }
    if (size() != str.size()) {
        return (size()<str.size()) ? -1 : 1;
    }
    return 0;
}

void string::resize(size_t n) {
    if (printStr) { cout << "-------------------------------\nRESIZING TO SIZE " << n << endl; }
    if (n > myRes) {
        int orgCap = int(myRes);
        #if defined(__clang__) //Clang
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
            delete bx.ptr;
        }
        bx.ptr = tempPtr;
    } else {
        char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr);
        for (size_t i = mySize; i < n; i++) {
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

void string::pop_back()
{ mySize = (mySize > 0) ? mySize-1 : 0; }

string & string::assign(const char * s, size_t n) {
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

string & string::erase(size_t pos, size_t len) {
    if (printStr) { cout << "-------------------------------\nERASE FROM " << pos << " WITH LEN OF " << len << endl; }
    len = (len == npos) ? myRes - pos : len;
    char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr);
    for (size_t i = pos; i < mySize; i++) {
        tempPtr[i] = (i + len < mySize) ? tempPtr[i + len] : '\0';
    }
    resize((pos + len >= mySize) ? pos : mySize - len);
    return *this;
}

string string::substr(size_t pos, size_t len) const {
    const char *tempPtr = ((myRes == initSize) ? bx.buf : bx.ptr) + pos;
    string subString(tempPtr, (pos + len <= mySize) ? len : mySize - pos);
    return subString;
}
