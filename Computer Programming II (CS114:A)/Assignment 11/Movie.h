//
//  Movie.h
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef Movie_h
#define Movie_h

class Movie {
public:
  Movie();
  int getMovieCode();
  int getPrice(int ticketType);
  bool getDate(int dateCode);
  bool getSessionTime(int sessionTimeCode);
  bool getOccupiedSeat(int dateCode, int sessionTimeCode, int row, int col);
  void setMovieCode(int theMovieCode);
  void setPrices(int thePrices[]);
  void setDates(bool theDates[]);
  void setSessionTimes(bool theSessionTimes[]);
  void setOccupiedSeat(int dateCode, int sessionTimeCode, int row, int col);

private:
  int movieCode;
  int prices[4];
  bool dates[4];
  bool sessionTimes[17];
  bool occupiedSeats[4][17][8][12];
};

#endif
