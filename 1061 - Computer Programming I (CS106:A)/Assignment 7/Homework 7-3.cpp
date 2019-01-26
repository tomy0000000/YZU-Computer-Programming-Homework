//
//  main.cpp
//  Hw6-3
//  Huge Integer Subtraction, Multiplication, and Division with Vector
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

#include <vector>
using std::vector;

const unsigned int numTestCases = 22;
const unsigned int arraySize = 200;

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, vector< int > hugeInt1, vector< int > hugeInt2,
             vector< int > hugeInt3, vector< int > hugeInt4 );

// enable user to input a positive huge integer
void input( istream &inFile, vector< int > &hugeInt );

// output the specified huge integer
void output( ostream &outFile, vector< int > hugeInt );

// return true if and only if all digits are zero
bool isZero( vector< int > hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( vector< int > hugeInt1, vector< int > hugeInt2 );

// return true if and only if hugeInt1 < hugeInt2
bool less( vector< int > hugeInt1, vector< int > hugeInt2 );

// sum = addend + adder
void addition( vector< int > addend, vector< int > adder, vector< int > &sum );

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( vector< int > minuend, vector< int > subtrahend, vector< int > &difference );

// product = multiplicand * multiplier
void multiplication( vector< int > multiplicand, vector< int > multiplier, vector< int > &product );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( vector< int > dividend, vector< int > divisor, vector< int > &quotient, vector< int > &remainder );

// hugeInt /= 10
void divideByTen( vector< int > &hugeInt );

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
    
    for( int i = 0; i < numTestCases; i++ )
    {
        vector< int > hugeInt1;
        vector< int > hugeInt2;
        vector< int > hugeInt3;
        vector< int > hugeInt4;
        
        input( inFile, hugeInt1 );
        input( inFile, hugeInt2 );
        perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
        perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
    }
    
    inFile.close();
    outFile.close();
}

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, vector< int > hugeInt1, vector< int > hugeInt2,
             vector< int > hugeInt3, vector< int > hugeInt4 )
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

void input( istream &inFile, vector< int > &hugeInt )
{
    char numericString[ arraySize ];
    
    inFile >> numericString;
    
    hugeInt.resize( strlen( numericString ) );
    for( unsigned int i = 0; i < hugeInt.size(); i++ )
        hugeInt[ hugeInt.size() - i - 1 ] = numericString[ i ] - '0';
}

void output( ostream &outFile, vector< int > hugeInt )
{
    if( isZero( hugeInt ) )
        outFile << 0;
    else
        for( int i = int(hugeInt.size())-1; i >= 0; i-- )
            if( hugeInt[ i ] < 10 )
                outFile << hugeInt[ i ];
    outFile << endl;
}

bool isZero( vector< int > hugeInt )
{
    for( unsigned int i = 0; i < hugeInt.size(); i++ )
        if( hugeInt[ i ] != 0 )
            return false;
    return true;
}

bool equal( vector< int > hugeInt1, vector< int > hugeInt2 )
{
    if (hugeInt1.size() != hugeInt2.size()) {
        return false;
    }
    else {
        for (int i = 0; i < hugeInt1.size(); i++) {
            if (hugeInt1[i] != hugeInt2[i]) {
                return false;
            }
        }
    }
    return true;
}

bool less( vector< int > hugeInt1, vector< int > hugeInt2 )
{
    if (hugeInt1.size() < hugeInt2.size()) {
        return true;
    } else if (hugeInt1.size() > hugeInt2.size()) {
        return false;
    } else if (hugeInt1.size() == hugeInt2.size()) {
        for (int i = int(hugeInt1.size())-1; i >= 0; i--) {
            if (hugeInt1[i] < hugeInt2[i]) {
                return true;
            } else if (hugeInt1[i] > hugeInt2[i]) {
                return false;
            }
        }
    }
    return false;
}

void addition( vector< int > addend, vector< int > adder, vector< int > &sum )
{
    sum.resize( ( addend.size() >= adder.size() ) ? addend.size() + 1 : adder.size() + 1 );
    
    for( unsigned int i = 0; i < addend.size(); i++ )
        sum[ i ] = addend[ i ];
    
    for( unsigned int i = int(addend.size()); i < sum.size(); i++ )
        sum[ i ] = 0;
    
    for( unsigned int i = 0; i < adder.size(); i++ )
        sum[ i ] += adder[ i ];
    
    for( unsigned int i = 0; i < sum.size() - 1; i++ )
        if( sum[ i ] > 9 ) // determine whether to carry a 1
        {
            sum[ i ] -= 10; // reduce to 0-9
            sum[ i + 1 ]++;
        }
    
    if( sum[ sum.size() - 1 ] == 0 )
        sum.pop_back();
}

void subtraction( vector< int > minuend, vector< int > subtrahend, vector< int > &difference )
{
    int TempFuture=0, Cal, fsubtrahend;
    
    //Do Substraction
    for (int i = 0; i < minuend.size(); i++) {
        fsubtrahend = (i < subtrahend.size()) ? subtrahend[i] : 0;
        Cal = minuend[i] - fsubtrahend + TempFuture;
        difference[i] = (Cal >= 0) ? Cal : Cal+10;
        TempFuture = (Cal >= 0) ? 0 : -1;
    }
    
    //Size Calibration
    for (int i=int(minuend.size())-1; i>=0; i--) {
        if (difference[i] != 0) {
            difference.resize(i+1);
            break;
        }
        if (i == 0) {
            difference.resize(1);
        }
    }
}

void multiplication( vector< int > multiplicand, vector< int > multiplier, vector< int > &product )
{
    //Setting Default Product then Cleaning
    product.resize(multiplicand.size() + multiplier.size());
    
    for (int i=0; i<product.size(); i++) {
        product[i] = 0;
    }
    
    //Double-Loop Calculate Each Digits
    for (int i = 0; i < multiplier.size(); i++) {
        for (int k = 0; k < multiplicand.size(); k++) {
            product[i + k] += multiplicand[k] * multiplier[i];
        }
    }
    
    //Carry-Onnnnnn
    for (int i = 0; i < product.size(); i++) {
        if (product[i] >= 10) {
            product[i+1] += product[i]/10;
            product[i] %= 10;
        }
    }
    
    //Recalculate Product Size
    if (product[product.size()-1] == 0) {
        product.resize(product.size()-1);
    }
}

void division( vector< int > dividend, vector< int > divisor, vector< int > &quotient, vector< int > &remainder )
{
    //Set Default RemainderSize
    remainder.resize(dividend.size());
    for (int i = 0; i < dividend.size(); i++) {
        remainder[i] = dividend[i];
    }
    
    //End Function if Dividend is Smaller
    if (less(dividend, divisor)) {
        quotient.resize(1);
        quotient[0] = 0;
        return;
    }
    
    //Set Default QuotientSize
    quotient.resize(dividend.size() - divisor.size());
    
    //Create Buffer
    vector<int> buffer;
    buffer.resize(dividend.size());
    int Shift = int(dividend.size()) - int(divisor.size());
    for (int i = 0; i < buffer.size(); i++) {
        buffer[i] = (i >= Shift) ? divisor[i - Shift] : 0;
    }
    
    //Buffer Calibration & Quotient Cleaning
    if (less(dividend, buffer)) {
        divideByTen(buffer);
    } else {
        quotient.resize(quotient.size()+1);
    }
    for (int i=0; i<quotient.size(); i++) {
        quotient[i] = 0;
    }
    
    //Calculate Remainder One Unit at One Time
    for (int k = int(quotient.size()-1); k >= 0; k--) {
        
        while (less(buffer, remainder) || equal(buffer, remainder)) {
            subtraction(remainder, buffer, remainder);
            quotient[k]++;
            
            //Examine Remainder
            if (isZero(remainder)) {
                return;
            }
        }
        divideByTen(buffer);
        
    }
}

// hugeInt /= 10
void divideByTen( vector< int > &hugeInt )
{
    if( hugeInt.size() == 1 )
        hugeInt[ 0 ] = 0;
    else
    {
        for( unsigned int i = 1; i < hugeInt.size(); i++ )
            hugeInt[ i - 1 ] = hugeInt[ i ];
        hugeInt[ hugeInt.size() - 1 ] = 0;
        hugeInt.pop_back();
    }
}
