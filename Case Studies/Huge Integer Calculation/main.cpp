//
//  main.cpp
//  HugeInt Calculation
//  Huge Integer Addition, Subtraction, Multiplication, and Division
//
//  Created by Tomy Hsieh on 2017/10/11.
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

// enable user to input two positive huge integers from user
void inputTwoHugeInts(istream & inFile, int hugeInt1[], int hugeInt2[], int & size1, int & size2);

// perform addition, subtraction, multiplication and division
void perform(ostream & outFile, int hugeInt1[], int hugeInt2[], int hugeInt3[],
             int hugeInt4[], int size1, int size2, int size3, int size4);

// output the specified huge integer
void output(ostream & outFile, int hugeInt[], int size);

// returns true if and only if the specified huge integer is zero
bool isZero(int hugeInt[], int size);

// return true if and only if hugeInt1 == hugeInt2
bool equal(int hugeInt1[], int hugeInt2[], int size1, int size2);

// returns true if and only if hugeInt1 < hugeInt2
bool less(int hugeInt1[], int hugeInt2[], int size1, int size2);

// sum = addend + adder
void addition(int addend[], int adder[], int sum[], int addendSize, int adderSize, int & sumSize);

// difference = minuend - subtrahend
void subtraction(int minuend[], int subtrahend[], int difference[],
                 int minuendSize, int subtrahendSize, int & differenceSize);

// product = multiplicand * multiplier
void multiplication(int multiplicand[], int multiplier[], int product[],
                    int multiplicandSize, int multiplierSize, int & productSize);

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int dividend[], int divisor[], int quotient[], int remainder[],
              int dividendSize, int divisorSize, int & quotientSize, int & remainderSize);

// hugeInt /= 10
void divideBy10(int hugeInt[], int & size);

const int numTestCases = 22; // the number of test cases
const int arraySize = 200;

int main() {
    
    //File Reading Stream
    ifstream inFile("Test cases.txt", ios:: in );
    if (!inFile) {
        cout << "File could not be opened" << endl;
        exit(1);
    }
    
    //File Writing Stream
    ofstream outFile("Result.txt", ios::out);
    if (!outFile) {
        cout << "File could not be opened" << endl;
        exit(1);
    }
    
    //Run Process Twice with Oupput to Console & File
    for (int i = 0; i < numTestCases; i++) {
        int hugeInt1[arraySize] = {};
        int hugeInt2[arraySize] = {};
        int hugeInt3[arraySize] = {};
        int hugeInt4[arraySize] = {};
        int size1 = 0;
        int size2 = 0;
        int size3 = 0;
        int size4 = 0;
        
        inputTwoHugeInts(inFile, hugeInt1, hugeInt2, size1, size2);
        perform(cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4);
        perform(outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4);
    }
    
    //Close Streams
    inFile.close();
    outFile.close();
}

// enable user to input two positive huge integers from user
void inputTwoHugeInts(istream & inFile, int hugeInt1[], int hugeInt2[], int & size1, int & size2) {
    
    char numericString1[arraySize];
    char numericString2[arraySize];
    
    inFile >> numericString1 >> numericString2;
    
    size1 = strlen(numericString1);
    for (int i = 0; i < size1; ++i)
        hugeInt1[i] = numericString1[size1 - i - 1] - '0';
    
    size2 = strlen(numericString2);
    for (int i = 0; i < size2; ++i)
        hugeInt2[i] = numericString2[size2 - i - 1] - '0';
    
}

// perform addition, subtraction and multiplication
void perform(ostream & outFile, int hugeInt1[], int hugeInt2[], int hugeInt3[],
             int hugeInt4[], int size1, int size2, int size3, int size4) {
    
    //Output Test Case
    output(outFile, hugeInt1, size1);
    output(outFile, hugeInt2, size2);
    
    //Perform Addition
    addition(hugeInt1, hugeInt2, hugeInt3, size1, size2, size3);
    output(outFile, hugeInt3, size3);
    
    //Perform Substraction
    if (less(hugeInt1, hugeInt2, size1, size2)) {
        outFile << '-'; //Add Negetive Mark
        // hugeInt3 = hugeInt2 - hugeInt1
        subtraction(hugeInt2, hugeInt1, hugeInt3, size2, size1, size3);
        output(outFile, hugeInt3, size3);
    } else {
        // hugeInt3 = hugeInt1 - hugeInt2
        subtraction(hugeInt1, hugeInt2, hugeInt3, size1, size2, size3);
        output(outFile, hugeInt3, size3);
    }
    
    //Perform Multiplication
    multiplication(hugeInt1, hugeInt2, hugeInt3, size1, size2, size3);
    output(outFile, hugeInt3, size3);
    
    //Perform Division
    if (isZero(hugeInt2, size2)) {
        outFile << "DivideByZero!\n";
        outFile << "DivideByZero!\n";
    } else {
        division(hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4);
        output(outFile, hugeInt3, size3); // outputs n1 / n2
        output(outFile, hugeInt4, size4); // outputs n1 % n2
    }
    
    outFile << endl;
}

void output(ostream & outFile, int hugeInt[], int size) {
    if (isZero(hugeInt, size))
        outFile << 0;
    else
        for (int i = size - 1; i >= 0; i--)
            outFile << hugeInt[i];
    
    outFile << endl;
}

bool isZero(int hugeInt[], int size) {
    for (int i = 0; i < size; i++) {
        if (hugeInt[i] != 0) {
            return false;
        }
    }
    return true;
}

bool equal(int hugeInt1[], int hugeInt2[], int size1, int size2) {
    if (size1 != size2) {
        return false;
    }
    else {
        for (int i = 0; i < size1; i++) {
            if (hugeInt1[i] != hugeInt2[i]) {
                return false;
            }
        }
    }
    return true;
}

bool less(int hugeInt1[], int hugeInt2[], int size1, int size2) {
    if (size1 < size2) {
        return true;
    } else if (size1 > size2) {
        return false;
    } else if (size1 == size2) {
        for (int i = size1 - 1; i >= 0; i--) {
            if (hugeInt1[i] < hugeInt2[i]) {
                return true;
            } else if (hugeInt1[i] > hugeInt2[i]) {
                return false;
            }
        }
    }
    return false;
}

void addition(int addend[], int adder[], int sum[],
              int addendSize, int adderSize, int & sumSize) {
    
    int Cal, faddend, fadder;
    sumSize = (addendSize >= adderSize) ? addendSize+1 : adderSize+1;
    std::fill_n(sum, sumSize, 0);
    
    for (int i=0; i<sumSize; i++) {
        faddend = (i < addendSize) ? addend[i] : 0;
        fadder = (i < adderSize) ? adder[i] : 0;
        Cal = sum[i] + faddend + fadder;
        sum[i] = Cal%10;
        sum[i+1] += Cal/10;
        sumSize = (i == sumSize-1 && sum[i] == 0) ? sumSize-1 : sumSize;
    }
    
}

void subtraction(int minuend[], int subtrahend[], int difference[],
                 int minuendSize, int subtrahendSize, int & differenceSize) {
    
    int TempFuture=0, Cal, fsubtrahend;
    
    //Do Substraction
    for (int i = 0; i < minuendSize; i++) {
        fsubtrahend = (i < subtrahendSize) ? subtrahend[i] : 0;
        Cal = minuend[i] - fsubtrahend + TempFuture;
        difference[i] = (Cal >= 0) ? Cal : Cal+10;
        TempFuture = (Cal >= 0) ? 0 : -1;
    }
    
    //Size Calibration
    for (int i=minuendSize-1; i>=0; i--) {
        if (difference[i] != 0) {
            differenceSize = i+1;
            break;
        }
        if (i == 0) {
            differenceSize = 1;
        }
    }
    
}

void multiplication(int multiplicand[], int multiplier[], int product[],
                    int multiplicandSize, int multiplierSize, int & productSize) {
    
    //Setting Default Product then Cleaning
    productSize = multiplicandSize + multiplierSize;
    std::fill_n(product, productSize, 0);
    
    //Double-Loop Calculate Each Digits
    for (int i = 0; i < multiplierSize; i++) {
        for (int k = 0; k < multiplicandSize; k++) {
            product[i + k] += multiplicand[k] * multiplier[i];
        }
    }
    
    //Carry-Onnnnnn
    for (int i = 0; i < productSize; i++) {
        if (product[i] >= 10) {
            product[i+1] += product[i]/10;
            product[i] %= 10;
        }
    }
    
    //Size Calibration
    if (product[productSize-1] == 0) {
        productSize--;
    }
    
}

void division(int dividend[], int divisor[], int quotient[], int remainder[],
              int dividendSize, int divisorSize, int & quotientSize, int & remainderSize) {
    
    //Set Default QuotientSize & RemainderSize
    quotientSize = dividendSize - divisorSize;
    remainderSize = dividendSize;
    for (int i = 0; i < dividendSize; i++) {
        remainder[i] = dividend[i];
    }
    
    //Create Buffer
    int bufferSize = dividendSize;
    int buffer[200];
    int Shift = dividendSize - divisorSize;
    for (int i = 0; i < bufferSize; i++) {
        buffer[i] = (i >= Shift) ? divisor[i - Shift] : 0;
    }
    
    //Buffer Calibration & Quotient Cleaning
    if (less(dividend, buffer, dividendSize, bufferSize)) {
        divideBy10(buffer, bufferSize);
    } else {
        quotientSize++;
    }
    std::fill_n(quotient, quotientSize, 0);
    
    //Calculate Remainder One Unit at One Time
    for (int k = quotientSize - 1; k >= 0; k--) {
        while (less(buffer, remainder, bufferSize, remainderSize) || equal(buffer, remainder, bufferSize, remainderSize)) {
            subtraction(remainder, buffer, remainder, remainderSize, bufferSize, remainderSize);
            quotient[k]++;
        }
        divideBy10(buffer, bufferSize);
    }
    
}

// hugeInt /= 10
void divideBy10(int hugeInt[], int & size) {
    if (size == 1)
        hugeInt[0] = 0;
    else {
        for (int i = 1; i < size; i++) {
            hugeInt[i - 1] = hugeInt[i];
        }
        size--;
        hugeInt[size] = 0;
    }
}

