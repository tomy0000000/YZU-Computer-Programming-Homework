//
//  Set.h
//  Hw3
//  Set
//
//  Created by Tomy Hsieh on 2018/11/15.
//  Copyright © 2018 Tomy Hsieh. All rights reserved.
//

#ifndef Set_h
#define Set_h

extern bool master_dEbUg, dEbUg;
enum Color { Red, Black };

//   #     #
//   ##    #  ####  #####  ######
//   # #   # #    # #    # #
//   #  #  # #    # #    # #####
//   #   # # #    # #    # #
//   #    ## #    # #    # #
//   #     #  ####  #####  ######

template <typename Kty>
class TreeNode {
  template <typename K>
  friend class set;

private:
  TreeNode *left;   // left subtree,  or smallest element if head
  TreeNode *parent; // parent,        or root of tree if head
  TreeNode *right;  // right subtree, or largest element if head
  Color color;      // red or black,  black if head
  bool isNil;       // true if head node (nil pointer points to)
  Kty myval;
};

//    #####
//   #     # ###### #####
//   #       #        #
//    #####  #####    #
//         # #        #
//   #     # #        #
//    #####  ######   #

template <typename Kty>
class set {
public:
  // Constructors & Destructors
  set();
  ~set();
  
  // Actions
  void insert(const Kty &val);
  unsigned int erase(const Kty &val); // Returns the number of elements erased

private:
  TreeNode<Kty> *myHead;
  unsigned int mySize; // Does NOT include head node

  // Removes all elements from the set object (which are destroyed)
  void clear(TreeNode<Kty> *node);
  // erase node provided that the degree of node is at most one
  void eraseDegreeOne(TreeNode<Kty> *node);
  
  // Rebalance Operations
  void reBalance(TreeNode<Kty> *node); // for insertion
  void fixUp(TreeNode<Kty> *N, TreeNode<Kty> *P); // for deletion
  
  // Rotations
  void LLRotation(TreeNode<Kty> *p);
  void RRRotation(TreeNode<Kty> *p);
  void LRRotation(TreeNode<Kty> *node);
  void RLRotation(TreeNode<Kty> *node);
  
  // Traversals
  void twoTraversals(); // Preorder and Inorder
  void preorder(TreeNode<Kty> *node);
  void inorder(TreeNode<Kty> *node);
};

//   #######
//   #       #    # #    #  ####   ####
//   #       #    # ##   # #    # #
//   #####   #    # # #  # #       ####
//   #       #    # #  # # #           #
//   #       #    # #   ## #    # #    #
//   #        ####  #    #  ####   ####

template <typename Kty>
set<Kty>::set() : myHead(new TreeNode<Kty>), mySize(0) {
  myHead->left   = myHead;
  myHead->parent = myHead;
  myHead->right  = myHead;
  myHead->color  = Black;
  myHead->isNil  = true;
}

template <typename Kty>
set<Kty>::~set() {
  clear(myHead->parent);
  delete myHead;
}

template <typename Kty>
void set<Kty>::insert(const Kty &val) {

  if (master_dEbUg && dEbUg) { cout << endl << "dEbUg Mode is ON" << endl; }

  // Find the Insertion position
  TreeNode<Kty> *insert_pos     = myHead;
  TreeNode<Kty> *pre_insert_pos = myHead->parent;
  bool direction; // True for Right, False for Left
  while (!pre_insert_pos->isNil) {
    insert_pos = pre_insert_pos;
    if (val == pre_insert_pos->myval) {
      return;
    } else if (val > pre_insert_pos->myval) {
      pre_insert_pos = pre_insert_pos->right;
      direction      = true;
    } else if (val < pre_insert_pos->myval) {
      pre_insert_pos = pre_insert_pos->left;
      direction      = false;
    }
  }

  // Init a new node
  TreeNode<Kty> *newNode = new TreeNode<Kty>;
  newNode->color         = Red;
  newNode->isNil         = false;
  newNode->myval         = val;
  newNode->left = newNode->right = myHead;

  // Execute Insertion
  if (insert_pos == myHead) {
    newNode->parent = myHead;
    myHead->parent = myHead->left = myHead->right = newNode;
  } else if (direction) {
    newNode->parent   = insert_pos;
    insert_pos->right = newNode;
  } else {
    newNode->parent  = insert_pos;
    insert_pos->left = newNode;
  }
  reBalance(newNode);
  if (master_dEbUg && dEbUg) { twoTraversals(); }
  mySize++;
}

template <typename Kty>
unsigned int set<Kty>::erase(const Kty &val) {
  
  if (master_dEbUg && dEbUg) {
    cout << endl << "dEbUg Mode is ON" << endl << endl;
    cout << "Before Removal: " << endl;
    twoTraversals();
    cout << endl;
  }
  
  // Find the Removal position
  TreeNode<Kty> *remove_pos     = myHead;
  TreeNode<Kty> *pre_remove_pos = myHead->parent;
  while (!pre_remove_pos->isNil) {
    remove_pos = pre_remove_pos;
    if (val == pre_remove_pos->myval) { break; }
    pre_remove_pos = (val > pre_remove_pos->myval) ? pre_remove_pos->right : pre_remove_pos->left;
  }
  if (val != remove_pos->myval) { return 0; }
  
  // Try finding a new value to replace
  // If found, delete the node where value was copied
  if (!remove_pos->left->isNil && !remove_pos->right->isNil) {
    TreeNode<Kty> *new_value = remove_pos->right;
    while (!new_value->left->isNil) {
      new_value = new_value->left;
    }
    remove_pos->myval = new_value->myval;
    remove_pos = new_value;
  }
  
  // Execute Deletion
  eraseDegreeOne(remove_pos);
  mySize--;
  if (master_dEbUg && dEbUg) {
    cout << "After Removal: " << endl;
    twoTraversals();
    cout << endl;
  }
  return 1;
}

template <typename Kty>
void set<Kty>::clear(TreeNode<Kty> *node) {
  if (!node->isNil) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <typename Kty>
void set<Kty>::reBalance(TreeNode<Kty> *node) {

  // Case 1 -> newNode is the only node
  if (node->parent == myHead) {
    node->color = Black;
    return;
  }

  // Case 2 -> parent is Black
  if (node->parent->color == Black) { return; }

  TreeNode<Kty> *uncle = node->parent->parent;
  uncle = (uncle->left == node->parent ? uncle->right : uncle->left);

  // Case 3 -> parent & uncle are Red -> LLr & LRr
  if (uncle != myHead && uncle->color == Red) {
    node->parent->color = uncle->color = Black;
    node->parent->parent->color        = Red;
    reBalance(node->parent->parent);
    return;
  }

  // Case 4 -> LRb & RLb
  if (node == node->parent->right &&
      node->parent == node->parent->parent->left) {
    LRRotation(node);
    std::swap(node->color, node->right->color);
    return;
  } else if (node == node->parent->left &&
             node->parent == node->parent->parent->right) {
    RLRotation(node);
    std::swap(node->color, node->left->color);
    return;
  }

  // Case 5 -> RRb & LLb
  if (node->parent->color == Red && uncle->color == Black) {
    if (node == node->parent->right) {
      RRRotation(node->parent);
      std::swap(node->parent->color, node->parent->left->color);
    } else {
      LLRotation(node->parent);
      std::swap(node->parent->color, node->parent->right->color);
    }
  }
}

// rotate right at g, where p = g->left and node = p->left
//                    +---+
//                    | g |  <- rotate at this
//                    +---+
//                  / ^
//                 / /
//                v /
//            +---+
//            | p |
//            +---+
//          / ^
//         / /
//        v /
// +------+
// | node |
// +------+
template <typename Kty>
void set<Kty>::LLRotation(TreeNode<Kty> *p) {
  p->parent->left = p->right;
  if (p->parent->parent == myHead) {
    p->parent->parent->parent = p;
  } else {
    if (p->parent == p->parent->parent->left) {
      p->parent->parent->left = p;
    } else {
      p->parent->parent->right = p;
    }
  }
  if (p->right != myHead) { p->right->parent = p->parent; }
  p->right         = p->parent;
  p->parent        = p->right->parent;
  p->right->parent = p;
}

// rotate left at g, where p = g->right and node = p->right
// +---+
// | g |  <- rotate at this
// +---+
//      \
//       +---+
//       | p |
//       +---+
//            \
//             +------+
//             | node |
//             +------+
template <typename Kty>
void set<Kty>::RRRotation(TreeNode<Kty> *p) {
  p->parent->right = p->left;
  if (p->parent->parent == myHead) {
    p->parent->parent->parent = p;
  } else {
    if (p->parent == p->parent->parent->left) {
      p->parent->parent->left = p;
    } else {
      p->parent->parent->right = p;
    }
  }
  if (p->left != myHead) { p->left->parent = p->parent; }
  p->left         = p->parent;
  p->parent       = p->left->parent;
  p->left->parent = p;
}

// LR rotation; p = g->left and node = p->right
//       +---+
//       | g |
//       +---+
//      /
// +---+
// | p |
// +---+
//      \
//       +------+
//       | node |
//       +------+
template <typename Kty>
void set<Kty>::LRRotation(TreeNode<Kty> *node) {
  RRRotation(node);
  LLRotation(node);
}

// RL rotation; p = g->right and node = p->left
//    +---+
//    | g |
//    +---+
//         \
//          +---+
//          | p |
//          +---+
//         /
// +------+
// | node |
// +------+
template <typename Kty>
void set<Kty>::RLRotation(TreeNode<Kty> *node) {
  LLRotation(node);
  RRRotation(node);
}

template <typename Kty>
void set<Kty>::eraseDegreeOne(TreeNode<Kty> *node) {
  
  // if node don't have any child
  // Refer to the left Nil leaf
  bool child_direction = node->left->isNil; // True for Right, False for Left
  TreeNode<Kty> *onlyChild = (child_direction) ? node->right : node->left;
  
  if (node->color == Red) { // Simple Case 1 -> Red node with two leaves
    if (node == node->parent->right) {
      node->parent->right = myHead;
    } else {
      node->parent->left = myHead;
    }
    delete node;
  } else if (onlyChild->color == Red) { // Simple Case 2 -> node is Black, onlyChild is Red
    node->color = Black;
    node->myval = onlyChild->myval;
    if (child_direction) {
      node->right = myHead;
    } else {
      node->left = myHead;
    }
    delete onlyChild;
  } else { // Complicate Casse: Black Node with two Nil Black Nodes
//    node->color = onlyChild->color;
//    node->myval = onlyChild->myval;
//    if (child_direction) {
//      node->right = myHead;
//    } else {
//      node->left = myHead;
//    }
//    delete onlyChild;
    fixUp(node, node->parent);
    if (node == node->parent->right) {
      node->parent->right = myHead;
    } else {
      node->parent->left = myHead;
    }
    delete node;
  }
  
  
}

template <typename Kty>
void set<Kty>::fixUp(TreeNode<Kty> *N, TreeNode<Kty> *P) {
  
  // Case 1 -> N is Root
  if (N->parent == myHead) {
//    myHead->left = myHead->right = myHead->parent = myHead;
    return;
  }
  
  TreeNode<Kty> *Sibling = (N == P->left) ? P->right : P->left;
  
  // Case 2 -> Sibling is Red
  if (Sibling->color == Red) {
    if (N == P->left) {
      RRRotation(Sibling);
      std::swap(P->color, Sibling->color);
      Sibling = (N == P->left) ? P->right : P->left;
    } else if (N == P->right) {
      LLRotation(Sibling);
      std::swap(P->color, Sibling->color);
      Sibling = (N == P->left) ? P->right : P->left;
    }
  }
  
  // Case 3 -> Every Node is Black
  if (N->color == Black && P->color == Black && Sibling->color == Black && Sibling->left->color == Black && Sibling->right->color == Black) {
    Sibling->color = Red;
    fixUp(P, P->parent);
    return;
  }
  
  // Case 4 -> Every Node is Black, but P
  if (N->color == Black && P->color == Red && Sibling->color == Black && Sibling->left->color == Black && Sibling->right->color == Black) {
    std::swap(P->color, Sibling->color);
    return;
  }
  
  // Case 5 -> Sibling has different colors of childs
  if (Sibling->color == Black) {
    // IF-statement above is Just For Noting, wasn't necessary
    // cuz case 2 catch the oppisite case
    if (N == P->left && Sibling->left->color == Red && Sibling->right->color == Black) {
      std::swap(Sibling->color, Sibling->left->color);
      LLRotation(Sibling->left);
      Sibling = (N == P->left) ? P->right : P->left;
    } else if (N == P->right && Sibling->right->color == Red && Sibling->left->color == Black) {
      std::swap(Sibling->color, Sibling->right->color);
      RRRotation(Sibling->right);
      Sibling = (N == P->left) ? P->right : P->left;
    }
  }
  
  // Case 6 -> Sibling is Black and Outer-Side-Sibling-Child is Red
  if (N == P->left && Sibling->color == Black && Sibling->right->color == Red) {
    std::swap(P->color, Sibling->color);
    Sibling->right->color = Black;
    RRRotation(Sibling);
  } else if (N == P->right && Sibling->color == Black && Sibling->left->color == Red) {
    std::swap(P->color, Sibling->color);
    Sibling->left->color = Black;
    LLRotation(Sibling);
  }
}

template <typename Kty>
void set<Kty>::twoTraversals() {
  cout << "Preorder sequence:\n";
  preorder(myHead->parent);

  cout << "\nInorder sequence:\n";
  inorder(myHead->parent);
  cout << endl;
}

template <typename Kty>
void set<Kty>::preorder(TreeNode<Kty> *node) {
  if (node != myHead) {
    cout << setw(5) << node->myval << (node->color == Red ? "R" : "B");
    preorder(node->left);
    preorder(node->right);
  }
}

template <typename Kty>
void set<Kty>::inorder(TreeNode<Kty> *node) {
  if (node != myHead) {
    inorder(node->left);
    cout << setw(5) << node->myval << (node->color == Red ? "R" : "B");
    inorder(node->right);
  }
}

#endif
