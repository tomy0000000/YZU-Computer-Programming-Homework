//
//  main.cpp
//  Hw3
//  Linear Operation of Equations
//
//  Created by Tomy Hsieh on 2018/12/1.
//  Copyright © 2018 Tomy Hsieh. All rights reserved.
//

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

class Polynomial;
enum Indeterminate {x3,y3,z3,x2y,x2z,xy2,xz2,y2z,yz2,x2,y2,z2,xyz,xy,xz,yz,x,y,z,cons};

int x_expon_of_indeterminate(Indeterminate indet) {
  if (indet == x3) { return 3; }
  if (indet == x2y || indet == x2z || indet == x2) { return 2; }
  if (indet == xy2 || indet == xz2 || indet == xyz || indet == xy ||
      indet == xz || indet == x) {
    return 1;
  }
  return 0;
}

int y_expon_of_indeterminate(Indeterminate indet) {
  if (indet == y3) { return 3; }
  if (indet == xy2 || indet == y2z || indet == y2) { return 2; }
  if (indet == x2y || indet == yz2 || indet == xyz || indet == xy ||
      indet == yz || indet == y) {
    return 1;
  }
  return 0;
}

int z_expon_of_indeterminate(Indeterminate indet) {
  if (indet == z3) { return 3; }
  if (indet == xz2 || indet == yz2 || indet == z2) { return 2; }
  if (indet == x2z || indet == y2z || indet == xyz || indet == xz ||
      indet == yz || indet == z) {
    return 1;
  }
  return 0;
}

void output_ind_part(ostream &os, Indeterminate ind, Indeterminate part,
                     bool &output) {
  string result, indet_str;
  int expon = 0;
  switch (part) {
  case x:
    expon     = x_expon_of_indeterminate(ind);
    indet_str = "x";
    break;
  case y:
    expon     = y_expon_of_indeterminate(ind);
    indet_str = "y";
    break;
  case z:
    expon     = z_expon_of_indeterminate(ind);
    indet_str = "z";
    break;
  default: break;
  }
  if (expon) {
    if (output) { os << " * "; }
    os << indet_str;
    if (expon > 1) { os << " ^ " << expon; }
    output = true;
  }
}

ostream &operator<<(ostream &os, const Indeterminate &ind) {
  bool output = false;
  for (int i = x; i <= z; i++) {
    output_ind_part(os, ind, static_cast<Indeterminate>(i), output);
  }
  return os;
}

//   #     #
//   ##    #  ####  #####  ######
//   # #   # #    # #    # #
//   #  #  # #    # #    # #####
//   #   # # #    # #    # #
//   #    ## #    # #    # #
//   #     #  ####  #####  ######

class PolyNode {
  friend class Polynomial;
  friend ostream &operator<<(ostream &os, const Polynomial &polynomial);
  friend ostream &operator<<(ostream &os, const PolyNode &node);

public:
  PolyNode()
      : coefficient(1), indeterminate(cons), x_expon(0), y_expon(0),
        z_expon(0) {}
  PolyNode(double coeff, Indeterminate indet)
      : coefficient(coeff), indeterminate(indet),
        x_expon(x_expon_of_indeterminate(indet)),
        y_expon(y_expon_of_indeterminate(indet)),
        z_expon(z_expon_of_indeterminate(indet)) {}

  PolyNode(double coeff, int x_pon, int y_pon, int z_pon)
      : coefficient(coeff), x_expon(x_pon), y_expon(y_pon), z_expon(z_pon) {
    calculate_indeterminate();
  }

  bool operator<(const PolyNode &rhs) const {
    return indeterminate < rhs.indeterminate;
  }

  PolyNode operator*(const PolyNode &rhs) const {
    return PolyNode(coefficient * rhs.coefficient, x_expon + rhs.x_expon,
                    y_expon + rhs.y_expon, z_expon + rhs.z_expon);
  }
  void set_coefficient(double value) {
    coefficient = value;
  }
  void set_expon(Indeterminate ind, int value) {
    if (ind == x) {
      x_expon = value;
      calculate_indeterminate();
    }
    if (ind == y) {
      y_expon = value;
      calculate_indeterminate();
    }
    if (ind == z) {
      z_expon = value;
      calculate_indeterminate();
    }
  }
  double get_coefficient() const {
    return coefficient;
  }
  int get_expon(Indeterminate ind) const {
    if (ind == x) { return x_expon; }
    if (ind == y) { return y_expon; }
    if (ind == z) { return z_expon; }
    return -1;
  }
  bool is_default() {
    if (coefficient != 1) { return false; }
    if (x_expon != 0) { return false; }
    if (y_expon != 0) { return false; }
    if (z_expon != 0) { return false; }
    if (indeterminate != cons) { return false; }
    return true;
  }

private:
  mutable double coefficient;
  int x_expon;
  int y_expon;
  int z_expon;
  Indeterminate indeterminate;

  void calculate_indeterminate() {
    for (int i = x3; i <= cons; i++) {
      Indeterminate tmp = static_cast<Indeterminate>(i);
      if (x_expon_of_indeterminate(tmp) == x_expon &&
          y_expon_of_indeterminate(tmp) == y_expon &&
          z_expon_of_indeterminate(tmp) == z_expon) {
        indeterminate = tmp;
        return;
      }
    }
  }
};

// Only Output ABSOLUTED Coefficient
ostream &operator<<(ostream &os, const PolyNode &node) {
  double abs_coeff = abs(node.coefficient);
  // Coefficient
  if (node.indeterminate == cons) {
    os << abs_coeff;
  } else if (abs_coeff != 1) {
    os << abs_coeff << " * ";
  }
  // Indeterminate
  os << node.indeterminate;
  return os;
}

//   ######
//   #     #  ####  #      #   #
//   #     # #    # #       # #
//   ######  #    # #        #
//   #       #    # #        #
//   #       #    # #        #
//   #        ####  ######   #

class Polynomial {
  friend ostream &operator<<(ostream &os, const Polynomial &polynomial);

public:
  Polynomial() {}
  Polynomial(double val) {
    nodes.insert(PolyNode(val, cons));
  }

  Polynomial operator-(const Polynomial &rhs) const {
    Polynomial result = *this;
    for (set<PolyNode>::iterator r_iter = rhs.nodes.begin();
         r_iter != rhs.nodes.end(); ++r_iter) {
      PolyNode tmp = *r_iter;
      tmp.coefficient *= -1;
      result.insert(tmp);
    }
    return result;
  }

  Polynomial operator+(const Polynomial &rhs) const {
    Polynomial result = *this;
    for (set<PolyNode>::iterator r_iter = rhs.nodes.begin();
         r_iter != rhs.nodes.end(); ++r_iter) {
      result.insert(*r_iter);
    }
    return result;
  }

  Polynomial operator*(const Polynomial &rhs) const {
    Polynomial result;
    for (set<PolyNode>::iterator l_iter = nodes.begin(); l_iter != nodes.end();
         ++l_iter) {
      for (set<PolyNode>::iterator r_iter = rhs.nodes.begin();
           r_iter != rhs.nodes.end(); ++r_iter) {
        result.insert((*l_iter) * (*r_iter));
      }
    }
    return result;
  }

  Polynomial operator*(const double &times) const {
    if (times == 0) { return Polynomial(); }
    Polynomial result;
    for (set<PolyNode>::iterator iter = nodes.begin(); iter != nodes.end();
         ++iter) {
      PolyNode tmp = *iter;
      tmp.coefficient *= times;
      result.insert(tmp);
    }
    return result;
  }

  Polynomial operator^(const int &expon) const {
    Polynomial result;
    if (expon == 0) {
      result.insert(PolyNode(1, 0, 0, 0));
    } else {
      result = *this;
      for (int i = 0; i < expon - 1; i++) { result = result * (*this); }
    }
    return result;
  }

  void insert(const PolyNode &newNode) {
    pair<set<PolyNode>::iterator, bool> status = nodes.insert(newNode);
    if (!status.second) { status.first->coefficient += newNode.coefficient; }
    if (status.first->coefficient == 0) { nodes.erase(status.first); }
  }

  bool *get_enables() {
    static bool xyz[] = {false, false, false};
    for (set<PolyNode>::iterator iter = nodes.begin(); iter != nodes.end();
         ++iter) {
      if (iter->x_expon != 0 && !xyz[0]) { xyz[0] = true; }
      if (iter->y_expon != 0 && !xyz[1]) { xyz[1] = true; }
      if (iter->z_expon != 0 && !xyz[2]) { xyz[2] = true; }
      bool stop = true;
      for (int i = 0; i < 3; i++) {
        if (!xyz[i]) {
          stop = false;
          break;
        }
      }
      if (stop) { break; }
    }
    return xyz;
  }
  bool empty() const {
    return nodes.empty();
  }
  set<PolyNode>::iterator begin() const {
    return nodes.begin();
  }
  set<PolyNode>::iterator end() const {
    return nodes.end();
  }

private:
  set<PolyNode> nodes;
};

ostream &operator<<(ostream &os, const Polynomial &polynomial) {
  for (set<PolyNode>::iterator iter = polynomial.nodes.begin();
       iter != polynomial.nodes.end(); ++iter) {
    if (iter != polynomial.begin()) {
      os << ((iter->coefficient > 0) ? " + " : " - ");
    } else if (iter->coefficient < 0) {
      os << "- ";
    }
    os << *iter;
  }
  return os;
}

bool check_status(Indeterminate status, int expon, PolyNode &tmp) {
  if (status == x || status == y || status == z) {
    tmp.set_expon(status, expon);
    return true;
  }
  return false;
}

//   #     #
//   ##   ##   ##   # #    #
//   # # # #  #  #  # ##   #
//   #  #  # #    # # # #  #
//   #     # ###### # #  # #
//   #     # #    # # #   ##
//   #     # #    # # #    #

bool dEbUg = false;

int main(int argc, const char *argv[]) {

  // Read Original Polynomial
  ifstream inFile(argv[1]);
  string poly_str, trash;
  Polynomial original;
  Indeterminate status = cons;
  bool coef_pos        = true;
  PolyNode tmp;
  while (inFile >> poly_str) {
    if (poly_str == "=") {
      if (check_status(status, 1, tmp)) {
        if (tmp.get_coefficient() == 1 && !coef_pos) {
          tmp.set_coefficient(-1);
        }
      }
      original.insert(tmp);
      break;
    } else if (poly_str == "+" || poly_str == "-") {
      check_status(status, 1, tmp);
      if (tmp.get_coefficient() == 1 && !coef_pos) { tmp.set_coefficient(-1); }
      if (!tmp.is_default()) { original.insert(tmp); }
      tmp      = PolyNode();
      status   = cons;
      coef_pos = poly_str == "+";
    } else if (poly_str == "x" || poly_str == "y" || poly_str == "z") {
      check_status(status, 1, tmp);
      status = (poly_str == "x") ? x : (poly_str == "y") ? y : z;
    } else if ("0" <= poly_str && poly_str <= "9") {
      double number = atof(poly_str.c_str());
      if (check_status(status, number, tmp)) {
        status = cons;
      } else if (status == cons) {
        tmp.set_coefficient(coef_pos ? number : number * -1);
      }
    }
  }
  getline(inFile, trash);

  if (dEbUg) { cout << original << " = 0" << endl << endl; }

  // Calc Original Polynomials Specs
  bool *org_enables = original.get_enables();
  size_t org_degree = 0;
  for (int i = 0; i < sizeof(org_enables) / sizeof(*org_enables); i++) {
    if (org_enables[i]) { org_degree++; }
  }

  // Read Matrices
  Mat mat1((int)org_degree, (int)org_degree, CV_64F);
  Mat mat2((int)org_degree, (int)org_degree, CV_64F);
  int col = 0;
  for (string line; getline(inFile, line) && col < org_degree; col++) {
    int row         = 0;
    size_t prev_pos = -1;
    size_t pos      = line.find(",");
    for (bool reading = true; reading; pos = line.find(",", pos + 1), row++) {
      reading        = pos != string::npos;
      string num_str = line.substr(prev_pos + 1, pos - prev_pos - 1);
      double val     = atof(num_str.c_str());
      if (row < org_degree) {
        mat1.at<double>(row, col) = val;
      } else {
        mat2.at<double>(row - (int)org_degree, col) = val;
      }
      prev_pos = pos;
    }
  }

  // Calculate Operation Matrix
  Mat op((int)org_degree, (int)org_degree, CV_64F);
  Mat op_32S((int)org_degree, (int)org_degree, CV_32S);
  op = (mat2 * mat1.inv());
  op.convertTo(op_32S, CV_32S);
  op_32S.convertTo(op, CV_64F);

  if (dEbUg) {
    cout << "mat 1" << endl;
    cout << mat1 << endl << endl;
    cout << "mat 2" << endl;
    cout << mat2 << endl << endl;
    cout << "op" << endl;
    cout << op << endl << endl;
  }

  // Building new Polynomial
  map<int, Polynomial> new_exps;
  int shift = 0;
  for (int i = x; i <= z; i++) {
    if (org_enables[i - x]) {
      for (int j = x; j <= z; j++) {
        if (org_enables[j - x]) {
          new_exps[i].insert(
              PolyNode(op.at<double>(i - x - shift, j - x - shift),
                       static_cast<Indeterminate>(j)));
        }
      }
    } else {
      shift++;
    }
  }

  if (dEbUg) {
    cout << "Expresssion (x, y, z)" << endl;
    for (int i = x; i <= z; i++) { cout << new_exps[x] << endl; }
    cout << endl;
  }

  Polynomial result;
  for (set<PolyNode>::iterator iter = original.begin(); iter != original.end();
       ++iter) {
    Polynomial tmp(iter->get_coefficient());
    for (int i = x; i <= z; i++) {
      if (org_enables[i - x]) {
        tmp = tmp *
              (new_exps[i] ^ iter->get_expon(static_cast<Indeterminate>(i)));
      }
    }
    result = result + tmp;

    if (dEbUg) {
      cout << "Original Node:\t\t\t"
           << (iter->get_coefficient() < 0 ? "- " : "") << *iter << endl;
      cout << "Expanded Polynmoial:\t" << tmp << endl;
      cout << endl;
    }
  }
  cout << result;
  cout << " = 0";
}
