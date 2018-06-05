//
//  MovieDatabase.cpp
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <fstream>
using std::ifstream;
using std::ios;
using std::ofstream;
#include <iomanip>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include "MovieDatabase.h"

extern char hours[17][8];

MovieDatabase::MovieDatabase() { loadMovies(); }
MovieDatabase::~MovieDatabase() { saveMovies(); }
long MovieDatabase::getNumMovies() { return movies.size(); }
Movie MovieDatabase::getMovie(int movieCode) { return movies[movieCode]; }
void MovieDatabase::setMovieSeat(int movieCode, int dateCode,
                                 int sessionTimeCode, int row, int col) {
  movies[movieCode].setOccupiedSeat(dateCode, sessionTimeCode, row, col);
}

void MovieDatabase::displaySessionTimes(char movieNames[][60],
                                        char availableDates[][12]) {
  cout << endl;
  for (int i = 0; i < movies.size(); i++) {
    cout << i << ".\tMovie:\t\t\t" << movieNames[i] << endl;
    cout << "\tDate:\t\t\t";
    for (int j = 0; j < 4; j++) {
      if (movies[i].getDate(j)) {
        cout << j << ". " << availableDates[j] << "\t";
      }
    }
    cout << endl;
    int printedTime = 0;
    cout << "\tSession Time: \t";
    for (int k = 0; k < 17; k++) {
      if (movies[i].getSessionTime(k)) {
        cout << k << ". " << hours[k] << "\t\t";
        printedTime++;
        if (printedTime % 4 == 0 && k != 16) {
          cout << endl << "\t\t\t\t\t";
        }
      }
    }
    cout << endl
         << endl
         << ((i == movies.size() - 1) ? "--------------------" : "\t\t\t\t\t")
         << "-------------------------------------------------------------"
         << endl;
  }
}

void MovieDatabase::loadMovies() {
  ifstream inFile("Movies.dat", ios::in | ios::binary);
  while (inFile.peek() != EOF) {
    movies.resize(movies.size() + 1);
    inFile.read(reinterpret_cast<char *>(&movies[movies.size() - 1]),
                sizeof(Movie));
  }
  inFile.close();
}

void MovieDatabase::saveMovies() {
  ofstream outFile("Movies.dat", ios::in | ios::binary);
  for (int i = 0; i < movies.size(); i++) {
    outFile.write(reinterpret_cast<const char *>(&movies[i]), sizeof(Movie));
  }
  outFile.close();
}
