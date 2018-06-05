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

void Movie::setMovieCode(int theMovieCode) {
  movieCode = (theMovieCode > 0 ? theMovieCode : 0);
}

int Movie::getMovieCode() { return movieCode; }

void Movie::setPrices(int thePrices[]) {
  for (int i = 0; i < 4; i++) {
    prices[i] = (thePrices[i] > 0 ? thePrices[i] : 0);
  }
}

int Movie::getPrice(int ticketType) { return prices[ticketType]; }

void Movie::setDates(bool theDates[]) {
  for (int i = 0; i < 4; i++) {
    dates[i] = theDates[i];
  }
}

bool Movie::getDate(int dateCode) { return dates[dateCode]; }

void Movie::setSessionTimes(bool theSessionTimes[]) {
  for (int i = 0; i < 17; i++) {
    sessionTimes[i] = theSessionTimes[i];
  }
}

bool Movie::getSessionTime(int sessionTimeCode) {
  return sessionTimes[sessionTimeCode];
}

void Movie::setOccupiedSeat(int dateCode, int sessionTimeCode, int row,
                            int col) {
  occupiedSeats[dateCode][sessionTimeCode][row][col] = true;
}

bool Movie::getOccupiedSeat(int dateCode, int sessionTimeCode, int row,
                            int col) {
  return occupiedSeats[dateCode][sessionTimeCode][row][col];
}
