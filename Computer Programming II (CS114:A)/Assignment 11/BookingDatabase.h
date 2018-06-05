//
//  BookingDatabase.h
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef BookingDatabase_h
#define BookingDatabase_h

#include "Booking.h"
#include "Vector.h"

class BookingDatabase {
public:
  BookingDatabase();  // calls loadBookings()
  ~BookingDatabase(); // calls saveBookings()

  // adds a booking object to the end of the vector bookings
  void addBooking(Booking newBooking);

  // returns true if there is a booking object containing specified email
  bool existingBooking(string email);

  void displayBookings(string email, MovieDatabase &movieDatabase);

private:
  vector<Booking> bookings; // vector of the bookings
  void loadBookings();      // loads bookings from the file Bookings.dat
  void saveBookings();      // stores bookings into the file Bookings.dat
};

#endif
