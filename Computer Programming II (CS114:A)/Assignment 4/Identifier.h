//
//  Identifier.h
//  Hw4
//  C++ Non-Keyword Identifiers Printer
//
//  Created by Tomy Hsieh on 2018/3/18.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "String.h" // string class definition

class Identifier {
    friend ostream &operator<<( ostream &output, Identifier &id );
    friend bool operator==( const Identifier &lhs, const Identifier &rhs );
public:
    Identifier();
    const Identifier &operator=( const string &right );
    bool keyword(); // check if the current identifier is a C++ keyword

private:
    string identifier;
};

#endif
