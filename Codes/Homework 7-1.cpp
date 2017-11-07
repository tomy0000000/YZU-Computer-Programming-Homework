//
//  main.cpp
//  Hw6-1
//  Huge Integer Addition, Subtraction, Multiplication, and Division
//
//  Created by Tomy Hsieh on 2017/10/24.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;

const unsigned int numTestCases = 22;
const unsigned int arraySize = 200;

// HugeInteger class definition
struct HugeInteger
{
    unsigned int size = 1;        // the number of digits of the integer; it can never be zero
    int elems[ arraySize ] = {};  // used to store a nonnegative integer, one digit per element
};


// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, HugeInteger hugeInt1, HugeInteger hugeInt2,
             HugeInteger hugeInt3, HugeInteger hugeInt4 );

// enable user to input a positive huge integer
void input( istream &inFile, HugeInteger &hugeInt );

// output the specified huge integer
void output( ostream &outFile, HugeInteger hugeInt );

// return true if and only if all digits are zero
bool isZero( HugeInteger hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInteger hugeInt1, HugeInteger hugeInt2 );

// return true if and only if hugeInt1 < hugeInt2
bool less( HugeInteger hugeInt1, HugeInteger hugeInt2 );

// sum = addend + adder
void addition( HugeInteger addend, HugeInteger adder, HugeInteger &sum );

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( HugeInteger minuend, HugeInteger subtrahend, HugeInteger &difference );

// product = multiplicand * multiplier
void multiplication( HugeInteger multiplicand, HugeInteger multiplier, HugeInteger &product );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( HugeInteger dividend, HugeInteger divisor, HugeInteger &quotient, HugeInteger &remainder );

// hugeInt /= 10
void divideByTen( HugeInteger &hugeInt );

int main() {
    
    ifstream inFile( "Test cases.txt", ios::in );
    
    if( !inFile ) {
        cout << "File could not be opened" << endl;
        exit( 1 );
    }
    
    ofstream outFile( "Result.txt", ios::out );
    
    if( !outFile ) {
        cout << "File could not be opened" << endl;
        exit( 1 );
    }
    
    for( int i = 0; i < numTestCases; i++ )
    {
        HugeInteger hugeInt1;
        HugeInteger hugeInt2;
        HugeInteger hugeInt3;
        HugeInteger hugeInt4;
        
        input( inFile, hugeInt1 );
        input( inFile, hugeInt2 );
        perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
        perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
    }
    
    inFile.close();
    outFile.close();
}

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, HugeInteger hugeInt1, HugeInteger hugeInt2,
             HugeInteger hugeInt3, HugeInteger hugeInt4 )
{
    output( outFile, hugeInt1 );
    output( outFile, hugeInt2 );
    
    addition( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 + hugeInt2
    output( outFile, hugeInt3 );
    
    if( less( hugeInt1, hugeInt2 ) )
    {
        outFile << '-';
        subtraction( hugeInt2, hugeInt1, hugeInt3 ); // hugeInt3 = hugeInt2 - hugeInt1
        output( outFile, hugeInt3 );
    }
    else
    {
        subtraction( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 - hugeInt2
        output( outFile, hugeInt3 );
    }
    
    multiplication( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 * hugeInt2
    output( outFile, hugeInt3 );
    
    if( isZero( hugeInt2 ) )
    {
        outFile << "DivideByZero!\n";
        outFile << "DivideByZero!\n";
    }
    else
    {
        // hugeInt3 = hugeInt1 / hugeInt2; // hugeInt4 = hugeInt1 % hugeInt2
        division( hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
        output( outFile, hugeInt3 );
        output( outFile, hugeInt4 );
    }
    
    outFile << endl;
}

void input( istream &inFile, HugeInteger &hugeInt )
{
    char numericString[ arraySize ];
    
    inFile >> numericString;
    
    hugeInt.size = strlen( numericString );
    for( unsigned int i = 0; i < hugeInt.size; i++ )
        hugeInt.elems[ hugeInt.size - i - 1 ] = numericString[ i ] - '0';
}

void output( ostream &outFile, HugeInteger hugeInt )
{
    if( isZero( hugeInt ) )
        outFile << 0;
    else
        for( int i = hugeInt.size - 1; i >= 0; i-- )
            if( hugeInt.elems[ i ] < 10 )
                outFile << hugeInt.elems[ i ];
    outFile << endl;
}

bool isZero( HugeInteger hugeInt )
{
    for( unsigned int i = 0; i < hugeInt.size; i++ )
        if( hugeInt.elems[ i ] != 0 )
            return false;
    return true;
}

bool equal( HugeInteger hugeInt1, HugeInteger hugeInt2 )
{
    if (hugeInt1.size != hugeInt2.size) {
        return false;
    }
    else {
        for (int i = 0; i < hugeInt1.size; i++) {
            if (hugeInt1.elems[i] != hugeInt2.elems[i]) {
                return false;
            }
        }
    }
    return true;
}

bool less( HugeInteger hugeInt1, HugeInteger hugeInt2 )
{
    if (hugeInt1.size < hugeInt2.size) {
        return true;
    } else if (hugeInt1.size > hugeInt2.size) {
        return false;
    } else if (hugeInt1.size == hugeInt2.size) {
        for (int i = hugeInt1.size - 1; i >= 0; i--) {
            if (hugeInt1.elems[i] < hugeInt2.elems[i]) {
                return true;
            } else if (hugeInt1.elems[i] > hugeInt2.elems[i]) {
                return false;
            }
        }
    }
    return false;
}

// sum = addend + adder
void addition( HugeInteger addend, HugeInteger adder, HugeInteger &sum )
{
    sum.size = ( addend.size >= adder.size ) ? addend.size + 1 : adder.size + 1;
    
    for( unsigned int i = 0; i < addend.size; i++ )
        sum.elems[ i ] = addend.elems[ i ];
    
    for( unsigned int i = addend.size; i < sum.size; i++ )
        sum.elems[ i ] = 0;
    
    for( unsigned int i = 0; i < adder.size; i++ )
        sum.elems[ i ] += adder.elems[ i ];
    
    for( unsigned int i = 0; i < sum.size - 1; i++ )
        if( sum.elems[ i ] > 9 ) // determine whether to carry a 1
        {
            sum.elems[ i ] -= 10; // reduce to 0-9
            sum.elems[ i + 1 ]++;
        }
    
    if( sum.elems[ sum.size - 1 ] == 0 )
        sum.size--;
}

// difference = minuend - subtrahend
void subtraction( HugeInteger minuend, HugeInteger subtrahend, HugeInteger &difference )
{
    int TempFuture=0, Cal, fsubtrahend;
    
    //Do Substraction
    for (int i = 0; i < minuend.size; i++) {
        fsubtrahend = (i < subtrahend.size) ? subtrahend.elems[i] : 0;
        Cal = minuend.elems[i] - fsubtrahend + TempFuture;
        difference.elems[i] = (Cal >= 0) ? Cal : Cal+10;
        TempFuture = (Cal >= 0) ? 0 : -1;
    }
    
    //Size Calibration
    for (int i=minuend.size-1; i>=0; i--) {
        if (difference.elems[i] != 0) {
            difference.size = i+1;
            break;
        }
        if (i == 0) {
            difference.size = 1;
        }
    }
}

// product = multiplicand * multiplier
void multiplication( HugeInteger multiplicand, HugeInteger multiplier, HugeInteger &product )
{
    //Setting Default Product then Cleaning
    product.size = multiplicand.size + multiplier.size;
    std::fill_n(product.elems, product.size, 0);
    
    //Double-Loop Calculate Each Digits
    for (int i = 0; i < multiplier.size; i++) {
        for (int k = 0; k < multiplicand.size; k++) {
            product.elems[i + k] += multiplicand.elems[k] * multiplier.elems[i];
        }
    }
    
    //Carry-Onnnnnn
    for (int i = 0; i < product.size; i++) {
        if (product.elems[i] >= 10) {
            product.elems[i+1] += product.elems[i]/10;
            product.elems[i] %= 10;
        }
    }
    
    //Recalculate Product Size
    if (product.elems[product.size-1] == 0) {
        product.size--;
    }
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( HugeInteger dividend, HugeInteger divisor, HugeInteger &quotient, HugeInteger &remainder )
{
    //Set Default QuotientSize & RemainderSize
    quotient.size = dividend.size - divisor.size;
    remainder.size = dividend.size;
    for (int i = 0; i < dividend.size; i++) {
        remainder.elems[i] = dividend.elems[i];
    }
    
    //End Function if Dividend is Smaller
    if (less(dividend, divisor)) {
        quotient.size = 1;
        quotient.elems[0] = 0;
        return;
    }
    
    //Create Buffer
    HugeInteger buffer;
    buffer.size = dividend.size;
    int Shift = dividend.size - divisor.size;
    for (int i = 0; i < buffer.size; i++) {
        buffer.elems[i] = (i >= Shift) ? divisor.elems[i - Shift] : 0;
    }
    
    //Buffer Calibration & Quotient Cleaning
    if (less(dividend, buffer)) {
        divideByTen(buffer);
    } else {
        quotient.size++;
    }
    std::fill_n(quotient.elems, quotient.size, 0);
    
    //Calculate Remainder One Unit at One Time
    for (int k = quotient.size - 1; k >= 0; k--) {
        
        while (less(buffer, remainder) || equal(buffer, remainder)) {
            subtraction(remainder, buffer, remainder);
            quotient.elems[k]++;
            
            //Examine Remainder
            if (isZero(remainder)) {
                return;
            }
        }
        divideByTen(buffer);
        
    }
}

// hugeInt /= 10
void divideByTen( HugeInteger &hugeInt )
{
    if( hugeInt.size == 1 )
        hugeInt.elems[ 0 ] = 0;
    else
    {
        for( unsigned int i = 1; i < hugeInt.size; i++ )
            hugeInt.elems[ i - 1 ] = hugeInt.elems[ i ];
        hugeInt.elems[ hugeInt.size - 1 ] = 0;
        hugeInt.size--;
    }
}
