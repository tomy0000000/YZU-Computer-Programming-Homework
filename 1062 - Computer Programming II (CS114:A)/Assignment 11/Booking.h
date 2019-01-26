//
//  Booking.h
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef Booking_h
#define Booking_h

#include <string>
using std::string;
#include "MovieDatabase.h"

class Booking {
public:
  Booking();
  string getEmail();
  int getMovieCode();
  int getDateCode();
  int getSessionTimeCode();
  int getNumTickets(int ticketType);
  string getSeletedSeat(int number);
  void setEmail(string theEmail);
  void setMovieCode(int theMovieCode);
  void setDateCode(int theDateCode);
  void setSessionTimeCode(int theSessionTimeCode);
  void setNumTickets(int theNumTickets[]);
  void setSeletedSeats(string theSeletedSeats[], int numSeats);
  void displayBooking(MovieDatabase &movieDatabase);

private:
  char email[40];
  int movieCode;
  int dateCode;
  int sessionTimeCode;
  int numTickets[4];
  // For Adult, Concession, Disability, Elderly ticket Respectivly
  char seletedSeats[24][3]; // Seleted Seats Number
};

#endif
