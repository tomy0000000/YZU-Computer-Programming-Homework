//
//  BuyTickets.h
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef BuyTickets_h
#define BuyTickets_h

#include "BookingDatabase.h"
#include "MovieDatabase.h"

class BuyTickets {
public:
  BuyTickets(MovieDatabase &theMovieDatabase,
             BookingDatabase &theBookingDatabase, string theEmail);
  void execute();

private:
  MovieDatabase &movieDatabase;
  BookingDatabase &bookingDatabase;
  char email[40];

  void selectSeats(Booking &newBooking);
};

#endif
