//
//  main.cpp
//  Hw5-2 (Functed)
//  Huge integer addition, subtraction, multiplication and division
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
    
    ifstream inFile("Test cases.txt", ios:: in );
    
    // exit program if ofstream could not open file
    if (!inFile) {
        cout << "File could not be opened" << endl;
        exit(1);
    }
    
    ofstream outFile("Result.txt", ios::out);
    
    // exit program if ofstream could not open file
    if (!outFile) {
        cout << "File could not be opened" << endl;
        exit(1);
    }
    
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
    
    output(outFile, hugeInt1, size1);
    output(outFile, hugeInt2, size2);
    
    // hugeInt3 = hugeInt1 + hugeInt2
    addition(hugeInt1, hugeInt2, hugeInt3, size1, size2, size3);
    output(outFile, hugeInt3, size3);
    
    // if hugeInt1 < hugeInt2
    if (less(hugeInt1, hugeInt2, size1, size2)) {
        outFile << '-';
        // hugeInt3 = hugeInt2 - hugeInt1
        subtraction(hugeInt2, hugeInt1, hugeInt3, size2, size1, size3);
        output(outFile, hugeInt3, size3); // outputs n2 - n1
    } else {
        // hugeInt3 = hugeInt1 - hugeInt2
        subtraction(hugeInt1, hugeInt2, hugeInt3, size1, size2, size3);
        output(outFile, hugeInt3, size3); // outputs n1 - n2
    }
    
    // hugeInt3 = hugeInt1 * hugeInt2
    multiplication(hugeInt1, hugeInt2, hugeInt3, size1, size2, size3);
    output(outFile, hugeInt3, size3); // outputs n1 * n2
    
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

// output the specified huge integer
void output(ostream & outFile, int hugeInt[], int size) {
    if (isZero(hugeInt, size))
        outFile << 0;
    else
        for (int i = size - 1; i >= 0; i--)
            outFile << hugeInt[i];
    
    outFile << endl;
}

// returns true if and only if the specified huge integer is zero
bool isZero(int hugeInt[], int size) {
    for (int i = 0; i < size; i++)
        if (hugeInt[i] != 0)
            return false;
    return true;
}

// return true if and only if hugeInt1 == hugeInt2
bool equal(int hugeInt1[], int hugeInt2[], int size1, int size2) {
    
    if (size1 != size2) {
        return false;
    }
    else if (size1 == size2) {
        for (int i = 0; i < size1; i++) {
            if (hugeInt1[i] != hugeInt2[i]) {
                return false;
            }
        }
    }
    return true;
    
}

// returns true if and only if hugeInt1 < hugeInt2
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

// sum = addend + adder
void addition(int addend[], int adder[], int sum[],
              int addendSize, int adderSize, int & sumSize) {
    
    sumSize = (addendSize >= adderSize) ? addendSize + 1 : adderSize + 1;
    
    for (int i = 0; i < addendSize; i++) {
        sum[i] = addend[i];
    }
    for (int i = addendSize; i < sumSize; i++) {
        sum[i] = 0;
    }
    for (int i = 0; i < adderSize; i++) {
        sum[i] += adder[i];
    }
    for (int i = 0; i < sumSize - 1; i++) {
        if (sum[i] > 9) {
            sum[i] -= 10;
            sum[i + 1]++;
        }
    }
    if (sum[sumSize - 1] == 0) {
        sumSize--;
    }
}

// difference = minuend - subtrahend
void subtraction(int minuend[], int subtrahend[], int difference[],
                 int minuendSize, int subtrahendSize, int & differenceSize) {
    
    //Presume the maximium Lens of Difference
    differenceSize = minuendSize;
    
    //Fill Array with 0
    for (int i = 0; i < differenceSize; i++) {
        difference[i] = 0;
    }
    
    if (minuendSize > subtrahendSize) { //If Minuend has Greater Size
        
        //Calcuate Correspond Digits
        for (int i = 0; i < subtrahendSize; i++) {
            difference[i] = minuend[i] - subtrahend[i];
        }
        
        //Calculate the Rest Digits
        for (int i = subtrahendSize; i < minuendSize; i++) {
            difference[i] = minuend[i];
        }
        
    } else { //If Sizes are same
        
        //Calculate all Digits
        for (int i = 0; i < subtrahendSize; i++) {
            difference[i] = minuend[i] - subtrahend[i];
        }
        
    }
    
    //Deal with Negatives
    for (int i = 0; i < differenceSize - 1; i++) {
        if (difference[i] < 0) {
            difference[i] += 10;
            difference[i + 1]--;
        }
    }
    
    //Recalculate Difference Size
    while (difference[differenceSize - 1] == 0) {
        differenceSize--;
    }
    
}

// product = multiplicand * multiplier
void multiplication(int multiplicand[], int multiplier[], int product[],
                    int multiplicandSize, int multiplierSize, int & productSize) {
    
    //Presume the maximium Lens of Product
    productSize = multiplicandSize + multiplierSize;
    
    //Fill Array with 0
    for (int i = 0; i < productSize; i++) {
        
        product[i] = 0;
        
    }
    
    //Double-Loop Calculate Each Digits
    for (int i = 0; i < multiplierSize; i++) {
        for (int k = 0; k < multiplicandSize; k++) {
            product[i + k] += multiplicand[k] * multiplier[i];
        }
    }
    
    //Carry-Onnnnnn
    for (int i = 0; i < productSize; i++) {
        if (product[i] >= 10) {
            product[i + 1] += product[i] / 10;
            product[i] = product[i] % 10;
        }
    }
    
    //Recalculate Product Size
    while (product[productSize - 1] == 0) {
        productSize--;
    }
    
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int dividend[], int divisor[], int quotient[], int remainder[],
              int dividendSize, int divisorSize, int & quotientSize, int & remainderSize) {
    
    //If Dividend == 0
    if (isZero(dividend, dividendSize)) {
        quotientSize = 1;
        remainderSize = 1;
        quotient[0] = 0;
        remainder[0] = 0;
        return;
    }
    
    //Set Default Remainder to Divisor
    remainderSize = dividendSize;
    for (int i = 0; i < dividendSize; i++) {
        remainder[i] = dividend[i];
    }
    
    //If Dividend < Divisor
    if (less(dividend, divisor, dividendSize, divisorSize)) {
        quotientSize = 1;
        quotient[0] = 0;
    } else {
        
        //Calculate Divisor Shift Unit
        int n = dividendSize - divisorSize;
        
        //Create Buffer
        int bufferSize = dividendSize;
        int * buffer = new int[bufferSize - 1];
        for (int i = 0; i < n; i++) {
            buffer[i] = 0;
        }
        for (int i = n; i < bufferSize; i++) {
            buffer[i] = divisor[i - n];
        }
        
        //Setting Default Quotient Size
        quotientSize = dividendSize - divisorSize;
        
        //If Dividend < Buffer
        if (less(dividend, buffer, dividendSize, bufferSize)) {
            
            //Shift Buffer if Buffer is Too Big
            divideBy10(buffer, bufferSize);
            
        } else {
            
            //Calculate New Quotient Size
            quotientSize++;
            
        }
        
        //Set Quotient to Zero
        for (int i = 0; i < quotientSize; i++) {
            quotient[i] = 0;
        }
        
        //Calculate Remainder One Unit at One Time
        for (int k = quotientSize - 1; k >= 0; k--) {
            
            //While Buffer <= Remainder
            while (less(buffer, remainder, bufferSize, remainderSize) || equal(buffer, remainder, bufferSize, remainderSize)) {
                
                //Calculate Unit Remainder
                for (int i = bufferSize - 1; i >= 0; i--) {
                    remainder[i] = remainder[i] - buffer[i];
                }
                for (int i = 0; i < remainderSize - 1; i++) {
                    if (remainder[i] < 0) {
                        remainder[i] += 10;
                        remainder[i + 1]--;
                    }
                }
                
                //Calculate New Remainder Size
                while (remainder[remainderSize - 1] == 0) {
                    remainderSize--;
                }
                
                //Calculate Unit Quotient
                quotient[k]++;
                
                //If Remainder == 0
                if (isZero(remainder, remainderSize)) {
                    return;
                }
                
            }
            
            //Shift Buffer for Next Calculation
            divideBy10(buffer, bufferSize);
            
        }
    }
    
}

// hugeInt /= 10
void divideBy10(int hugeInt[], int & size) {
    if (size == 1)
        hugeInt[0] = 0;
    else {
        for (int i = 1; i < size; i++)
            hugeInt[i - 1] = hugeInt[i];
        
        size--;
        hugeInt[size] = 0;
    }
}

