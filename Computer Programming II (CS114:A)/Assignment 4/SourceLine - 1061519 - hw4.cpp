//
//  SourceLine - 1061519 - hw4.cpp
//  Hw4
//  C++ Non-Keyword Identifiers Printer
//
//  Created by Tomy Hsieh on 2018/3/18.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;

#include "SourceLine.h"

void SourceLine::printSourceLine() {
    for (size_t i=0; i<sourceLine.size(); i++) {
        cout << ((sourceLine[i] == '\0') ? '0' : sourceLine[i]);
    }
    cout << endl;
}

// default/conversion constructor
SourceLine::SourceLine() : sourceLine() {}

void SourceLine::assign( const char *s, size_t n ) {
    sourceLine.assign(s, n);
}

void SourceLine::delComments() {
    size_t slashPos = sourceLine.find('/');
    if (slashPos != npos && sourceLine[slashPos+1] == '/') {
        sourceLine.erase(slashPos);
    }
}

void SourceLine::delStrConst() {
    size_t strPos = sourceLine.find('"');
    size_t strEndPos = sourceLine.find('"', strPos+1);
    while (sourceLine[strEndPos+1] == ' ') { strEndPos++; }
    while (strPos != npos) {
        sourceLine.erase(strPos, strEndPos-strPos+1);
        strPos = sourceLine.find('"');
        strEndPos = sourceLine.find('"', strPos+1);
        while (sourceLine[strEndPos+1] == ' ') { strEndPos++; }
    }
}

void SourceLine::delCharConst() {
    size_t charPos = sourceLine.find('\'');
    size_t charEndPos = sourceLine.find('\'', charPos+1);
    while (sourceLine[charEndPos+1] == ' ') { charEndPos++; }
    while (charPos != npos) {
        sourceLine.erase(charPos, charEndPos);
        charPos = sourceLine.find('\'', charPos+1);
        charEndPos = sourceLine.find('\'', charPos+1);
        while (sourceLine[charEndPos+1] == ' ') { charEndPos++; }
    }
}

string SourceLine::delFirstIdentifier() {
    size_t identifierPos = 0;
    while ((!isIdentifierChar(sourceLine[identifierPos], true)) && (identifierPos < sourceLine.size())) {
        identifierPos++;
    }
    size_t identifierEndPos = identifierPos;
    while ((isIdentifierChar(sourceLine[identifierEndPos], false)) && (identifierEndPos < sourceLine.size())) {
        identifierEndPos++;
    }
    string identifier = sourceLine.substr(identifierPos, identifierEndPos - identifierPos);
    sourceLine.erase(identifierPos, identifierEndPos - identifierPos);
    return identifier;
}

bool isIdentifierChar(char c, bool first) {
    if (c >= '0' && c <= '9' && !first) {
        return true;
    }
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    if (c == '_') {
        return true;
    }
    return false;
}
