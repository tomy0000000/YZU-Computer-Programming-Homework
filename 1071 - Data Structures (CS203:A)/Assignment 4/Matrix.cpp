//
//  Matrix.cpp
//  Hw4
//  Sparse Matrices
//
//  Created by Tomy Hsieh on 2018/11/15.
//  Copyright © 2018 Tomy Hsieh. All rights reserved.
//

#include "Matrix.h"

extern bool dEbUg;

//   #     #
//   ##    #  ####  #####  ######
//   # #   # #    # #    # #
//   #  #  # #    # #    # #####
//   #   # # #    # #    # #
//   #    ## #    # #    # #
//   #     #  ####  #####  ######

MatrixNode::MatrixNode(bool b, Triple &t) {
  head = b;
  if (b)
    right = down = next = this; // row/column header node
  else
    triple = t; // element node or header node for list of header nodes
}

//   #     #
//   ##   ##   ##   #####
//   # # # #  #  #    #
//   #  #  # #    #   #
//   #     # ######   #
//   #     # #    #   #
//   #     # #    #   #

Matrix::Matrix() : headNode(nullptr) {}

Matrix::Matrix(TwoDimArray &twoDimArray) {

  // Build main-head
  Triple s;
  s.row   = twoDimArray.numRows;
  s.col   = twoDimArray.numCols;
  s.value = twoDimArray.numValues;
  if (s.col <= 0 || s.row <= 0) { return; }
  headNode = new MatrixNode(false, s);

  // build seperate nodes
  Triple *triples = new Triple[s.value];
  int count       = 0;
  for (int i = 0; i < s.row; i++) {
    for (int j = 0; j < s.col; j++) {
      if (twoDimArray.ptr[i][j] != 0) {
        triples[count].row   = i;
        triples[count].col   = j;
        triples[count].value = twoDimArray.ptr[i][j];
        count++;
      }
    }
  }

  int p = (s.col > s.row) ? s.col : s.row;

  // at least one row and column
  MatrixNode **head = new MatrixNode *[p];
  Triple zeroTriple = {};
  for (int i = 0; i < p; i++) {
    head[i] = new MatrixNode(true, zeroTriple); // create header nodes
  }

  int currentRow   = 0;
  MatrixNode *last = head[0];         // last node in current row
  for (int i = 0; i < s.value; i++) { // input triples

    // close current row
    if (triples[i].row > currentRow) {
      last->right = head[currentRow];
      currentRow  = triples[i].row;
      last        = head[currentRow];
    }

    // link new node into row list
    last = last->right = new MatrixNode(false, triples[i]);

    // link into column list
    head[triples[i].col]->next = head[triples[i].col]->next->down = last;
  }

  // close last row
  last->right = head[currentRow];

  // close all column lists
  for (int i = 0; i < s.col; i++) { head[i]->next->down = head[i]; }

  // Link lines between header-nodes
  for (int i = 0; i < p - 1; i++) { head[i]->next = head[i + 1]; }

  // Link main head's two lines
  head[p - 1]->next = headNode;
  headNode->right   = head[0];

  // Clean Up
  delete[] head;
}

Matrix::Matrix(const Matrix &matrixToCopy) {
  *this = matrixToCopy;
}

Matrix::~Matrix() {
  erase();
}

//
//
//   ##### ##### ##### ##### ##### ##### ##### ##### ##### #####
//
//   ##### ##### ##### ##### ##### ##### ##### ##### ##### #####
//
//

Matrix &Matrix::operator=(const Matrix &op2) {

  if (!headNode) { erase(); }

  // Build main-head
  Triple s;
  s.row   = op2.headNode->triple.row;
  s.col   = op2.headNode->triple.col;
  s.value = op2.headNode->triple.value;
  if (s.col <= 0 || s.row <= 0) { return *this; }
  headNode = new MatrixNode(false, s);

  // Build heads
  int head_nums     = (s.col > s.row) ? s.col : s.row;
  MatrixNode **head = new MatrixNode *[head_nums];
  Triple zeroTriple = {};
  for (int i = 0; i < head_nums; i++) {
    head[i] = new MatrixNode(true, zeroTriple);
    if (i > 0) {
      head[i - 1]->next = head[i]; // Lines between heads
    }
  }
  // Main-head lines
  headNode->right           = head[0];
  head[head_nums - 1]->next = headNode;

  // Scan Columns (Build and Link)
  MatrixNode *rhs_head = op2.headNode->right;
  for (int head_index = 0; head_index < head_nums;
       head_index++, rhs_head = rhs_head->next) {
    MatrixNode *col_ptr = head[head_index];

    for (MatrixNode *rhs_item = rhs_head->down; !rhs_item->head;
         rhs_item             = rhs_item->down) {
      Triple *tmp          = new Triple;
      tmp->row             = rhs_item->triple.row;
      tmp->col             = rhs_item->triple.col;
      tmp->value           = rhs_item->triple.value;
      MatrixNode *lhs_item = new MatrixNode(false, *tmp);
      lhs_item->down       = head[head_index];
      col_ptr = col_ptr->down = lhs_item;
    }
  }

  // Scan Rows (Link only)
  rhs_head = op2.headNode->right;
  for (int head_index = 0; head_index < head_nums;
       head_index++, rhs_head = rhs_head->next) {
    for (MatrixNode *lhs_item = nullptr, *rhs_item = rhs_head->right;
         !rhs_item->head;
         lhs_item = lhs_item->right, rhs_item = rhs_item->right) {

      // For first node after row head
      if (!lhs_item) {
        lhs_item = head[rhs_item->triple.col]->down;
        while (lhs_item->triple.row != rhs_item->triple.row) {
          lhs_item = lhs_item->down;
        }
        head[rhs_item->triple.row]->right = lhs_item;
      }

      // Link to head or next node
      if (rhs_item->right->head) {
        lhs_item->right = head[head_index];
      } else {
        MatrixNode *tmp = head[rhs_item->right->triple.col]->down;
        while (tmp->triple.row != rhs_item->right->triple.row) {
          tmp = tmp->down;
        }
        lhs_item->right = tmp;
      }
    }
  }

  // Clean Up
  delete[] head;
  return *this;
}

//
//
//   ##### ##### ##### ##### ##### ##### ##### ##### ##### #####
//
//   ##### ##### ##### ##### ##### ##### ##### ##### ##### #####
//
//

//
//     #     #     #     #     #     #     #     #     #     #
//     #     #     #     #     #     #     #     #     #     #
//   ##### ##### ##### ##### ##### ##### ##### ##### ##### #####
//     #     #     #     #     #     #     #     #     #     #
//     #     #     #     #     #     #     #     #     #     #
//

Matrix Matrix::operator+(const Matrix &op2) const {

  // Create a copy of addend
  Matrix sum(*this);
  if (dEbUg) {
    cout << "+++++++++++++++" << endl << "prebuild" << endl << sum << endl;
  }

  // Scan Columns
  for (MatrixNode *lhs_head = sum.headNode->right,
                  *rhs_head = op2.headNode->right;
       lhs_head != sum.headNode;
       lhs_head = lhs_head->next, rhs_head = rhs_head->next) {

    // Init
    MatrixNode *lhs_prev = lhs_head, *lhs_item = lhs_head->down,
               *rhs_item = rhs_head->down;

    // Scan Row of Columns
    for (int row_index = 0; row_index < sum.headNode->triple.row; row_index++) {

      // Run with index, pass thru if both side didn't exist

      if (rhs_item->triple.row == row_index) { // Modified when rhs exist

        // Push lhs to same row or further
        while (lhs_item->triple.row < row_index) {
          lhs_prev = lhs_item;
          lhs_item = lhs_item->down;
        }

        if (lhs_item->triple.row == row_index) { // both side has node

          if (lhs_item->triple.value += rhs_item->triple.value) {
            lhs_prev = lhs_item;
            lhs_item = lhs_item->down;
          } else { // Sum is 0, node should be decomposed

            // Relink row side
            MatrixNode *ptr = sum.headNode->right;

            // Push ptr to one node ahead of lhs node in row
            for (int cnt = 0; cnt < row_index; cnt++) { ptr = ptr->next; }
            while (ptr->right != lhs_item) { ptr = ptr->right; }

            // Relink
            ptr->right = lhs_item->right;

            // Relink column side
            lhs_prev->down = lhs_item->down;

            // Clena Up
            delete lhs_item;
            lhs_item = lhs_prev->down;
            sum.headNode->triple.value--;
          }

        } else { // lhs didn't exist, build a new one

          // Build a new node
          Triple *tmp              = new Triple;
          tmp->row                 = rhs_item->triple.row;
          tmp->col                 = rhs_item->triple.col;
          tmp->value               = rhs_item->triple.value;
          MatrixNode *new_lhs_item = new MatrixNode(false, *tmp);
          sum.headNode->triple.value++;

          // Link column side
          new_lhs_item->down = lhs_item;
          lhs_prev->down     = new_lhs_item;
          lhs_prev           = new_lhs_item;

          // Link row side
          MatrixNode *ptr =
              sum.headNode->right; // use ptr to find next row node

          // Redirect to row head
          for (int cnt = 0; cnt < row_index; cnt++) { ptr = ptr->next; }

          MatrixNode *ptr_prev = ptr;        // prev point to prev item
          ptr                  = ptr->right; // ptr point to next item

          // Push ptr to the right location
          while (ptr->triple.col < tmp->col && !ptr->head) {
            ptr_prev = ptr;
            ptr      = ptr->right;
          }

          // Link
          ptr_prev->right     = new_lhs_item;
          new_lhs_item->right = ptr;

          if (dEbUg) {
            cout << "Link " << tmp->row << tmp->col << tmp->value << endl;
          }
        }

        // Push rhs down with 1 unit
        rhs_item = rhs_item->down;
      }
    }
  }
  if (dEbUg) {
    cout << sum << endl;
    cout << "+++++++++++++++" << endl;
  }
  return sum;
}

//
//     #     #     #     #     #     #     #     #     #     #
//     #     #     #     #     #     #     #     #     #     #
//   ##### ##### ##### ##### ##### ##### ##### ##### ##### #####
//     #     #     #     #     #     #     #     #     #     #
//     #     #     #     #     #     #     #     #     #     #
//

//
//   #    # #    # #    # #    # #    # #    # #    # #    # #    #
//    #  #   #  #   #  #   #  #   #  #   #  #   #  #   #  #   #  #
//     ##     ##     ##     ##     ##     ##     ##     ##     ##
//     ##     ##     ##     ##     ##     ##     ##     ##     ##
//    #  #   #  #   #  #   #  #   #  #   #  #   #  #   #  #   #  #
//   #    # #    # #    # #    # #    # #    # #    # #    # #    #

Matrix Matrix::operator*(const Matrix &op2) const {

  // Create Matrix
  Matrix product;
  Triple s;
  s.row            = headNode->triple.row;
  s.col            = op2.headNode->triple.col;
  s.value          = 0;
  product.headNode = new MatrixNode(false, s);

  // Build heads
  int head_nums     = (s.col > s.row) ? s.col : s.row;
  MatrixNode **head = new MatrixNode *[head_nums];
  Triple zeroTriple = {};
  for (int i = 0; i < head_nums; i++) {
    head[i] = new MatrixNode(true, zeroTriple);
    if (i > 0) {
      head[i - 1]->next = head[i]; // Lines between heads
    }
  }

  // Main-head lines
  product.headNode->right   = head[0];
  head[head_nums - 1]->next = product.headNode;

  // Build a pointer db
  MatrixNode **row_last = new MatrixNode *[s.row]();
  for (int row = 0; row < s.row; row++) {
    row_last[row] = head[row]->right = head[row];
  }

  // Scan Columns of op2 (Build and Link)
  MatrixNode *op2_head = op2.headNode->right;
  for (int col = 0; col < s.col; col++, op2_head = op2_head->next) {

    MatrixNode *col_ptr  = head[col];
    MatrixNode *op1_head = headNode->right;
    for (int row = 0; row < s.row; row++, op1_head = op1_head->next) {

      int value            = 0;
      MatrixNode *op1_item = op1_head->right, *op2_item = op2_head->down;
      for (int inter = 0; inter < headNode->triple.col; inter++) {
        if (op1_item->triple.col == inter && op2_item->triple.row == inter &&
            !op1_item->head && !op2_item->head) {
          value += op1_item->triple.value * op2_item->triple.value;
        }
        if (op1_item->triple.col <= inter) { op1_item = op1_item->right; }
        if (op2_item->triple.row <= inter) { op2_item = op2_item->down; }
      }

      // Don't build node if value is 0
      if (!value) { continue; }

      // Build a new node
      Triple *tmp          = new Triple;
      tmp->row             = row;
      tmp->col             = col;
      tmp->value           = value;
      MatrixNode *new_node = new MatrixNode(false, *tmp);
      product.headNode->triple.value++;
      new_node->down = head[col];
      col_ptr = col_ptr->down = new_node;

      // Link row side
      row_last[row] = row_last[row]->right = new_node;
      new_node->right                      = head[row];

      if (dEbUg) { cout << "Link " << row << col << value << endl; }
    }
  }

  if (dEbUg) {
    cout << product << endl;
    cout << "xxxxxxxxxxxxxxx" << endl;
  }

  // Clean Up
  delete[] head;
  delete[] row_last;
  return product;
}

//
//   #    # #    # #    # #    # #    # #    # #    # #    # #    #
//    #  #   #  #   #  #   #  #   #  #   #  #   #  #   #  #   #  #
//     ##     ##     ##     ##     ##     ##     ##     ##     ##
//     ##     ##     ##     ##     ##     ##     ##     ##     ##
//    #  #   #  #   #  #   #  #   #  #   #  #   #  #   #  #   #  #
//   #    # #    # #    # #    # #    # #    # #    # #    # #    #

void Matrix::erase() { // erase the matrix, return the nodes to the heap
  MatrixNode *x, *y;
  if (headNode != nullptr) {
    MatrixNode *head = headNode->right;

    while (head != headNode) // free the triple and header nodes by row
    {
      y = head->right;
      while (y != head) {
        x = y;
        y = y->right;
        delete x;
      }

      x    = head;
      head = head->next;
      delete x;
    }

    delete headNode;
    headNode = nullptr;
  }
}

bool Matrix::operator==(TwoDimArray &twoDimArray) {
  int numRows = headNode->triple.row;
  int numCols = headNode->triple.col;

  if (numRows != twoDimArray.numRows || numCols != twoDimArray.numCols ||
      headNode->triple.value != twoDimArray.numValues) {
    cout << "Basic Info Diff." << endl;
    return false;
  }

  int col;
  MatrixNode *head = headNode->right;

  // scan header nodes one by one
  for (int row = 0; row < numRows; row++, head = head->next) {
    col = 0;
    // scan elements in the current row
    for (MatrixNode *temp = head->right; temp != head; temp = temp->right) {

      if (row != temp->triple.row) {
        cout << "wrong row info at " << row << endl;
        return false;
      }

      // find next nonzero element in the current row
      while (twoDimArray.ptr[row][col] == 0) { col++; }

      if (col != temp->triple.col) {
        cout << "wrong col info at " << col << endl;
        return false;
      }

      if (twoDimArray.ptr[row][col] != temp->triple.value) {
        cout << "wrong value at (" << row << ", " << col << ")" << endl;
        return false;
      }

      col++;
    }
  }

  int row;
  head = headNode->right;

  // scan header nodes one by one
  for (int col = 0; col < numRows; col++, head = head->next) {
    row = 0;
    // scan elements in the current column
    for (MatrixNode *temp = head->down; temp != head; temp = temp->down) {

      if (col != temp->triple.col) {
        cout << "wrong col info at " << col << endl;
        return false;
      }

      // find next nonzero element in the current column
      while (twoDimArray.ptr[row][col] == 0) { row++; }

      if (row != temp->triple.row) {
        cout << "wrong row info at " << row << endl;
        return false;
      }

      if (twoDimArray.ptr[row][col] != temp->triple.value) {
        cout << "wrong value at (" << row << ", " << col << ")" << endl;
        return false;
      }

      row++;
    }
  }

  return true;
}

//   #######
//   #       #    # #    #  ####   ####
//   #       #    # ##   # #    # #
//   #####   #    # # #  # #       ####
//   #       #    # #  # # #           #
//   #       #    # #   ## #    # #    #
//   #        ####  #    #  ####   ####

ostream &operator<<(ostream &os, const Matrix &matrix) {
  int preCol;
  int numRows      = matrix.headNode->triple.row;
  MatrixNode *head = matrix.headNode->right;
  // scan header nodes one by one
  for (int row = 0; row < numRows; row++, head = head->next) {
    preCol = -1;
    // scan elements in the current row
    for (MatrixNode *temp = head->right; temp != head; temp = temp->right) {
      // display zero elements
      for (int i = 1; i < temp->triple.col - preCol; i++) {
        os << setw(4) << 0;
      }
      os << setw(4) << temp->triple.value; // display nonzero element
      preCol = temp->triple.col;
    }

    for (int i = 1; i < matrix.headNode->triple.col - preCol; i++)
      os << setw(4) << 0;
    os << endl;
  }

  return os; // enables os << x << y;
}
