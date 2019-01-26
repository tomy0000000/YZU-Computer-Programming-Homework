//
//  Identifier - 1061519 - hw4.cpp
//  Hw4
//  C++ Non-Keyword Identifiers Printer
//
//  Created by Tomy Hsieh on 2018/3/18.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include "Identifier.h"

char keywords[ 61 ][ 20 ] = { "auto", "break", "case", "char", "const", "continue",
                              "default", "do", "double", "else", "enum", "extern",
                              "float", "for", "goto", "if", "int", "long",
                              "register", "return", "short", "signed", "sizeof",
                              "static", "struct", "switch", "typedef", "union",
                              "unsigned", "void", "volatile", "while", "bool",
                              "catch", "class", "const_cast", "delete",
                              "dynamic_cast", "explicit", "false", "friend",
                              "inline", "mutable", "namespace", "new", "operator",
                              "private", "protected", "public", "reinterpret_cast",
                              "static_cast", "template", "this", "throw", "true",
                              "try", "typeid", "typename", "using", "virtual",
                              "include" };

// default/conversion constructor
Identifier::Identifier() : identifier() {}

// overloaded = operator; avoids self assignment
const Identifier &Identifier::operator=( const string &right ) {
    identifier = right;
    return *this;
}

// check if the current identifier is a C++ keyword
bool Identifier::keyword() {
    for (int i = 0; i < 61; i++) {
        if (identifier == string(keywords[i], strlen(keywords[i]))) {
            return true;
        }
    }
    return false;
}

bool operator==( const Identifier &lhs, const Identifier &rhs )
{ return lhs.identifier == rhs.identifier; }

std::ostream &operator<<( std::ostream &output, Identifier &id ) {
    output << id.identifier;
    return output; // enables cout << x << y;
}
