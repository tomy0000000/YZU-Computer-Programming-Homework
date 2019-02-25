//
//  Deque.h
//  Hw1
//  Self Build Deque
//
//  Created by Tomy Hsieh on 2018/9/12.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef DEQUE_H
#define DEQUE_H

template <typename T>
class deque;

//   ###
//    #  ##### ###### #####
//    #    #   #      #    #
//    #    #   #####  #    #
//    #    #   #      #####
//    #    #   #      #   #
//   ###   #   ###### #    #

// DequeIterator class template definition
template <typename T>
class DequeIterator {
  template <typename Tf>
  friend class deque;

public:
  DequeIterator() {}

  DequeIterator(deque<T> *container, unsigned int offset)
      : myCont(container), myOff(offset) {}

  DequeIterator(const DequeIterator &iteratorToCopy)
      : myCont(iteratorToCopy.myCont), myOff(iteratorToCopy.myOff) {}

  ~DequeIterator() {}

  // const return avoids: ( a1 = a2 ) = a3
  const DequeIterator &operator=(const DequeIterator &right) {
    if (&right != this) // avoid self-assignment
    {
      myCont = right.myCont;
      myOff  = right.myOff;
    }
    return *this; // enables x = y = z, for example
  }

  T &operator*() const {
    unsigned int block = (myOff % (4 * myCont->mapSize)) / 4;
    unsigned int off   = myOff % 4;
    return (myCont->map)[block][off];
  }

  DequeIterator &operator++() {
    ++myOff;
    return *this;
  }

  bool operator==(const DequeIterator &right) const {
    return (myCont == right.myCont) && (myOff == right.myOff);
  }
  bool operator!=(const DequeIterator &right) const {
    return (myCont != right.myCont) || (myOff != right.myOff);
  }
  bool operator<(const DequeIterator &right) const {
    return (myCont == right.myCont) && (myOff < right.myOff);
  }
  bool operator<=(const DequeIterator &right) const {
    return (myCont == right.myCont) && (myOff <= right.myOff);
  }
  DequeIterator operator+(unsigned int i) {
    return DequeIterator(myCont, myOff + i);
  }
  DequeIterator operator-(unsigned int i) {
    return DequeIterator(myCont, myOff - i);
  }

private:
  deque<T> *myCont   = nullptr; // keep a pointer to deque
  unsigned int myOff = 0;       // offset of element in deque
};                              // end class template DequeIterator

//
//   #####  ######  ####  #    # ######
//   #    # #      #    # #    # #
//   #    # #####  #    # #    # #####
//   #    # #      #  # # #    # #
//   #    # #      #   #  #    # #
//   #####  ######  ### #  ####  ######

// deque class template definition
template <typename T>
class deque {

  // Friends
  template <typename Tf>
  friend class DequeIterator;
  template <typename Tf>
  friend bool operator==(const deque<Tf> &lhs, const deque<Tf> &rhs);
  template <typename Tf>
  friend bool operator!=(const deque<Tf> &lhs, const deque<Tf> &rhs);

public:
  using iterator = DequeIterator<T>;

  // Constructors & Destructors
  deque();
  deque(unsigned int n, const T &val);
  ~deque();

  // Returns an iterator pointing to the first element in the deque container.
  // If the deque is empty, the returned iterator shall not be dereferenced.
  iterator begin() {
    return iterator(this, myOff);
  }

  // Returns an iterator referring to the past-the-end element in the deque
  // container. The past-the-end element is the theoretical element that would
  // follow the last element in the deque container. It does not point to any
  // element, and thus shall not be dereferenced.
  iterator end() {
    return iterator(this, myOff + mySize);
  }

  // Returns the number of elements in the deque container.
  unsigned int size() const {
    return mySize;
  }

  // The deque container is extended by inserting a new element
  // before the element at the specified position.
  // This effectively increases the container size by one.
  void insert(const iterator position, const T &val);

  // Removes from the deque container a single element at the specified
  // position. This effectively reduces the container size by one.
  void erase(const iterator position);

private:
  T **map              = nullptr; // pointer to array of pointers to blocks
  unsigned int mapSize = 0;       // size of map array, zero or 2^N
  unsigned int myOff   = 0;       // offset of initial element
  unsigned int mySize  = 0;       // current length of sequence

  void doubleMapSize(); // double the size of map array without changing myOff
                        // and mySize
  int fix_index(int index);
  int fix_map(int map_index);
  int fix_block(int block_index);;
};

//   #######
//   #       #    # #    #  ####   ####
//   #       #    # ##   # #    # #
//   #####   #    # # #  # #       ####
//   #       #    # #  # # #           #
//   #       #    # #   ## #    # #    #
//   #        ####  #    #  ####   ####

template <typename T>
deque<T>::deque() : map(nullptr), mapSize(0), myOff(0), mySize(0) {}

template <typename T>
deque<T>::deque(unsigned int n, const T &val) : myOff(0), mySize(n) {
  if (n == 0) {
    map     = nullptr;
    mapSize = 0;
  } else {
    mapSize = 8;
    while (n > 4 * (mapSize - 1)) { mapSize *= 2; }
    map = new T *[mapSize]();
    for (unsigned int i = 0; i <= (n - 1) / 4; i++) { map[i] = new T[4]; }
    for (unsigned int i = 0; i < n; i++) { map[i / 4][i % 4] = val; }
  }
}

template <typename T>
deque<T>::~deque() {
  if (mapSize > 0) {
    for (unsigned int i = 0; i < mapSize; i++) {
      if (map[i] != nullptr) { delete[] map[i]; }
    }
    delete[] map;
  }
}

template <typename T>
void deque<T>::insert(const iterator position, const T &val) {

  // Init
  int item_to_move_forward = position.myOff - myOff;
  int item_to_move_back    = myOff + mySize - position.myOff;
  bool f_or_b              = item_to_move_forward <= item_to_move_back;
  int count = (f_or_b) ? item_to_move_forward : item_to_move_back;
  int head  = (f_or_b) ? myOff : (myOff + mySize);
  int index = position.myOff;

  // Check Map
  if (map == nullptr) {
    mapSize = 8;
    map     = new T *[mapSize]();
  }
  if ((head % 4 == 0) && (mySize >= (mapSize - 1) * 4)) { doubleMapSize(); }

  // Move-It Move-It!
  for (int i = 0; i < count; i++) {
    int item_index = (f_or_b) ? myOff + i : myOff + mySize - i - 1;
    item_index     = fix_index(item_index);
    int old_row    = item_index / 4;
    int old_col    = item_index % 4;
    int new_row    = old_row;
    int new_col    = (f_or_b) ? old_col - 1 : old_col + 1;
    if (new_col < 0) {
      new_row--;
      new_col = 3;
    } else if (new_col > 3) {
      new_row++;
      new_col = 0;
    }
    new_row = fix_map(new_row);
    if (!map[new_row]) { map[new_row] = new T[4]; }
    map[new_row][new_col] = map[old_row][old_col];
  }

  // Operation for Insertion at Front
  if (f_or_b) {
    index--;
    myOff = (myOff == 0) ? mapSize * 4 - 1 : myOff - 1;
  }

  // Clean Up
  index = fix_index(index);
  myOff = fix_index(myOff);
  mySize++;

  // Finally Place-In
  if (!map[index / 4]) { map[index / 4] = new T[4]; }
  map[index / 4][index % 4] = val;
}

template <typename T>
void deque<T>::erase(const iterator position) {

  // Init
  int item_to_move_back    = position.myOff - myOff;
  int item_to_move_forward = myOff + mySize - position.myOff - 1;
  bool f_or_b              = item_to_move_forward <= item_to_move_back;
  int count = (f_or_b) ? item_to_move_forward : item_to_move_back;

  // Move-It Move-It!
  for (int i = 0; i < count; i++) {
    int item_index = (f_or_b) ? position.myOff + i + 1 : position.myOff - 1 - i;
    item_index     = fix_index(item_index);
    int old_row    = item_index / 4;
    int old_col    = item_index % 4;
    int new_row    = old_row;
    int new_col    = (f_or_b) ? old_col - 1 : old_col + 1;
    if (new_col < 0) {
      new_row--;
      new_col = 3;
    } else if (new_col > 3) {
      new_row++;
      new_col = 0;
    }
    new_row = fix_map(new_row);
    map[new_row][new_col] = map[old_row][old_col];
  }

  // Clean Up
  if (!f_or_b) { myOff++; }
  mySize--;
  if (mySize == 0) { myOff = 0; }
}

// double the size of map array without changing myOff and mySize
template <typename T>
void deque<T>::doubleMapSize() {
  T **new_map        = new T *[mapSize * 2]();
  int blocks_to_move = (mySize % 4 != 0) ? mySize / 4 + 1 : mySize / 4;
  for (int i = 0; i < blocks_to_move; i++) {
    int pos      = myOff / 4 + i;
    new_map[pos] = map[(pos >= mapSize) ? pos - mapSize : pos];
  }
  delete[] map;
  map = new_map;
  mapSize *= 2;
}

// Return fixed index if index is overflow
template <typename T>
int deque<T>::fix_index(int index) {
  if (index < 0) { index += mapSize * 4; }
  if (index >= mapSize * 4) { index -= mapSize * 4; }
  return index;
}

// Return fixed index if map index is overflow
template <typename T>
int deque<T>::fix_map(int map_index) {
  if (map_index < 0) {
    map_index = mapSize - 1;
  } else if (map_index >= mapSize) {
    map_index = 0;
  }
  return map_index;
}

// Return fixed index if block index is overflow
template <typename T>
int deque<T>::fix_block(int block_index) {
  
  return block_index;
}

// determine if two deques are equal and return true, otherwise return false
template <typename T>
bool operator==(const deque<T> &lhs, const deque<T> &rhs) {
  if (lhs.mapSize != rhs.mapSize) { return false; }
  if (lhs.myOff != rhs.myOff) { return false; }
  if (lhs.mySize != rhs.mySize) { return false; }
  for (int i = 0; i < lhs.mapSize; i++) {
    if (lhs.map[i] == nullptr && rhs.map[i] != nullptr) { return false; }
    if (lhs.map[i] != nullptr && rhs.map[i] == nullptr) { return false; }
    if (lhs.map[i] == nullptr && rhs.map[i] == nullptr) { continue; }
    for (int j = 0; j < 4; j++) {
      if (lhs.map[i][j] != rhs.map[i][j]) { return false; }
    }
  }
}

// inequality operator; returns opposite of == operator
template <typename T>
bool operator!=(const deque<T> &lhs, const deque<T> &rhs) {
  return !(lhs == rhs); // invokes operator==
}

#endif
