//
//  main.cpp
//  Hw1
//
//  Created by Tomy Hsieh on 2018/9/19.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

#define PI 3.14159265

int gcd(int m, int n) {
  return ((n == 0) ? m : gcd(n, m % n));
}

class dots {
public:
  dots(double cord_x, double cord_y) : x(cord_x), y(cord_y) {}
  bool operator<(const dots &rhs) const {
    return ((x != rhs.x) ? (x < rhs.x) : (y < rhs.y));
  }
  double x, y;
};

class slope {
public:
  slope(dots d1, dots d2) {
    int dist_x = d1.x - d2.x, dist_y = d1.y - d2.y,
        dist_gcd = gcd(dist_x, dist_y);
    dist_x /= dist_gcd;
    dist_y /= dist_gcd;
    min_x = (dist_x < 0) ? dist_x * -1 : dist_x;
    min_y = (dist_x < 0) ? dist_y * -1 : dist_y;
  }
  bool operator<(const slope &rhs) const {
    return ((min_x != rhs.min_x) ? (min_x < rhs.min_x) : (min_y < rhs.min_y));
  }
  int min_x, min_y;
};

int main(int argc, const char *argv[]) {

  // DB Init
  map<slope, set<dots> > slope_db;
  vector<dots> dots_db;
  dots center(0, 0);

  // Read Input
  ifstream fin(argv[1]);
  for (string line; getline(fin, line);) {
    int tmp_x = atoi(line.substr(0, line.find(',')).c_str()),
        tmp_y = atoi(line.substr(line.find(',') + 1).c_str());
    center.x += tmp_x;
    center.y += tmp_y;
    dots_db.push_back(dots(tmp_x, tmp_y));
  }
  center.x /= dots_db.size();
  center.y /= dots_db.size();

  // Scan through Dot Pairs
  int theSlope_x = 0, theSlope_y = 0;
  for (vector<dots>::iterator it = dots_db.begin(); it != dots_db.end(); ++it) {
    for (vector<dots>::iterator it2 = it + 1; it2 != dots_db.end(); ++it2) {
      slope tmp(*it, *it2);
      map<slope, set<dots> >::iterator it3 = slope_db.find(tmp);
      if (it == dots_db.begin()) {
        slope_db.insert(pair<slope, set<dots> >(tmp, set<dots>()));
        slope_db[tmp].insert(*it);
        slope_db[tmp].insert(*it2);
      } else if (it3 != slope_db.end()) {
        it3->second.insert(*it);
        it3->second.insert(*it2);
      }
    }

    // Eliminate Slopes
    for (map<slope, set<dots> >::iterator it2 = slope_db.begin();
         it2 != slope_db.end();) {
      if (it2->second.find(*it) == it2->second.end()) {
        slope_db.erase(it2++);
      } else {
        ++it2;
      }
    }
    // Check if Slope is Found
    if (slope_db.size() == 1) {
      theSlope_x = slope_db.begin()->first.min_x;
      theSlope_y = slope_db.begin()->first.min_y;
      break;
    }
  }

  // Calculate Rotation Degree
  double current_degree =
             (theSlope_x == 0)
                 ? 90
                 : (atan((double)(theSlope_y) / (double)(theSlope_x)) * 180 /
                    PI),
         rev_rotation_degree = (current_degree < 0) ? abs(current_degree) + 90
                                                    : 90 - current_degree;

  // Print Results
  for (vector<dots>::iterator it = dots_db.begin(); it != dots_db.end(); ++it) {
    double cord_x = (it->x - center.x) * cos(rev_rotation_degree * PI / 180) -
                    (it->y - center.y) * sin(rev_rotation_degree * PI / 180) +
                    center.x,
           cord_y = (it->x - center.x) * sin(rev_rotation_degree * PI / 180) +
                    (it->y - center.y) * cos(rev_rotation_degree * PI / 180) +
                    center.y;
    cout << fixed << setprecision(6) << cord_x << "," << cord_y << endl;
  }
}
