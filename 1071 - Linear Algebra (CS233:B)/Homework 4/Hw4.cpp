//
//  main.cpp
//  Hw4
//  Least Squares Problem
//
//  Created by Tomy Hsieh on 2019/1/2.
//  Copyright © 2019 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, const char *argv[]) {
  
  ifstream inFile(argv[1]);
  vector<double> v2_vec, y_vec;
  double v2_tmp, y_tmp;
  while (inFile >> v2_tmp >> y_tmp) {
    v2_vec.push_back(v2_tmp);
    y_vec.push_back(y_tmp);
  }
  Mat C_mat, y_mat(y_vec), Out;
  hconcat(Mat(vector<double>(y_vec.size(), 1), true), Mat(v2_vec), C_mat);
  Out = (C_mat.t() * C_mat).inv() * C_mat.t() * y_mat;
  cout << fixed << setprecision(4) << Out.at<double>(0, 0) << " " << Out.at<double>(0, 1);
  
}
