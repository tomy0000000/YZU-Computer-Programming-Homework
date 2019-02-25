//
//  main.cpp
//  Hw2
//  Haar Wavelet Transform
//
//  Created by Tomy Hsieh on 2018/10/16.
//  Copyright © 2018 Tomy Hsieh. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;

#define DEEBUG false
//typedef float precision_std;
//int precision_cv = CV_32F;

typedef double precision_std;
int precision_cv = CV_64F;

int main(int argc, const char *argv[]) {

  // Read Image
  Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  image.convertTo(image, precision_cv);
  if (!image.data) {
    cout << "Could not open or find the image" << endl;
    return -1;
  }

  // Show Image in New Window
  if (DEEBUG) {
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", image);
    waitKey(0);
  }

  // Read Haar Matrix
  vector<vector<precision_std> > haar_vec;
  ifstream matIn(argv[2]);
  for (string line; getline(matIn, line);) {
    vector<precision_std> row;
    size_t prev_pos = -1;
    size_t pos      = line.find(",");
    for (; pos != string::npos; pos = line.find(",", pos + 1)) {
      string num_str = line.substr(prev_pos + 1, pos - prev_pos - 1);
      precision_std val     = atof(num_str.c_str());
      row.push_back(val);
      prev_pos = pos;
    }
    precision_std last_num = atof(line.substr(prev_pos + 1).c_str());
    row.push_back(last_num);
    haar_vec.push_back(row);
  }
  Mat haar((int)haar_vec.size(), (int)haar_vec[0].size(), precision_cv);
  for (int row = 0; row < haar_vec.size(); row++) {
    for (int col = 0; col < haar_vec[0].size(); col++) {
      haar.at<precision_std>(row, col) = haar_vec[row][col];
    }
  }

  // Split Image to Blue, Green, Red Channels
  vector<Mat> rgbChannels(3);
  split(image, rgbChannels);

  // Execute Transformation
  size_t r_times = image.rows / haar.rows;
  size_t c_times = image.cols / haar.cols;
  for (int channel = 0; channel < 3; channel++) {
    for (int row = 0; row < r_times; row++) {
      for (int col = 0; col < c_times; col++) {
        Rect range(col * haar.cols, row * haar.rows, haar.cols, haar.rows);
        Mat tmpMat = rgbChannels[channel](range);
        tmpMat     = haar.t() * tmpMat * haar;
        for (int row_tmp = 0; row_tmp < tmpMat.rows; row_tmp++) {
          for (int col_tmp = 0; col_tmp < tmpMat.cols; col_tmp++) {
            precision_std tmp = tmpMat.at<precision_std>(col_tmp, row_tmp);
            if (tmp < 0) {
              tmpMat.at<precision_std>(col_tmp, row_tmp) = 0;
            } else if (tmp > 255) {
              tmpMat.at<precision_std>(col_tmp, row_tmp) = 255;
            }
          }
        }
      }
    }
  }

  // Write Image from Channels
  Mat final_img;
  merge(rgbChannels, final_img);
  imwrite(argv[3], final_img);
}
