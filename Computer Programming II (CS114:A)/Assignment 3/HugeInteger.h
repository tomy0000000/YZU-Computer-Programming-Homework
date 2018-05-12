//
//  HugeInteger.h
//  Hw3
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/3/13.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H
#include "Vector.h"

class HugeInteger {
public:
    
    //Constructor & Destructors
    HugeInteger();
    HugeInteger( const HugeInteger &integerToCopy );
    ~HugeInteger();
    
    //Comparing Functions
    bool equal( const HugeInteger &right ) const;
//    bool notEqual( const HugeInteger &right ) const;
    bool less( const HugeInteger &right ) const;
    bool lessEqual( const HugeInteger &right ) const;
//    bool greater( const HugeInteger &right ) const;
//    bool greaterEqual( const HugeInteger &right ) const;
    bool isZero() const;
    
    //Arithmetics
    HugeInteger add( const HugeInteger &op2 ) const;
    HugeInteger subtract( const HugeInteger &op2 ) const; // Minuend must be Bigger than Subtrahend
    HugeInteger multiply( const  HugeInteger &op2 ) const;
    HugeInteger divide( const HugeInteger &op2 ) const; // Dividor must not be 0
    HugeInteger modulus( const HugeInteger &op2 ) const; // Dividor must not be 0

    //Some Gears
    const HugeInteger &assign( const HugeInteger &right );
    void convert( vector vector ); // vector -> HugeInteger
    void output( std::ostream &outFile );
    
private:
    vector integer;
    HugeInteger( unsigned int n ); // constructor
    void divideByTen();
    
};

#endif
