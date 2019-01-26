//
//  main.cpp
//  Hw6-2
//  Huge Integer Subtraction, Multiplication, and Division with Class
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
class HugeInteger
{
public:
    // enable user to input a positive huge integer
    void input( istream &inFile );
    
    // output the specified huge integer
    void output( ostream &outFile );
    
    // return true if and only if all digits are zero
    bool isZero();
    
    // return true if and only if current object == hugeInt2
    bool equal( HugeInteger hugeInt2 );
    
    // return true if and only if current object < hugeInt2
    bool less( HugeInteger hugeInt2 );
    
    // sum = current object + adder
    void addition( HugeInteger adder, HugeInteger &sum );
    
    // difference = current object - subtrahend
    // provided that the minuend is greater than or equal to the subtrahend
    void subtraction( HugeInteger subtrahend, HugeInteger &difference );
    
    // product = current object * multiplier
    void multiplication( HugeInteger multiplier, HugeInteger &product );
    
    // quotient = current object / divisor; remainder = current object % divisor
    // provided that the divisor is not equal to 0
    void division( HugeInteger divisor, HugeInteger &quotient, HugeInteger &remainder );
    
    // current object /= 10
    void divideByTen();
    
    unsigned int size = 1;        // the number of digits of the integer; it can never be zero
    int elems[ arraySize ] = {};  // used to store a nonnegative integer, one digit per element
}; // end class HugeInteger


// enable user to input a positive huge integer
void HugeInteger::input( istream &inFile )
{
    char numericString[ arraySize ];
    
    inFile >> numericString;
    
    size = strlen( numericString );
    for( unsigned int i = 0; i < size; i++ )
        elems[ size - i - 1 ] = numericString[ i ] - '0';
} // end function input

// output the specified huge integer
void HugeInteger::output( ostream &outFile )
{
    if( isZero() )
        outFile << 0;
    else
        for( int i = size - 1; i >= 0; i-- )
            if( elems[ i ] < 10 )
                outFile << elems[ i ];
    outFile << endl;
}


bool HugeInteger::isZero()
{
    for( unsigned int i = 0; i < size; i++ )
        if( elems[ i ] != 0 )
            return false;
    return true;
}

bool HugeInteger::equal( HugeInteger hugeInt2 )
{
    if (size != hugeInt2.size) {
        return false;
    }
    else {
        for (int i = 0; i < size; i++) {
            if (elems[i] != hugeInt2.elems[i]) {
                return false;
            }
        }
    }
    return true;
}

bool HugeInteger::less( HugeInteger hugeInt2 )
{
    if (size < hugeInt2.size) {
        return true;
    } else if (size > hugeInt2.size) {
        return false;
    } else if (size == hugeInt2.size) {
        for (int i = size - 1; i >= 0; i--) {
            if (elems[i] < hugeInt2.elems[i]) {
                return true;
            } else if (elems[i] > hugeInt2.elems[i]) {
                return false;
            }
        }
    }
    return false;
}

// sum = current object + adder
void HugeInteger::addition( HugeInteger adder, HugeInteger &sum )
{
    sum.size = ( size >= adder.size ) ? size + 1 : adder.size + 1;
    
    for( unsigned int i = 0; i < size; i++ )
        sum.elems[ i ] = elems[ i ];
    
    for( unsigned int i = size; i < sum.size; i++ )
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

void HugeInteger::subtraction( HugeInteger subtrahend, HugeInteger &difference )
{
    int TempFuture=0, Cal, fsubtrahend;
    
    //Do Substraction
    for (int i = 0; i < size; i++) {
        fsubtrahend = (i < subtrahend.size) ? subtrahend.elems[i] : 0;
        Cal = elems[i] - fsubtrahend + TempFuture;
        difference.elems[i] = (Cal >= 0) ? Cal : Cal+10;
        TempFuture = (Cal >= 0) ? 0 : -1;
    }
    
    //Size Calibration
    for (int i=size-1; i>=0; i--) {
        if (difference.elems[i] != 0) {
            difference.size = i+1;
            break;
        }
        if (i == 0) {
            difference.size = 1;
        }
    }
}

void HugeInteger::multiplication( HugeInteger multiplier, HugeInteger &product )
{
    //Setting Default Product then Cleaning
    product.size = size + multiplier.size;
    std::fill_n(product.elems, product.size, 0);
    
    //Double-Loop Calculate Each Digits
    for (int i = 0; i < multiplier.size; i++) {
        for (int k = 0; k < size; k++) {
            product.elems[i + k] += elems[k] * multiplier.elems[i];
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

void HugeInteger::division( HugeInteger divisor, HugeInteger &quotient, HugeInteger &remainder )
{
    //Set Default QuotientSize & RemainderSize
    quotient.size = size - divisor.size;
    remainder.size = size;
    for (int i = 0; i < size; i++) {
        remainder.elems[i] = elems[i];
    }
    
    //End Function if Dividend is Smaller
    if (this->less(divisor)) { //dividend less than divisor
        quotient.size = 1;
        quotient.elems[0] = 0;
        return;
    }
    
    //Create Buffer
    HugeInteger buffer;
    buffer.size = size;
    int Shift = size - divisor.size;
    for (int i = 0; i < buffer.size; i++) {
        buffer.elems[i] = (i >= Shift) ? divisor.elems[i - Shift] : 0;
    }
    
    //Buffer Calibration & Quotient Cleaning
    if (less(buffer)) { //dividend less than divisor
        buffer.divideByTen();
    } else {
        quotient.size++;
    }
    std::fill_n(quotient.elems, quotient.size, 0);
    
    //Calculate Remainder One Unit at One Time
    for (int k = quotient.size - 1; k >= 0; k--) {
        
        while (buffer.less(remainder) || buffer.equal(remainder)) {
            remainder.subtraction(buffer, remainder);
            quotient.elems[k]++;
            
            //Examine Remainder
            if (remainder.isZero()) {
                return;
            }
        }
        buffer.divideByTen();
        
    }
}

// current object /= 10
void HugeInteger::divideByTen()
{
    if( size == 1 )
        elems[ 0 ] = 0;
    else
    {
        for( unsigned int i = 1; i < size; i++ )
            elems[ i - 1 ] = elems[ i ];
        elems[ size - 1 ] = 0;
        size--;
    }
} // end function divideByTen


void perform( ostream &outFile, HugeInteger hugeInt1, HugeInteger hugeInt2,
             HugeInteger hugeInt3, HugeInteger hugeInt4 );

int main()
{
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
    
    for( int i = 0; i < numTestCases; i++ ) {
        HugeInteger hugeInt1;
        HugeInteger hugeInt2;
        HugeInteger hugeInt3;
        HugeInteger hugeInt4;
        
        hugeInt1.input( inFile );
        hugeInt2.input( inFile );
        perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
        perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
    }
    
    inFile.close();
    outFile.close();
}

void perform( ostream &outFile, HugeInteger hugeInt1, HugeInteger hugeInt2,
             HugeInteger hugeInt3, HugeInteger hugeInt4 )
{
    hugeInt1.output( outFile );
    hugeInt2.output( outFile );
    
    hugeInt1.addition( hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 + hugeInt2
    hugeInt3.output( outFile );
    
    if( hugeInt1.less( hugeInt2 ) )
    {
        outFile << '-';
        hugeInt2.subtraction( hugeInt1, hugeInt3 ); // hugeInt3 = hugeInt2 - hugeInt1
        hugeInt3.output( outFile );
    }
    else
    {
        hugeInt1.subtraction( hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 - hugeInt2
        hugeInt3.output( outFile );
    }
    
    hugeInt1.multiplication( hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 * hugeInt2
    hugeInt3.output( outFile );
    
    if (hugeInt2.isZero()) {
        outFile << "DivideByZero!\n";
        outFile << "DivideByZero!\n";
    }
    else {
        // hugeInt3 = hugeInt1 / hugeInt2; // hugeInt4 = hugeInt1 % hugeInt2
        hugeInt1.division( hugeInt2, hugeInt3, hugeInt4 );
        hugeInt3.output( outFile );
        hugeInt4.output( outFile );
    }
    
    outFile << endl;
}

