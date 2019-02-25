//
//  Unordered Set.h
//  C++ Sandbox
//
//  Created by Tomy Hsieh on 2018/9/26.
//  Copyright © 2018 Tomy Hsieh. All rights reserved.
//

#ifndef Unordered_Set_h
#define Unordered_Set_h

//#include <iostream>
#include <unordered_set>
//#include <vector>
//using std::vector;

//#include <list>
//using std::list;

unsigned int maxValue = 99;

// unordered_set class template definition
template <typename T>
class unordered_set {
  template <typename Tf>
  friend void print(std::unordered_set<Tf> &data1, unordered_set<Tf> &data2);
  friend void testUnorderedSet2();
//  template <typename Tf>
//  friend void print2(std::unordered_set<Tf> &data1, unordered_set<Tf> &data2);
public:
  using listIterator = typename list<T>::iterator;
  using VecListIter = typename vector<listIterator>::iterator;
  bool DEEBUG = false;

  unordered_set();
  ~unordered_set();

  // Returns the number of elements in the unordered_set container.
  unsigned int size() const;

  // Searches the container for an element with k as value and
  // returns an iterator to it if found,
  // otherwise it returns an iterator to unordered_set::end
  // (the element past the end of the container).
  listIterator find(const T &k);

  // Inserts a new element in the unordered_set.
  // The element is inserted only if it is not equivalent to any other element
  // already in the container ( elements in an unordered_set have unique values
  // ). This effectively increases the container size by one.
  void insert(const T &val);

  // Removes from the unordered_set container a single element.
  // This effectively reduces the container size by one.
  void erase(const T &k);

  // Returns the number of buckets in the unordered_set container.
  unsigned int bucket_count() const;

  // Returns the number of elements in bucket n.
  unsigned int bucket_size(unsigned int n) const;

  // Returns the bucket number where the element with value k is located.
  unsigned int bucket(const T &k) const;

  // Returns true iff the current object is equal to data
  bool operator==(std::unordered_set<T> &data);

private:
  list<T> myList; // list of elements, must initialize before myVec
  vector<listIterator> myVec; // vector of list iterators, begin() then end() - 1
  unsigned int maxidx = 8; // current maximum key value
  // put a new element in the unordered_set when myVec is large enough
  void putIn(const T &val);
  // Computes hash value which will be used to compute bucket number
  unsigned int hashSeq(const unsigned int &key, unsigned int count) const;
};

template <typename T>
unordered_set<T>::unordered_set() {
  myVec.reserve(16);
  myVec.assign(16, myList.end());
}

template <typename T>
unordered_set<T>::~unordered_set() {
  myList.clear();
  myVec.clear();
}

template <typename T>
unsigned int unordered_set<T>::size() const {
  return myList.size();
}

template <typename T>
typename unordered_set<T>::listIterator unordered_set<T>::find(const T &k) {
  for (listIterator it = myList.begin(); it != myList.end(); ++it) {
    if (*it == k) {
      return it;
    }
  }
  return myList.end();
}

template <typename T>
void unordered_set<T>::insert(const T &val) {
  
  // Check if already Exist
  if(find(val) != myList.end()) {
    return;
  }
  
  // Check if Vector Needs To Expand
  if(size() == maxidx) {
    maxidx *= (maxidx < 512) ? 8 : 2;
    // TRANSFER OLD VECTOR TO NEW VECTOR
    if (DEEBUG) {
      DEEBUG = false;
    }
    list<T>tmp(myList);
    myList.clear();
    myVec.resize(maxidx * 2);
    myVec.assign(maxidx * 2, myList.end());
    
    // Place The Damn Business First, then Reallocate
    putIn(val);
    
    for (listIterator it = tmp.begin(); it != tmp.end(); ++it) {
      putIn(*it);
    }
//    listIterator itEnd = myList.end();
//    itEnd--;
//    for (listIterator it = myList.begin(); it != myList.end(); ++it) {
//      putIn(*it);
//      myList.erase(it);
//    }
//    DEEBUG = true;
  } else {
    // Place In
    putIn(val);
  }
  
}

template <typename T>
void unordered_set<T>::erase(const T &k) {
  
  listIterator loc = find(k);
  unsigned int bucketNo = bucket(k);
  if (DEEBUG) {
    cout << " from bucket #" << bucketNo << ", list pos " << distance(myList.begin(), loc) << endl;
  }
  if(loc == myList.end()) {
    return;
  }
  if (bucket_size(bucketNo) == 1) {
    myVec[bucketNo * 2] = myList.end();
    myVec[bucketNo * 2 + 1] = myList.end();
  } else {
//    cout << "wow" << endl;
    if (myVec[bucketNo * 2] == loc) {
      myVec[bucketNo * 2]++;
    }
    if (myVec[bucketNo * 2 + 1] == loc) {
      myVec[bucketNo * 2 + 1]--;
    }
  }
  myList.erase(loc);
//  cout << "wow" << endl;
  
}

template <typename T>
unsigned int unordered_set<T>::bucket_count() const {
  return maxidx;
}

template <typename T>
unsigned int
unordered_set<T>::bucket_size(unsigned int n) const {
  if (myVec[n * 2] == myList.end()) {
    return 0;
  }
  long tmp = distance(myVec[n * 2], myVec[n * 2 + 1]);
  tmp++;
  return (unsigned int)(tmp);
}

template <typename T>
unsigned int unordered_set<T>::bucket(const T &k) const {
  unsigned int hashValue = hashSeq(k, sizeof(T));
  return hashValue % maxidx; // bucket number
}

template <typename T>
void unordered_set<T>::putIn(const T &val) {
  unsigned int loc = bucket(val);
  myList.insert(myVec[loc * 2], val);
  if (DEEBUG) {
    cout << " to bucket #" << loc << ", list pos " << distance(myList.begin(), myVec[loc * 2]) << endl;
  }
  if (myVec[loc * 2] == myList.end()) {
    if (myList.empty()) {
      if (DEEBUG) {
        cout << "Freshly ";
      }
      // new vector item, list is empty
      myVec[loc * 2] = myList.begin();
      myVec[loc * 2 + 1] = myList.begin();
    } else {
      // new vector item, list is not empty
      myVec[loc * 2]--;
      myVec[loc * 2 + 1]--;
    }
    if (DEEBUG) {
      cout << "Open Bucket" << endl;
    }
  } else {
    // old vector item
    myVec[loc * 2]--;
    if (DEEBUG) {
      cout << "Extend Bucket" << endl;
    }
  }
}

template <typename T>
unsigned int unordered_set<T>::hashSeq(const unsigned int &key,
                                       unsigned int count) const {
  const unsigned int _FNV_offset_basis =
      2166136261U; // 10000001 00011100 10011101 11000101
  const unsigned int _FNV_prime =
      16777619U; // 00000001 00000000 00000001 10010011
  const unsigned char *first = reinterpret_cast<const unsigned char *>(&key);
  unsigned int val           = _FNV_offset_basis;
  for (unsigned int next = 0; next < count; ++next) { // fold in another byte
    val ^= static_cast<unsigned int>(first[next]);
    val *= _FNV_prime;
  }

  return val;
}

template <typename T>
bool unordered_set<T>::operator==(std::unordered_set<T> &data) {
  
  // Check Size
  if (myList.size() != data.size()) {
    if (DEEBUG) {
      cout << "Size Should be " << data.size() << ", instead of " << myList.size() << endl;
      system("pause");
    }
    return false;
  }

  unsigned int *firstVec = *(reinterpret_cast<unsigned int **>(&data) + 5);
  VecListIter it = myVec.begin();
  for (unsigned int bucketNo = 0; it != myVec.end(); ++it, bucketNo++) {
    
    // Check BucketSize
    if (data.bucket_size(bucketNo) != bucket_size(bucketNo)) {
      if (DEEBUG) {
        cout << "Bucket#" << bucketNo << " Size Should be " << data.bucket_size(bucketNo) << ", instead of " << bucket_size(bucketNo) << endl;
        system("pause");
      }
      return false;
    }

    unsigned int *stlBucketFirst =
        *(reinterpret_cast<unsigned int **>(&firstVec[2 * bucketNo]));
    unsigned int *stlBucketLast =
        *(reinterpret_cast<unsigned int **>(&firstVec[2 * bucketNo + 1]));

    listIterator myBucketFirst = *it;
    ++it;
    listIterator myBucketLast = *it;
    if (myBucketFirst != myList.end()) {
      if (myBucketFirst == myBucketLast) {
        if (*myBucketFirst != *(stlBucketFirst + 2)) {
          if (DEEBUG) {
            cout << "Bucket #" << bucketNo << " Contain only 1 item" << endl;
            cout << "Content Should be " << *(stlBucketFirst + 2) << ", instead of " << *myBucketFirst << endl;
            system("pause");
          }
          return false;
        }
      } else {
        unsigned int *stlPtr   = stlBucketFirst;
        listIterator myIt = myBucketFirst;
        while (myIt != myBucketLast) {
          if (*myIt != *(stlPtr + 2)) {
            if (DEEBUG) {
              cout << "Bucket #" << bucketNo << " Contain multiple item" << endl;
              cout << "Content of Index " << distance(myBucketFirst, myIt) << " Should be " << *(stlPtr + 2) << ", instead of " << *myIt << endl;
              system("pause");
            }
            return false;
          }
          stlPtr = *(reinterpret_cast<unsigned int **>(stlPtr));
          ++myIt;
        }

        if (*myBucketLast != *(stlBucketLast + 2)) {
          if (DEEBUG) {
            cout << "Bucket #" << bucketNo << " Contain multiple item" << endl;
            cout << "Last Item Should be " << *(stlBucketLast + 2) << ", instead of " << *myBucketLast << endl;
            system("pause");
          }
          return false;
        }
      }
    }
  }

  for (unsigned int key = 1; key <= maxValue; key++) {
    if (data.bucket(key) != bucket(key)) {
      if (DEEBUG) {
        cout << "Item " << key << " should be placed in bucket#" << data.bucket(key) << " ,instead of bucket#" << bucket(key) << endl;
        system("pause");
      }
      return false;
    }
  }

  return true;
}

#endif
