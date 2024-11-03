/********************************************
* File: clock.cpp
* Author: Kane Miller
* Date: 2024-02-04
********************************************/

#include <iostream>
#include <tuple>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace std;

// Global variables for time keeping
int milHour = 23;
int minute = 59;
int hour = 11;
int second = 55;
bool stop = false;

// Function to determine AM or PM
string morningOrNight(int milHour) {
    return (milHour >= 12 && milHour < 24) ? " P.M." : " A.M.";
}

// Function to print stars for the clock border
void starPrint(int j, int k) {
    for (int m = 0; m < k; m++) {
        cout << string(j, '*') << "  ";
    }
    cout << endl;
}

// Function to check and adjust time variables for overflow
tuple<int, int, int, int> timeCheck() {
    if (second >= 60) {
        second = 0;
        minute++;
    }
    if (minute >= 60) {
        minute = 0;
        hour++;
        milHour++;
    }
    if (hour > 12) {
        hour = 1;
    }
    if (milHour >= 24) {
        milHour = 0;
    }
    return make_tuple(hour, minute, second, milHour);
}

// Function to display the current time
void showTime() {
    int currentHour, currentMinute, currentSecond, currentMilHour;
    tie(currentHour, currentMinute, currentSecond, currentMilHour) = timeCheck();

    cout << setfill('0');
    // Print the 12-hour clock time
    cout << setw(2) << currentHour << ":" << setw(2) << currentMinute << ":" 
         << setw(2) << currentSecond << morningOrNight(currentMilHour) << "     *  *         ";
    // Print the 24-hour clock time
    cout << setw(2) << currentMilHour << ":" << setw(2) << currentMinute << ":" 
         << setw(2) << currentSecond  << "        *"<< endl;
}

// Function to print the time and clock design
void printTime() {
    system("clear");
    starPrint(27, 2);
    cout << "*       12-Hour Clock     *  *      24-Hour Clock      *" << endl;
    cout << "*       ";
    showTime();
    starPrint(27, 2);
    this_thread::sleep_for(chrono::seconds(1));
}

// Function to display the menu and process user input
void menuDisplay() {
    starPrint(27, 1);
    cout << "*    1 - Add One Hour     *" << endl;
    cout << "*    2 - Add One Minute   *" << endl;
    cout << "*    3 - Add One Second   *" << endl;
    cout << "*    4 - Exit Program     *" << endl;
    starPrint(27, 1);

    int dataEdit;
    cin >> dataEdit;

    switch (dataEdit) {
        case 1:
            milHour = (milHour + 1) % 24;
            hour = (hour == 12) ? 1 : (hour + 1) % 13;
            break;
        case 2:
            minute = (minute + 1) % 60;
            // Increment hour if minutes wrap around
            if (minute == 0) {
                milHour = (milHour + 1) % 24;
                hour = (hour == 12) ? 1 : (hour + 1) % 13;
            }
            break;
        case 3:
            second = (second + 1) % 60;
            // Increment minute if seconds wrap around
            if (second == 0) {
                minute = (minute + 1) % 60;
                // Increment hour if minutes wrap around
                if (minute == 0) {
                    milHour = (milHour + 1) % 24;
                    hour = (hour == 12) ? 1 : (hour + 1) % 13;
                }
            }
                    break;
        case 4:
            cout << "Goodbye." << endl;
            stop = true;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

// The main function that runs the clock program
int main() {
    do {
        printTime();
        menuDisplay();
    } while (!stop);

    return 0;
}
