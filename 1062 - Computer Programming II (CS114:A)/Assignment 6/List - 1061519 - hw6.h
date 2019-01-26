//
//  List - 1061519 - hw6.h
//  Hw6
//  List Test Program
//
//  Created by Tomy Hsieh on 2018/4/9.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef LIST___1061519___HW6_H
#define LIST___1061519___HW6_H

#include <list>
template <typename T> struct ListNode;
template <typename T> class list;

template <typename T> struct ListNode {
  template <typename Tf>
  friend void printList(list<Tf> &theList, std::list<Tf> &theSTLList);
  ListNode *prev;
  T myVal;
  ListNode *next;
};

template <typename T> class list {
  template <typename Tf>
  friend void printList(list<Tf> &theList, std::list<Tf> &theSTLList);
  
public:
  // Constructors & Destructors
  list();
  list(unsigned int n);
  ~list();
  
  // Attributes
  unsigned int size() const;
  
  // Some Gears
  void push_front(const T val);
  void push_back(const T val);
  void pop_back();
  void resize(unsigned int n);
  void clear();
  bool equal(std::list<T> &stdList);
  
private:
  unsigned int mySize = 0;
  ListNode<T> *myHead = nullptr;
};

//   #######
//   #       #    # #    #  ####  ##### #  ####  #    #  ####
//   #       #    # ##   # #    #   #   # #    # ##   # #
//   #####   #    # # #  # #        #   # #    # # #  #  ####
//   #       #    # #  # # #        #   # #    # #  # #      #
//   #       #    # #   ## #    #   #   # #    # #   ## #    #
//   #        ####  #    #  ####    #   #  ####  #    #  ####

template <typename T> list<T>::list() {
  myHead = new ListNode<T>;
  myHead->myVal = T();
  myHead->prev = myHead->next = myHead;
}

template <typename T> list<T>::list(unsigned int n) {
  myHead = new ListNode<T>;
  myHead->myVal = T();
  myHead->prev = myHead->next = myHead;
  for (unsigned int i = 0; i < n; i++) {
    push_back(T());
  }
}

template <typename T> list<T>::~list() {
  clear();
  delete myHead;
}

template <typename T> unsigned int list<T>::size() const { return mySize; }

template <typename T> void list<T>::push_front(const T val) {
  myHead->next->prev = new ListNode<T>;
  myHead->next->prev->myVal = val;
  myHead->next->prev->next = myHead->next;
  myHead->next->prev->prev = myHead;
  myHead->next = myHead->next->prev;
  mySize++;
}

template <typename T> void list<T>::push_back(const T val) {
  myHead->prev->next = new ListNode<T>;
  myHead->prev->next->myVal = val;
  myHead->prev->next->prev = myHead->prev;
  myHead->prev->next->next = myHead;
  myHead->prev = myHead->prev->next;
  mySize++;
}

template <typename T> void list<T>::pop_back() {
  if (myHead->prev != myHead) {
    myHead->prev = myHead->prev->prev;
    delete myHead->prev->next;
    myHead->prev->next = myHead;
    mySize--;
  }
}

template <typename T> void list<T>::resize(unsigned int n) {
  unsigned int difference = (n > mySize) ? n - mySize : mySize - n;
  for (unsigned int i = 0; i < difference; i++) {
    if (n > mySize) {
      push_back(T());
    } else if (n < mySize) {
      pop_back();
    }
  }
}

template <typename T> void list<T>::clear() {
  while (mySize > 0) {
    pop_back();
  }
}

template <typename T> bool list<T>::equal(std::list<T> &stdList) {
  if (mySize != stdList.size()) {
    return false;
  }
  
  ListNode<T> *ptr = myHead->next;
  typename std::list<T>::iterator it = stdList.begin();
  for (; ptr != myHead && it != stdList.end(); ptr = ptr->next, ++it) {
    if (ptr->myVal != *it) {
      return false;
    }
  }
  return true;
}

#endif

