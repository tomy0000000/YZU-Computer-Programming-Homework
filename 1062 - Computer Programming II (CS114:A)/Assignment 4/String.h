//
//  String.h
//  Hw4
//  C++ Non-Keyword Identifiers Printer
//
//  Created by Tomy Hsieh on 2018/3/18.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef STRING_H
#define STRING_H

#include <iostream>
using std::ostream;

class string {
    friend ostream &operator<<(ostream &output, string &str);
    friend bool operator==(const string &lhs, const string &rhs);
    friend bool operator!=(const string &lhs, const string &rhs);
public:
    static const bool printStr = false;
    // the greatest possible value for an element of type size_t (i.e., 4294967295)
    static const size_t npos = -1;
    #if defined(__clang__) //Clang
        static const unsigned int initSize = 22;
    #endif
    #if defined(_MSC_VER) //Microsoft Visual Studio
        static const unsigned int initSize = 15;
    #endif

    // Constructors & Destructors
    string();
    string(const string &str);
    string(const char *s, size_t n);
    ~string();

    // Operators
    string& operator=(const string &str);
    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;

    // Gears (Ptrs, Attributes...)
    char* begin();
    char* end();
    size_t size() const;
    size_t capacity() const;
    size_t find(char c, size_t pos = 0) const;
    int compare(const string& str) const;
    
    // Editing
    void resize(size_t n);
    void clear();
    void push_back(char c);
    void pop_back();
    string& assign(const char *s, size_t n);
    string& erase(size_t pos = 0, size_t len = npos);
    string substr(size_t pos = 0, size_t len = npos) const;

private:
    union Bxty {
        char buf[initSize+1];
        char *ptr;
    } bx;
    size_t mySize = 0;
    size_t myRes = initSize;
};

#endif
