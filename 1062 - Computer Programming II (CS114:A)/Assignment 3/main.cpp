//
//  main.cpp
//  Hw3
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/3/13.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include "HugeInteger.h"

void input( HugeInteger n1[], HugeInteger n2[] );
void print( ostream &outFile, HugeInteger n1, HugeInteger n2 );

const int numTestCases = 22;

int main() {
    
    HugeInteger n1[ numTestCases ];
    HugeInteger n2[ numTestCases ];
    
    input( n1, n2 );
    
    for( int i = 0; i < numTestCases; i++ ) {
        print( cout, n1[ i ], n2[ i ] );
    }
    
    ofstream outFile( "Result.txt", ios::out );
    if( !outFile ) {
        cout << "File could not be opened" << endl;
        exit( 1 );
    }
    
    for( int i = 0; i < numTestCases; i++ ) {
        print( outFile, n1[ i ], n2[ i ] );
    }
    
    outFile.close();
}

void input( HugeInteger n1[], HugeInteger n2[] ) {
    ifstream inFile( "Test cases.txt", ios::in );
    if(!inFile) {
        cout << "File could not be opened" << endl;
        exit( 1 );
    }
    
    char digit;
    for( int i = 0; i < numTestCases; i++ ) {
        vector vector1, vector2;
        
        #if defined(__clang__)
        const char EOL_CHAR = '\r';
        const bool BITER = true;
        #endif
        #if defined(_MSC_VER)
        const char EOL_CHAR = '\n';
        const bool BITER = false;
        #endif
        
        while( ( digit = inFile.get() ) != EOL_CHAR ) {
            vector1.push_back( digit - '0' );
        }
        if (BITER) {
            inFile.get();
        }
        
        while( ( digit = inFile.get() ) != EOL_CHAR ) {
            vector2.push_back( digit - '0' );
        }
        if (BITER) {
            inFile.get();
        }
        
        inFile.get();
        if (BITER) {
            inFile.get();
        }
        
        n1[ i ].convert( vector1 );
        n2[ i ].convert( vector2 );
    }
    
    inFile.close();
}

void print( ostream &outFile, HugeInteger n1, HugeInteger n2 ) {
    
    // Output Original
    n1.output( outFile );
    n2.output( outFile );
    
    // Addition
    n1.add( n2 ).output( outFile );
    
    // Substraction
    if( n1.less( n2 ) ) {
        outFile << '-';
        n2.subtract( n1 ).output( outFile );
    } else {
        n1.subtract( n2 ).output( outFile );
    }
    
    // Multiply
    n1.multiply( n2 ).output( outFile );
    
    // Division
    if( n2.isZero() ) {
        outFile << "DivideByZero!\n";
    } else {
        n1.divide( n2 ).output( outFile );
    }
    
    // Modulus
    if( n2.isZero() ) {
        outFile << "DivideByZero!\n";
    } else {
        n1.modulus( n2 ).output( outFile );
    }
    
    // EOL
    outFile << endl;
}
