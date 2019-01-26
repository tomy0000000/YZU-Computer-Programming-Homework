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
  BookingDatabase();
  ~BookingDatabase();
  // Add newBooking to booking database
  void addBooking(Booking newBooking);
  // Check if given email has any booking history
  bool existingBooking(string email);
  // Display details of the booking history
  void displayBookings(string email, MovieDatabase &movieDatabase);

private:
  vector<Booking> bookings;
  void loadBookings();
  void saveBookings();
};

#endif
