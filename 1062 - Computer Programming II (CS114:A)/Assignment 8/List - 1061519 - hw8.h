//
//  List - 1061519 - hw8.h
//  Hw8
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/5/8.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef LIST___1061519___HW8_H
#define LIST___1061519___HW8_H

//   #                         #     #
//   #       #  ####  #####    ##    #  ####  #####  ######
//   #       # #        #      # #   # #    # #    # #
//   #       #  ####    #      #  #  # #    # #    # #####
//   #       #      #   #      #   # # #    # #    # #
//   #       # #    #   #      #    ## #    # #    # #
//   ####### #  ####    #      #     #  ####  #####  ######

template <typename T>
struct ListNode {
  ListNode *next;
  T myVal;
  ListNode *prev;
};

//   ###
//    #  ##### ###### #####
//    #    #   #      #    #
//    #    #   #####  #    #
//    #    #   #      #####
//    #    #   #      #   #
//   ###   #   ###### #    #

template <typename T>
class ListIterator {
public:
  ListIterator(ListNode<T> *p = nullptr) : ptr(p) {}
  ListIterator(const ListIterator &iteratorToCopy) : ptr(iteratorToCopy.ptr) {}
  ~ListIterator() {}

  bool operator==(const ListIterator &right) const { return ptr == right.ptr; }
  bool operator!=(const ListIterator &right) const { return ptr != right.ptr; }
  T &operator*() const { return ptr->myVal; }
  const ListIterator &operator=(const ListIterator &right) {
    if (&right != this) {
      ptr = right.ptr;
    }
    return *this;
  }

  ListIterator &operator++() {
    ptr = ptr->next;
    return *this;
  }
  ListIterator &operator--() {
    ptr = ptr->prev;
    return *this;
  }
  ListIterator operator++(int) {
    ListIterator tmp(*this);
    ptr = ptr->next;
    return tmp;
  }
  ListIterator operator--(int) {
    ListIterator tmp(*this);
    ptr = ptr->prev;
    return tmp;
  }

private:
  ListNode<T> *ptr = nullptr;
};

//   ######                   ###
//   #     # ###### #    #     #  ##### ###### #####
//   #     # #      #    #     #    #   #      #    #
//   ######  #####  #    #     #    #   #####  #    #
//   #   #   #      #    #     #    #   #      #####
//   #    #  #       #  #      #    #   #      #   #
//   #     # ######   ##      ###   #   ###### #    #

template <typename T>
class ReverseListIterator : public ListIterator<T> {
public:
  ReverseListIterator(ListNode<T> *p = nullptr) : ListIterator<T>(p) {}
  ReverseListIterator(const ReverseListIterator &iteratorToCopy) : ListIterator<T>(iteratorToCopy) {}
  ~ReverseListIterator() {}

//  T &operator*() const { return ptr->myVal; }
//  const ReverseListIterator &operator=(const ReverseListIterator &right) {
//    if (&right != this) {
//      ptr = right.ptr;
//    }
//    return *this;
//  }
  
  ReverseListIterator &operator++() {
    ListIterator<T>::operator--();
    return *this;
  }
  ReverseListIterator &operator--() {
    ListIterator<T>::operator++();
    return *this;
  }
  ReverseListIterator operator++(int) {
    ReverseListIterator tmp(*this);
    ListIterator<T>::operator--();
    return tmp;
  }
  ReverseListIterator operator--(int) {
    ReverseListIterator tmp(*this);
    ListIterator<T>::operator++();
    return tmp;
  }
};

//   #
//   #       #  ####  #####
//   #       # #        #
//   #       #  ####    #
//   #       #      #   #
//   #       # #    #   #
//   ####### #  ####    #

template <typename T>
class list {
  template <typename Tf>
  friend bool operator==(const list<Tf> &lhs, const list<Tf> &rhs);

  template <typename Tf>
  friend bool operator!=(const list<Tf> &lhs, const list<Tf> &rhs);

public:
  using iterator = ListIterator<T>;
  using reverse_iterator = ReverseListIterator<T>;

  list(unsigned int n = 0);
  list(const list &x) { *this = x; }
  ~list();

  list &operator=(const list &x);

  iterator begin() const { return iterator(myHead->next); }
  iterator end() const { return iterator(myHead); }
  reverse_iterator rbegin() const { return reverse_iterator(myHead->prev); }
  reverse_iterator rend() const { return reverse_iterator(myHead); }
  unsigned int size() const { return mySize; }

  void resize(unsigned int n);
  void push_front(const T val);
  void push_back(const T val);
  void pop_back();
  void clear();

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

template <typename T>
list<T>::list(unsigned int n) {
  myHead = new ListNode<T>;
  myHead->myVal = T();
  myHead->prev = myHead->next = myHead;
  for (unsigned int i = 0; i < n; i++) {
    push_back(T());
  }
}

template <typename T>
list<T>::~list() {
  clear();
  delete myHead;
}

template <typename T>
list<T> &list<T>::operator=(const list &x) {
  clear();
  delete myHead;
  myHead = new ListNode<T>;
  myHead->myVal = T();
  myHead->prev = myHead->next = myHead;
  for (iterator it = x.begin(); it != x.end(); it++) {
    push_back(*it);
  }
  return *this;
}

template <typename T>
void list<T>::resize(unsigned int n) {
  size_t difference = (n > mySize) ? n - mySize : mySize - n;
  for (size_t i = 0; i < difference; i++) {
    if (n > mySize) {
      push_back(T());
    } else if (n < mySize) {
      pop_back();
    }
  }
}

template <typename T>
void list<T>::push_front(const T val) {
  myHead->next->prev = new ListNode<T>;
  myHead->next->prev->myVal = val;
  myHead->next->prev->next = myHead->next;
  myHead->next->prev->prev = myHead;
  myHead->next = myHead->next->prev;
  mySize++;
}
template <typename T>
void list<T>::push_back(const T val) {
  myHead->prev->next = new ListNode<T>;
  myHead->prev->next->myVal = val;
  myHead->prev->next->prev = myHead->prev;
  myHead->prev->next->next = myHead;
  myHead->prev = myHead->prev->next;
  mySize++;
}

template <typename T>
void list<T>::pop_back() {
  if (myHead->prev != myHead) {
    myHead->prev = myHead->prev->prev;
    delete myHead->prev->next;
    myHead->prev->next = myHead;
    mySize--;
  }
}

template <typename T>
void list<T>::clear() {
  while (mySize > 0) {
    pop_back();
  }
}

template <typename T>
bool operator==(const list<T> &lhs, const list<T> &rhs) {
  if (lhs.mySize != rhs.mySize) {
    return false;
  }
  typename list<T>::iterator it1 = lhs.begin();
  typename list<T>::iterator it2 = rhs.begin();
  for (; it1 != lhs.end() && it2 != rhs.end(); it1++, it2++) {
    if (*it1 != *it2) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool operator!=(const list<T> &lhs, const list<T> &rhs) {
  return !(lhs == rhs);
}

#endif
