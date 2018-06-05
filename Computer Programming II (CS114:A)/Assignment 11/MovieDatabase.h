//
//  MovieDatabase.h
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef MovieDatabase_h
#define MovieDatabase_h

#include "Movie.h"
#include "Vector.h"

class MovieDatabase {
public:
  MovieDatabase();
  ~MovieDatabase();
  // Get Total Amount of Movie
  long getNumMovies();
  Movie getMovie(int movieCode);
  // Toggle a movie seat to occupied (true)
  void setMovieSeat(int movieCode, int dateCode, int sessionTimeCode, int row,
                    int col);
  // Display movie table available for sale
  void displaySessionTimes(char movieNames[][60], char availableDates[][12]);

private:
  vector<Movie> movies;
  void loadMovies();
  void saveMovies();
};

#endif
