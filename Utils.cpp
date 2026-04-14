#include "Utils.h"
#include <cctype>
#include <iostream>
#include <limits>
using namespace std;


// simple check: input should not be empty
bool isValidName(const string& text) {
    return !text.empty();
}


void clearInput() {
    // reset error state + remove leftover input
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


bool parseTimeToMinutes(const string& timeStr, int& totalMinutes) {
    // enforce format HH:MM
    if (timeStr.length() != 5 || timeStr[2] != ':') {
        return false;
    }

    // ensure all characters are digits except ':'
    if (!isdigit(timeStr[0]) || !isdigit(timeStr[1]) ||
        !isdigit(timeStr[3]) || !isdigit(timeStr[4])) {
        return false;
    }

    int hour = stoi(timeStr.substr(0, 2));
    int minute = stoi(timeStr.substr(3, 2));

    // basic time validation
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return false;
    }

    // convert to minutes → easier for comparison and delay
    totalMinutes = hour * 60 + minute;
    return true;
}


string minutesToTime(int totalMinutes) {
    // keep time within 24-hour range
    totalMinutes %= (24 * 60);
    if (totalMinutes < 0) {
        totalMinutes += (24 * 60);
    }

    int hour = totalMinutes / 60;
    int minute = totalMinutes % 60;

    // format back to HH:MM
    string hh = (hour < 10 ? "0" : "") + to_string(hour);
    string mm = (minute < 10 ? "0" : "") + to_string(minute);

    return hh + ":" + mm;
}


int getValidatedInt(const string& prompt, int minValue) {
    int value;

    while (true) {
        cout << prompt;
        cin >> value;

        // handles non-numeric input like "abc"
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            clearInput();
            continue;
        }

        // ensures value meets minimum requirement
        if (value < minValue) {
            cout << "Invalid input. Value must be at least " << minValue << ".\n";
            clearInput();
            continue;
        }

        clearInput();
        return value;
    }
}


string getValidatedLine(const string& prompt) {
    string input;

    while (true) {
        cout << prompt;
        getline(cin, input);

        if (!isValidName(input)) {
            cout << "Invalid input. Field cannot be empty.\n";
            continue;
        }

        return input;
    }
}


string getValidatedTime(const string& prompt) {
    string timeStr;
    int minutes;

    while (true) {
        cout << prompt;
        getline(cin, timeStr);

        // reuse parser to validate time format
        if (!parseTimeToMinutes(timeStr, minutes)) {
            cout << "Invalid time format. Please use HH:MM (example: 08:30 or 14:05).\n";
            continue;
        }

        return timeStr;
    }
}