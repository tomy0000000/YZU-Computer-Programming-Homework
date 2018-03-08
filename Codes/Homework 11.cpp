//
//  main.cpp
//  Hw11
//  Simplified Vieshow Cinemas Ticket System
//
//  Created by Tomy Hsieh on 2017/12/5.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

struct showTime {
    int movieCode;
    char dates[12];
    int numSessions;
    char sessionTimes[11][8];
};

struct movieMenu {
    int movieCode;
    char name[50];
};

void loadFromTableFile(ifstream &inTableFile, showTime Table[], int &tableNum);                                         //Load File Data to Table
void printLoadedSession(showTime Table[], int tableNum);                                                                //Tester to Print Loaded Datas
int inputAnInteger(int begin, int end);                                                                                 //Return a Valid Input
void printMovies(movieMenu Menu[], int movieNum);                                                                       //Print Movies
void printAvailableDates(showTime Table[], int tableNum, showTime Booking, int &dateChoices);                           //Print Dates
void printAvailableSessionTimes(showTime Table[], int tableNum, showTime Booking, int &sessionChoices);                 //Print Session Times

/*
 movieMenu:
    Menu[100]               //movieCode and movieName
 showTime:
    Table[200]              //Load Available Session Times from File
    Booking                 //Save User Choice
 int:
    movieNum                //Number of datas stored in Menu[]
    tableNum                //Number of datas stored in Table[]
    dateOptions             //Available Option Number for Dates
    sessionOptions          //Available Option Number for Session Times
    dateChoice              //User Selected Number of Date
    sessionChoice           //User Selected Number of Session Time
*/

int main() {
    
    //Movie Menu Initialization
    movieMenu Menu[100];
    int movieNum = 27;
    for (int i = 0; i<movieNum; i++) {
        Menu[i].movieCode = i;
    }
    strcpy(Menu[0].name, "ROMEO AND JULIET SHAKESPEARE");
    strcpy(Menu[1].name, "STAR WARS THE LAST JEDI");
    strcpy(Menu[2].name, "THE WINTERS TALE SHAKESPEARE");
    strcpy(Menu[3].name, "THE GREAT BUDDHA");
    strcpy(Menu[4].name, "WONDER");
    strcpy(Menu[5].name, "SUBURBICON");
    strcpy(Menu[6].name, "DADDYS HOME 2");
    strcpy(Menu[7].name, "PADDINGTON 2");
    strcpy(Menu[8].name, "TAKE ME TO THE MOON");
    strcpy(Menu[9].name, "SHUTTLE LIFE");
    strcpy(Menu[10].name, "TAP THE LAST SHOW");
    strcpy(Menu[11].name, "VICEROYS HOUSE");
    strcpy(Menu[12].name, "BASE ON A TRUE STORY");
    strcpy(Menu[13].name, "MIDNIGHT RUNNERS");
    strcpy(Menu[14].name, "THE BOLD THE CORRUPT AND THE BEAUTIFUL");
    strcpy(Menu[15].name, "COCO AND OLAFS FROZEN ADVENTURE");
    strcpy(Menu[16].name, "MANHUNT");
    strcpy(Menu[17].name, "SECRET SUPERSTAR");
    strcpy(Menu[18].name, "BATTLE OF THE SEXES");
    strcpy(Menu[19].name, "MUMON");
    strcpy(Menu[20].name, "GOOD TIME");
    strcpy(Menu[21].name, "ONLY THE BRAVE");
    strcpy(Menu[22].name, "POKEMON THE MOVIE I CHOOSE YOU");
    strcpy(Menu[23].name, "LOVE EDUCATION");
    strcpy(Menu[24].name, "JUSTICE LEAGUE");
    strcpy(Menu[25].name, "JIGSAW");
    strcpy(Menu[26].name, "THOR RAGNAROK");
    
    //System Initialization
    showTime Table[200];
    int tableNum = 0;
    ifstream inSessionFile;
    loadFromTableFile(inSessionFile, Table, tableNum);
    showTime Booking;
    int dateOptions = 0, sessionOptions = 0;
    
    //Menu of Movie
    cout << "Welcome to Vieshow Cinemas Taipei Hsing Yi system" << endl << endl;
    printMovies(Menu, movieNum);
    cout << endl;
    Booking.movieCode = -1;
    while (Booking.movieCode == -1) {
        cout << "Enter movie code (0 - " << movieNum - 1 << "): ";
        Booking.movieCode = inputAnInteger(0, movieNum - 1);
        if (Booking.movieCode == -1) {
            cout << "Input Error!" << endl;
        }
    }
    cout << endl;
    
    //Menu of Dates
    printAvailableDates(Table, tableNum, Booking, dateOptions);
    int dateChoice = -1;
    while (dateChoice == -1) {
        cout << "Enter date code (0 - " << dateOptions - 1 << "): ";
        dateChoice = inputAnInteger(0, dateOptions - 1);
        if (dateChoice == -1) {
            cout << "Input Error!" << endl;
        }
    }
    cout << endl;
    
    //Save Date
    int cnt = 0;
    for (int i = 0; i<tableNum; i++) {
        if (Table[i].movieCode == Booking.movieCode) {
            if (dateChoice == cnt) {
                strcpy(Booking.dates, Table[i].dates);
                break;
            }
            else {
                cnt++;
            }
        }
    }
    
    //Menu of Session Times
    printAvailableSessionTimes(Table, tableNum, Booking, sessionOptions);
    int sessionChoice = -1;
    while (sessionChoice == -1) {
        cout << "Enter session time code (0 - " << sessionOptions - 1 << "): ";
        sessionChoice = inputAnInteger(0, sessionOptions - 1);
        if (sessionChoice == -1) {
            cout << "Input Error!" << endl;
        }
    }
    
    //Save Session Time
    Booking.numSessions = 1;
    cnt = 0;
    for (int i = 0; i<tableNum; i++) {
        if (Table[i].movieCode == Booking.movieCode && strcmp(Table[i].dates, Booking.dates) == 0) {
            for (int j = 0; j<Table[i].numSessions; j++) {
                if (sessionChoice == cnt) {
                    strcpy(Booking.sessionTimes[0], Table[i].sessionTimes[j]);
                    break;
                }
                else {
                    cnt++;
                }
            }
        }
    }
    
    //Final Results Printing
    cout << endl;
    cout << Menu[Booking.movieCode].name << endl;
    cout << Booking.dates << " " << Booking.sessionTimes[0] << endl << endl;
    
}

void loadFromTableFile(ifstream &inTableFile, showTime Table[], int &tableNum) {
    
    inTableFile.open("Session Times.dat", ios::in | ios::binary);
    while (inTableFile.peek() != EOF) {
        inTableFile.read(reinterpret_cast<char*>(&Table[tableNum]), sizeof(showTime));
        tableNum++;
    }
    //    printLoadedSession(Table, TableNum);
    inTableFile.close();
    
}

void printLoadedSession(showTime Table[], int tableNum) {
    for (int i = 0; i<tableNum; i++) {
        cout << Table[i].movieCode << "\t";
        cout << Table[i].dates << "\t";
        cout << Table[i].numSessions << "\t";
        for (int j = 0; j<Table[i].numSessions; j++) {
            cout << Table[i].sessionTimes[j] << "\t";
        }
        cout << endl;
    }
}

int inputAnInteger(int begin, int end) {
    int iInput;
    cin >> iInput;
    return (iInput >= begin && iInput <= end) ? iInput : -1;
}

void printMovies(movieMenu Menu[], int movieNum) {
    for (int i = 0; i<movieNum; i++) {
        cout << Menu[i].movieCode << "." << Menu[i].name << endl;
    }
}

void printAvailableDates(showTime Table[], int tableNum, showTime Booking, int &dateChoices) {
    for (int i = 0; i<tableNum; i++) {
        if (Table[i].movieCode == Booking.movieCode) {
            cout << dateChoices << ". " << Table[i].dates << endl;
            dateChoices++;
        }
    }
    cout << endl;
}

void printAvailableSessionTimes(showTime Table[], int tableNum, showTime Booking, int &sessionChoices) {
    for (int i = 0; i<tableNum; i++) {
        if (Table[i].movieCode == Booking.movieCode && strcmp(Table[i].dates, Booking.dates) == 0) {
            for (int j = 0; j<Table[i].numSessions; j++) {
                cout << sessionChoices << ". " << Table[i].sessionTimes[j] << endl;
                sessionChoices++;
            }
        }
    }
    cout << endl;
}


