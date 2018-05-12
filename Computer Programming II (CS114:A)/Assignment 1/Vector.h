//
//  Vector.h
//  Hw1
//  Vector Test Program
//
//  Created by Tomy Hsieh on 2018/2/27.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <vector>

class vector
{
public:
    // Constructs a zero vector with size n.
    vector( unsigned int n = 0 );
    
    ~vector(); // Destroys the vector.
    
    // Returns the number of elements in the vector.
    // This is the number of actual objects held in the vector,
    // which is not necessarily equal to its storage capacity.
    unsigned int size();
    
    // Returns the size of the storage space currently allocated for the vector,
    // expressed in terms of elements.
    unsigned int capacity();
    
    // Adds a new element at the end of the vector, after its current last element.
    // The content of val is copied to the new element.
    // This effectively increases the vector size by one,
    // which causes an automatic reallocation of the allocated storage space
    // if and only if the new vector size surpasses the current vector capacity.
    void push_back( const int val );
    
    // Removes the last element in the vector,
    // effectively reducing the container size by one.
    void pop_back();
    
    // Resizes the vector so that it contains n elements.
    // If n is smaller than the current vector size,
    // the content is reduced to its first n elements, removing those beyond.
    // If n is greater than the current vector size,
    // the content is expanded by inserting at the end as many elements as needed to reach a size of n.
    // The new elements are initialized as 0.
    // If n is also greater than the current vector capacity,
    // an automatic reallocation of the allocated storage space takes place.
    void resize( unsigned int n );
    
    // Determines if two vectors are equal.
    bool equal( std::vector< int > &v );
    
private:
    int *myFirst = nullptr;
    int *myLast = nullptr;
    int *myEnd = nullptr;
};

#endif
