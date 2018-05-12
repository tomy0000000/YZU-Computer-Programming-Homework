//
//  main.cpp
//  Hw4
//  C++ Non-Keyword Identifiers Printer
//
//  Created by Tomy Hsieh on 2018/3/18.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;
using std::ios;
#include "Identifier.h"
#include "SourceLine.h"

bool duplicate(Identifier identifiers[], int pos);
void printAllIdentifiers(Identifier identifiers[], int numIdentifiers);

int main() {
    ifstream inFile( "test.cpp", ios::in );

    // exit program if ifstream could not open file
    if ( !inFile ) {
        std::cout << "File could not be opened" << std::endl;
        system( "pause" );
        exit( 1 );
    }

    char source[ 200 ];
    SourceLine sourceLine;
    Identifier identifiers[ 1000 ];
    string identifier;
    string null;
    int numIdentifiers = 0;
    
    #if defined(__clang__)
        const char EOL_CHAR = '\r';
    #endif
    #if defined(_MSC_VER)
        const char EOL_CHAR = '\n';
    #endif

    while (inFile.getline( source, sizeof( source ), EOL_CHAR )) {
        sourceLine.assign( source, strlen( source ) );
        
//        sourceLine.printSourceLine();
        
        sourceLine.delComments();
        sourceLine.delStrConst();
        sourceLine.delCharConst();
        
//        sourceLine.printSourceLine();

        // extracts all identifiers from sourceLine
        while ( ( identifier = sourceLine.delFirstIdentifier() ) != null ) {
            identifiers[numIdentifiers++] = identifier;
        }
        #if defined(__clang__)
            inFile.get();
        #endif
    }

//    printAllIdentifiers(identifiers, numIdentifiers);
    
    for ( int i = 0; i < numIdentifiers; i++ ) {
        if ( !identifiers[ i ].keyword() && !duplicate( identifiers, i ) ) {
            cout << identifiers[ i ] << endl;
        }
    }

    system( "pause" );
}

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(Identifier identifiers[], int pos) {
    for ( int i = 0; i < pos; i++ ) {
        if (identifiers[ i ] == identifiers[ pos ]) {
            return true;
        }
    }
    return false;
}

void printAllIdentifiers(Identifier identifiers[], int numIdentifiers) {
    for (int i=0; i < numIdentifiers; i++) {
        cout << i << ": " << identifiers[i] << endl;
    }
}
