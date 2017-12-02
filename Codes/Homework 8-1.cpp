//
//  main.cpp
//  Hw8
//  Huge Integer Addition, Subtraction, Multiplication, and Division with Struct and Dynamic Memory Allocation
//
//  Created by Tomy Hsieh on 2017/11/13.
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

// HugeInt struct definition
struct HugeInt
{
    unsigned int size;
    int *elems;
};

void input( istream &inFile, HugeInt &hugeInt );
void perform( ostream &outFile, const HugeInt &hugeInt1, const HugeInt &hugeInt2, HugeInt &hugeInt3, HugeInt &hugeInt4 );
void output( ostream &outFile, const HugeInt &hugeInt );
bool isZero( const HugeInt &hugeInt );
bool equal( const HugeInt &hugeInt1, const HugeInt &hugeInt2 );
bool less( const HugeInt &hugeInt1, const HugeInt &hugeInt2 );
void addition( const HugeInt &addend, const HugeInt &adder, HugeInt &sum );
void subtraction( const HugeInt &minuend, const HugeInt &subtrahend, HugeInt &difference );
void multiplication( const HugeInt &multiplicand, const HugeInt &multiplier, HugeInt &product );
void division( const HugeInt &dividend, const HugeInt &divisor, HugeInt &quotient, HugeInt &remainder );
void divideByTen( HugeInt &hugeInt );
void assign( HugeInt &hugeInt1, const HugeInt &hugeInt2 );

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
    
    HugeInt hugeInt1 = { 0, NULL };
    HugeInt hugeInt2 = { 0, NULL };
    HugeInt hugeInt3 = { 0, NULL };
    HugeInt hugeInt4 = { 0, NULL };
    for( int i = 0; i < numTestCases; i++ ) {
        input( inFile, hugeInt1 );
        input( inFile, hugeInt2 );
        perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
        perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
        delete[] hugeInt1.elems;
        delete[] hugeInt2.elems;
    }
    
    inFile.close();
    outFile.close();
}

// enable user to input a positive huge integer
void input( istream &inFile, HugeInt &hugeInt )
{
    char numericString[ arraySize ];
    
    inFile >> numericString;
    
    hugeInt.size = strlen( numericString );
    hugeInt.elems = new int[ hugeInt.size ];
    for( unsigned int i = 0; i < hugeInt.size; i++ )
        hugeInt.elems[ hugeInt.size - i - 1 ] = numericString[ i ] - '0';
}

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, const HugeInt &hugeInt1, const HugeInt &hugeInt2,
             HugeInt &hugeInt3, HugeInt &hugeInt4 )
{
    output( outFile, hugeInt1 );
    output( outFile, hugeInt2 );
    
    addition( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 + hugeInt2
    output( outFile, hugeInt3 );
    delete [] hugeInt3.elems;
    
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
    delete[] hugeInt3.elems;
    
    multiplication( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 * hugeInt2
    output( outFile, hugeInt3 );
    delete[] hugeInt3.elems;
    
    if( isZero( hugeInt2 ) )
    {
        outFile << "DivideByZero!\n";
        outFile << "DivideByZero!\n";
    }
    else
    {
        // hugeInt3 = hugeInt1 / hugeInt2;   hugeInt4 = hugeInt1 % hugeInt2
        division( hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
        output( outFile, hugeInt3 );
        output( outFile, hugeInt4 );
        delete[] hugeInt3.elems;
        delete[] hugeInt4.elems;
    }
    
    outFile << endl;
}

// output the specified huge integer
void output( ostream &outFile, const HugeInt &hugeInt )
{
    if( isZero( hugeInt ) )
        outFile << 0;
    else
        for( int i = hugeInt.size - 1; i >= 0; i-- )
            if( hugeInt.elems[ i ] < 10 )
                outFile << hugeInt.elems[ i ];
    outFile << endl;
}

// test if a HugeInt is zero
bool isZero( const HugeInt &hugeInt )
{
    for( unsigned int i = 0; i < hugeInt.size; i++ )
        if( hugeInt.elems[ i ] != 0 )
            return false;
    return true;
}

// test if two HugeIntegers are equal
bool equal( const HugeInt &hugeInt1, const HugeInt &hugeInt2 ) {
    
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

// test if one HugeInt is less than another
bool less( const HugeInt &hugeInt1, const HugeInt &hugeInt2 ) {
    
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
void addition( const HugeInt &addend, const HugeInt &adder, HugeInt &sum ) {
    int Cal, faddend, fadder;
    sum.size = (addend.size >= adder.size) ? addend.size+1 : adder.size+1;
    sum.elems = new int[sum.size];
    std::fill_n(sum.elems, sum.size, 0);
    
    for (int i=0; i<sum.size; i++) {
        faddend = (i < addend.size) ? addend.elems[i] : 0;
        fadder = (i < adder.size) ? adder.elems[i] : 0;
        Cal = sum.elems[i] + faddend + fadder;
        sum.elems[i] = Cal%10;
        sum.elems[i+1] += Cal/10;
        sum.size = (i == sum.size-1 && sum.elems[i] == 0) ? sum.size-1 : sum.size;
    }
}

// provided that the minuend is greater than or equal to the subtrahend
void subtraction( const HugeInt &minuend, const HugeInt &subtrahend, HugeInt &difference ) {
    
    //Initialization
    int TempFuture=0, Cal, fsubtrahend;
    difference.elems = new int[difference.size];
    
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

void multiplication( const HugeInt &multiplicand, const HugeInt &multiplier, HugeInt &product ) {
    
    //Setting Default Product then Cleaning
    product.size = multiplicand.size + multiplier.size;
    product.elems = new int [product.size];
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
    
    //Size Calibration
    if (product.elems[product.size-1] == 0) {
        product.size--;
    }
}

void division( const HugeInt &dividend, const HugeInt &divisor, HugeInt &quotient, HugeInt &remainder ) {
    
    //Remainder Setting
    remainder.elems = new int [remainder.size];
    assign(remainder, dividend);
    
    //Raise dividendSmaller Case
    if (less(dividend, divisor)) {
        quotient.size = 1;
        quotient.elems = new int [quotient.size];
        quotient.elems[0] = 0;
        return;
    }
    
    //Buffer Setting
    HugeInt buffer = { 0, NULL };
    buffer.size = dividend.size;
    buffer.elems = new int[buffer.size];
    int Shift = dividend.size - divisor.size;
    for (int i = 0; i < buffer.size; i++) {
        buffer.elems[i] = (i >= Shift) ? divisor.elems[i - Shift] : 0;
    }
    
    //Buffer Calibration & Quotient Setting
    quotient.size = dividend.size - divisor.size;
    if (less(dividend, buffer)) {
        divideByTen(buffer);
    } else {
        quotient.size++;
    }
    quotient.elems = new int [quotient.size];
    std::fill_n(quotient.elems, quotient.size, 0);
    
    //Dividing
    for (int k = quotient.size - 1; k >= 0; k--) {
        while (less(buffer, remainder) || equal(buffer, remainder)) {
            HugeInt fremainder = { 0, NULL };
            fremainder.elems = new int[fremainder.size];
            assign(fremainder, remainder);
            subtraction(fremainder, buffer, remainder);
            delete[] fremainder.elems;
            quotient.elems[k]++;
            
            //Examine Remainder
            if (isZero(remainder)) {
                return;
            }
        }
        divideByTen(buffer);
    }
    
    //Release Kraken
    delete[] buffer.elems;
    
}

// hugeInt1 = hugeInt2; assignment
void assign( HugeInt &hugeInt1, const HugeInt &hugeInt2 )
{
    hugeInt1.size = hugeInt2.size;
    delete[] hugeInt1.elems;
    hugeInt1.elems = new int[ hugeInt1.size ];
    for( unsigned int i = 0; i < hugeInt1.size; i++ )
        hugeInt1.elems[ i ] = hugeInt2.elems[ i ];
}

// hugeInt /= 10
void divideByTen( HugeInt &hugeInt )
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
