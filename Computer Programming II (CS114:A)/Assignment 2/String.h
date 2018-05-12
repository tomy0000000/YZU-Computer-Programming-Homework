//
//  String.h
//  Hw2
//  String Test Program
//
//  Created by Tomy Hsieh on 2018/2/28.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef STRING_H
#define STRING_H

class string {
public:
    static const bool printStr = false;
    static const unsigned int npos = -1;
    #if defined(__clang__) //Clang
        static const unsigned int initSize = 22;
    #endif
    #if defined(_MSC_VER) //Microsoft Visual Studio
        static const unsigned int initSize = 15;
    #endif
    
    char getItem(int pos);
    
    string();
    string(const string &str);
    string( const char *s, unsigned int n );
    ~string();
    
    unsigned int size() const;
    unsigned int capacity() const;
    
    void resize( unsigned int n ); // If n > length, new elements are '\0'
    void clear(); // clear to size 0, with 1 element: '\0'
    void push_back( char c );
    void pop_back();
    
    // Rebuild string with s[:n]
    string& assign( const char *s, unsigned int n );
    
    // Erase len chars strart from pos, move everything behind to pos
    string& erase( unsigned int pos = 0, unsigned int len = npos );
    
    // Return loc(c) if c in string[pos:] else npos
    unsigned int find( char c, unsigned int pos = 0 ) const;
    
    // Return new string with content of string[pos:pos+len]
    string substr( unsigned int pos = 0, unsigned int len = npos ) const;
    
    bool equal( std::string &str );
    
private:
    union Bxty {
        char buf[initSize+1];
        char *ptr;
    } bx;
    unsigned int mySize = 0;
    unsigned int myRes = initSize;
};

#endif
