//
//  HugeInteger - 1061519 - hw3.cpp
//  Hw3
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/3/13.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include "Vector.h"
#include "HugeInteger.h"

HugeInteger::HugeInteger(): integer( 1 ) {}
HugeInteger::HugeInteger(unsigned int n): integer( ( n > 0 ) ? n : 1 ) {}
HugeInteger::HugeInteger( const HugeInteger &integerToCopy ): integer( integerToCopy.integer ) {}
HugeInteger::~HugeInteger() {}

bool HugeInteger::equal( const HugeInteger &right ) const {
    if (integer.size() != right.integer.size()) {
        return false;
    }
    else {
        vector::iterator it1 = integer.begin();
        vector::iterator it2 = right.integer.begin();
        for ( ; it1 != integer.end(); it1++, it2++) {
            if (*it1 != *it2) {
                return false;
            }
        }
    }
    return true;
}

bool HugeInteger::less( const HugeInteger &right ) const {
    if (integer.size() < right.integer.size()) {
        return true;
    }
    else if (integer.size() > right.integer.size()) {
        return false;
    }
    else if (integer.size() == right.integer.size()) {
        vector::iterator it1 = integer.end() - 1;
        vector::iterator it2 = right.integer.end() - 1;
        for ( ; it1 >= integer.begin(); it1--, it2--) {
            if (*it1 < *it2) {
                return true;
            }
            else if (*it1 > *it2) {
                return false;
            }
        }
    }
    return false;
}

bool HugeInteger::lessEqual( const HugeInteger &right ) const {
    return ( less( right ) || equal( right ) );
}

bool HugeInteger::isZero() const {
    for ( vector::iterator it = integer.begin(); it != integer.end(); it++ ) {
        if ( *it != 0 ) {
            return false;
        }
    }
    return true;
}

HugeInteger HugeInteger::add( const HugeInteger &op2 ) const {
    unsigned int sumSize = ( integer.size() >= op2.integer.size() ) ? integer.size() + 1 : op2.integer.size() + 1;

    HugeInteger sum( sumSize );

    vector::iterator it1 = integer.begin();
    vector::iterator it3 = sum.integer.begin();
    for ( ; it1 != integer.end(); ++it1, ++it3 )
    { *it3 = *it1; }

    vector::iterator it2 = op2.integer.begin();
    for ( it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3 )
    { *it3 += *it2; }

    for ( it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3 )
        if ( *it3 > 9 ) {
            ( *it3 ) -= 10;
            ( *( it3 + 1 ) )++;
        }

    if ( *it3 == 0 )
    { sum.integer.pop_back(); }

    return sum;
}

HugeInteger HugeInteger::subtract( const HugeInteger &op2 ) const {
    
    //Initializing
    HugeInteger difference(integer.size());
    int TempFuture = 0, Cal, fsubtrahend;
    
    //Do Substraction
    for (vector::iterator it1 = integer.begin(), it2 = op2.integer.begin(), it3 = difference.integer.begin(); it1 != integer.end(); it1++, it2++, it3++) {
        fsubtrahend = (it2 < op2.integer.end()) ? *it2 : 0;
        Cal = *it1 - fsubtrahend + TempFuture;
        *it3 = (Cal >= 0) ? Cal : Cal + 10;
        TempFuture = (Cal >= 0) ? 0 : -1;
    }
    
    //Size Calibration
    while (*(difference.integer.end() - 1) == 0 && difference.integer.size() != 1) {
        difference.integer.pop_back();
    }
    
    return difference;
}

HugeInteger HugeInteger::multiply( const  HugeInteger &op2 ) const {
    
    //Initializing
    HugeInteger product(integer.size() + op2.integer.size() + 1);
    for (vector::iterator it = product.integer.begin() ; it != product.integer.end(); it++) {
        *it = 0;
    }
    
    //Double-Loop Calculate Each Digits
    for (vector::iterator it1 = integer.begin(); it1 != integer.end(); it1++) {
        for (vector::iterator it2 = op2.integer.begin(); it2 != op2.integer.end(); it2++) {
            vector::iterator it3 = product.integer.begin();
            it3 += (it1 - integer.begin());
            it3 += (it2 - op2.integer.begin());
            *it3 += (*it1) * (*it2);
        }
    }
    
    //Carry-Onnnnnn
    for (vector::iterator it = product.integer.begin(); it < product.integer.end(); it++) {
        if (*it >= 10) {
            *(it + 1) += *it / 10;
            *it %= 10;
        }
    }
    
    //Size Calibration
    while (*(product.integer.end() - 1) == 0 && product.integer.size() != 1) {
        product.integer.pop_back();
    }
    
    return product;
    
}

HugeInteger HugeInteger::divide( const HugeInteger &op2 ) const {
    
    //Initializing Quotient & Remainder
    HugeInteger quotient(1);
    HugeInteger remainder(integer.size());
    vector::iterator it1, it2;
    it1 = integer.begin();
    it2 = remainder.integer.begin();
    for (; it1 != integer.end(); it1++, it2++) {
        *it2 = *it1;
    }
    
    //End Function if Dividend is Smaller
    if (less(op2)) {
        *quotient.integer.begin() = 0;
        return quotient;
    }
    
    //Set Default QuotientSize
    quotient.integer.resize(integer.size() - op2.integer.size());
    
    //Create Buffer
    HugeInteger buffer(integer.size());
    int Shift = integer.size() - op2.integer.size();
    it1 = op2.integer.begin();
    it2 = buffer.integer.begin();
    for ( ; it2 != buffer.integer.end(); it1++, it2++) {
        *it2 = (it2 - buffer.integer.begin() >= Shift) ? *(it1 - Shift) : 0;
    }
    
    //Buffer Calibration & Quotient Cleaning
    if (less(buffer)) {
        buffer.divideByTen();
    }
    else {
        quotient.integer.resize(quotient.integer.size() + 1);
    }
    it1 = quotient.integer.begin();
    for ( ; it1 != quotient.integer.end(); it1++) {
        *it1 = 0;
    }
    
    //Calculate Remainder One Unit at One Time
    it1 = quotient.integer.end() - 1;
    for ( ; it1 >= quotient.integer.begin(); it1--) {
        while (buffer.lessEqual(remainder)) {
            remainder.assign(remainder.subtract(buffer));
            (*it1)++;
        }
        //Examine Remainder
        if (remainder.isZero()) {
            return quotient;
        }
        buffer.divideByTen();
    }
    
    return quotient;
    
}

HugeInteger HugeInteger::modulus( const HugeInteger &op2 ) const {
    HugeInteger quotient = divide( op2 );
    HugeInteger product = quotient.multiply( op2 );
    HugeInteger remainder = subtract( product );
    return remainder;
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger &HugeInteger::assign( const HugeInteger &right ) {
    //Avoid Self-Assignment
    if ( &right != this ) {
        integer.assign( right.integer );
    }
    return *this; // enables x = y = z, for example
}

void HugeInteger::convert( vector v ) {
    integer.resize( v.size() );
    for (vector::iterator it1 = integer.end() - 1, it2 = v.begin(); it2 != v.end(); it1--, it2++) {
        *it1 = *it2;
    }
}

void HugeInteger::output( std::ostream &outFile ) {
    for (vector::iterator it = integer.end() - 1; it != integer.begin() - 1; it--) {
        if (*it < 10) {
            outFile << *it;
        }
    }
    outFile << std::endl;
}

void HugeInteger::divideByTen() {
    for (vector::iterator it = integer.begin(), it2 = it+1; it2 != integer.end(); it++, it2++ ) {
        *it = *it2;
    }
    integer.pop_back();
}
