// Huge integer division
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;
using std::istream;
using std::ofstream;
using std::ostream;

// enable user to input two positive huge integers from user
void inputTwoHugeInts(istream &inFile, unsigned int hugeInt1[],
                      unsigned int hugeInt2[], unsigned int &size1,
                      unsigned int &size2);

// perform addition, subtraction, multiplication and division
void perform(ostream &outFile, unsigned int hugeInt1[], unsigned int hugeInt2[],
             unsigned int hugeInt3[], unsigned int hugeInt4[],
             unsigned int size1, unsigned int size2, unsigned int size3,
             unsigned int size4);

// output the specified huge integer
void output(ostream &outFile, unsigned int hugeInt[], unsigned int size);

// returns true if and only if the specified huge integer is zero
bool isZero(unsigned int hugeInt[], unsigned int size);

// returns true if and only if hugeInt1 < hugeInt2
bool less(unsigned int hugeInt1[], unsigned int hugeInt2[], unsigned int size1,
          unsigned int size2);

// quotient = dividend / divisor; remainder = dividend % divisor
void division(unsigned int dividend[], unsigned int divisor[],
              unsigned int quotient[], unsigned int remainder[],
              unsigned int dividendSize, unsigned int divisorSize,
              unsigned int &quotientSize, unsigned int &remainderSize);

// product = multiplicand * multiplier * ( 10 ^ multiplierPos )
void multiplication(unsigned int multiplicand[], unsigned int multiplier,
                    unsigned int product[], unsigned int multiplicandSize,
                    unsigned int multiplierPos, unsigned int &productSize);

// minuend -= subtrahend
void subtraction(unsigned int minuend[], unsigned int subtrahend[],
                 unsigned int &minuendSize, unsigned int subtrahendSize);

const unsigned int numTestCases = 22; // the number of test cases
const unsigned int arraySize = 200;

unsigned int main() {
  system("mode con cols=122");

  ifstream inFile("Test cases.txt", ios::in);

  // exit program if ofstream could not open file
  if (!inFile) {
    cout << "File could not be opened" << endl;
    system("pause");
    exit(1);
  }

  ofstream outFile("Result.txt", ios::out);

  // exit program if ofstream could not open file
  if (!outFile) {
    cout << "File could not be opened" << endl;
    system("pause");
    exit(1);
  }

  for (unsigned int i = 0; i < numTestCases; i++) {
    unsigned int hugeInt1[arraySize] = {};
    unsigned int hugeInt2[arraySize] = {};
    unsigned int hugeInt3[arraySize] = {};
    unsigned int hugeInt4[arraySize] = {};
    unsigned int size1 = 0;
    unsigned int size2 = 0;
    unsigned int size3 = 0;
    unsigned int size4 = 0;

    inputTwoHugeInts(inFile, hugeInt1, hugeInt2, size1, size2);
    perform(cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3,
            size4);
    perform(outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2,
            size3, size4);
  }

  inFile.close();
  outFile.close();

  system("pause");
}

// enable user to input two positive huge integers from user
void inputTwoHugeInts(istream &inFile, unsigned int hugeInt1[],
                      unsigned int hugeInt2[], unsigned int &size1,
                      unsigned int &size2) {
  char numericString1[arraySize];
  char numericString2[arraySize];

  inFile >> numericString1 >> numericString2;

  size1 = strlen(numericString1);
  for (unsigned int i = 0; i < size1; ++i)
    hugeInt1[i] = numericString1[size1 - i - 1] - '0';

  size2 = strlen(numericString2);
  for (unsigned int i = 0; i < size2; ++i)
    hugeInt2[i] = numericString2[size2 - i - 1] - '0';
}

// perform addition, subtraction and multiplication
void perform(ostream &outFile, unsigned int hugeInt1[], unsigned int hugeInt2[],
             unsigned int hugeInt3[], unsigned int hugeInt4[],
             unsigned int size1, unsigned int size2, unsigned int size3,
             unsigned int size4) {
  output(outFile, hugeInt1, size1);
  output(outFile, hugeInt2, size2);

  if (isZero(hugeInt2, size2)) {
    outFile << "DivideByZero!\n";
    outFile << "DivideByZero!\n";
  } else {
    division(hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3,
             size4);
    output(outFile, hugeInt3, size3); // outputs n1 / n2
    output(outFile, hugeInt4, size4); // outputs n1 % n2
  }

  outFile << endl;
}

// output the specified huge integer
void output(ostream &outFile, unsigned int hugeInt[], unsigned int size) {
  if (isZero(hugeInt, size))
    outFile << 0;
  else
    for (int i = size - 1; i >= 0; i--)
      outFile << hugeInt[i];

  outFile << endl;
}

// returns true if and only if the specified huge integer is zero
bool isZero(unsigned int hugeInt[], unsigned int size) {
  for (unsigned int i = 0; i < size; i++)
    if (hugeInt[i] != 0)
      return false;
  return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less(unsigned int hugeInt1[], unsigned int hugeInt2[], unsigned int size1,
          unsigned int size2) {
  if (size1 > size2) {
    return false;
  }
  if (size1 < size2) {
    return true;
  }
  if (size1 == size2) {
    for (int i = size1 - 1; i >= 0; i--) {
      if (hugeInt1[i] < hugeInt2[i]) {
        return true;
      }
      if (hugeInt1[i] > hugeInt2[i]) {
        return false;
      }
    }
    return false;
  }
}

void division(unsigned int dividend[], unsigned int divisor[],
              unsigned int quotient[], unsigned int remainder[],
              unsigned int dividendSize, unsigned int divisorSize,
              unsigned int &quotientSize, unsigned int &remainderSize) {
  if (isZero(dividend, dividendSize)) {
    quotientSize = 1;
    quotient[0] = 0;
    remainderSize = 1;
    remainder[0] = 0;
    return;
  }

  remainderSize = dividendSize;
  for (int i = 0; i < dividendSize; i++) {
    remainder[i] = dividend[i];
  }

  if (less(remainder, divisor, remainderSize, divisorSize)) {
    quotientSize = 1;
    quotient = 0;
  }

  else {
    // Make Buffer
    int n = dividendSize - divisorSize;
    unsigned int buffer[200];
    for (int i = 0; i < divisorSize; i++) {
      buffer[i + n] = divisor[i];
    }
    for (int i = 0; i < n; i++) {
      buffer[i] = 0;
    }
    unsigned int bufferSize = divisorSize + n;

    // Cal
    quotientSize = dividendSize - divisorSize;
    if (!less(dividend, buffer, dividendSize, bufferSize)) {
      quotientSize++;
    }
    for (int i = 0; i < quotientSize; i++) {
      quotient[i] = 0;
    }
    int a = divisor[divisorSize - 1];
    int j = dividendSize - 1;
    for (int i = dividendSize - divisorSize; i >= 0; i--, j--) {
      int b = 10 * remainder[j + 1] + remainder[j];
      if (a <= b) {
        quotient[i] = b / a;
        multiplication(divisor, quotient[i], buffer, divisorSize, i,
                       bufferSize);
        while (less(remainder, buffer, remainderSize, bufferSize)) {
          quotient[i]--;
          multiplication(divisor, quotient[i], buffer, divisorSize, i,
                         bufferSize);
        }
        subtraction(remainder, buffer, remainderSize, bufferSize);
        // system("pause");
      }
    }
  }
}

void multiplication(unsigned int multiplicand[], unsigned int multiplier,
                    unsigned int product[], unsigned int multiplicandSize,
                    unsigned int multiplierPos, unsigned int &productSize) {

  for (int i = 0; i < productSize; i++) {
    product[i] = 0;
  }

  productSize = multiplicandSize;

  for (int i = 0; i < productSize; i++) {
    product[i] = 0;
  }

  for (unsigned int i = 0; i < multiplicandSize; i++) {
    product[i] = multiplicand[i] * multiplier;
  }

  if (product[productSize - 1] >= 10) {
    product[productSize] = 0;
    productSize++;
  }

  for (unsigned int i = 0; i < productSize; i++) {
    while (product[i] >= 10) {
      product[i] -= 10;
      product[i + 1]++;
    }
  }

  for (unsigned int i = productSize - 1; i > 0; i--) {
    product[i + multiplierPos] = product[i];
  }
  product[multiplierPos] = product[0];
  for (unsigned int i = 0; i < multiplierPos; i++) {
    product[i] = 0;
    productSize++;
  }
}

void subtraction(unsigned int minuend[], unsigned int subtrahend[],
                 unsigned int &minuendSize, unsigned int subtrahendSize) {
  if (minuendSize != subtrahendSize) {
    for (unsigned int k = subtrahendSize; k < minuendSize; k++) {
      subtrahend[k] == 0;
    }
    subtrahendSize = minuendSize;
  }

  for (unsigned int i = 0; i < minuendSize; i++) {
    if (minuend[i] < subtrahend[i]) {
      minuend[i] += 10;
      for (int j = 1; j < minuendSize; j++) {
        if (minuend[i + j] > 0) {
          minuend[i + j]--;
          break;
        } else {
          minuend[i + j] = 9;
        }
      }
    }
  }

  for (unsigned int i = 0; i < minuendSize; i++) {
    minuend[i] -= subtrahend[i];
  }

  while (!isZero(minuend, minuendSize) && minuend[minuendSize - 1] == 0) {
    minuendSize--;
  }
}