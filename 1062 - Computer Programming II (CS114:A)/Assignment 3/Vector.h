//
//  Vector.h
//  Hw3
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/3/13.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef VECTOR_H
#define VECTOR_H

class vector {
    //Equal To
//    friend bool equal( const vector &lhs, const vector &rhs );
public:
    using iterator = int*;

    //Constructor & Destructors
    vector(unsigned int n = 0);
    vector(const vector &x);
    ~vector();

    //Assignment Operator
    const vector &assign(const vector &x);

    //Pointers
    int* begin() const; // Shall NOT be dereferenced if vector is empty
    int* end() const; // Shall NOT be dereferenced under any Circumstances

    //Attributes
    unsigned int size() const;
    unsigned int capacity() const;
    
    //Some Gears
    void push_back(const int val);
    void pop_back();
    void resize(unsigned int n); // If n > size, new elements are 0
//    bool equal(std::vector< int > &v);

private:
    int *myFirst = nullptr;
    int *myLast = nullptr;
    int *myEnd = nullptr;
};

#endif
