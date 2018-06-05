//
//  Movie.cpp
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include "Movie.h"

Movie::Movie() {}
int Movie::getMovieCode() { return movieCode; }
int Movie::getPrice(int ticketType) { return prices[ticketType]; }
bool Movie::getDate(int dateCode) { return dates[dateCode]; }
bool Movie::getSessionTime(int sessionTimeCode) {
  return sessionTimes[sessionTimeCode];
}
bool Movie::getOccupiedSeat(int dateCode, int sessionTimeCode, int row,
                            int col) {
  return occupiedSeats[dateCode][sessionTimeCode][row][col];
}

void Movie::setMovieCode(int theMovieCode) {
  movieCode = (theMovieCode > 0 ? theMovieCode : 0);
}

void Movie::setPrices(int thePrices[]) {
  for (int i = 0; i < 4; i++) {
    prices[i] = (thePrices[i] > 0 ? thePrices[i] : 0);
  }
}

void Movie::setDates(bool theDates[]) {
  for (int i = 0; i < 4; i++) {
    dates[i] = theDates[i];
  }
}

void Movie::setSessionTimes(bool theSessionTimes[]) {
  for (int i = 0; i < 17; i++) {
    sessionTimes[i] = theSessionTimes[i];
  }
}

void Movie::setOccupiedSeat(int dateCode, int sessionTimeCode, int row,
                            int col) {
  occupiedSeats[dateCode][sessionTimeCode][row][col] = true;
}
