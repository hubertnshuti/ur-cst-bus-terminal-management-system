#pragma once
#include <string>
using namespace std;

void clearInput();
bool parseTimeToMinutes(const string&, int&);
string minutesToTime(int);
int getValidatedInt(const string&, int);
string getValidatedLine(const string&);
string getValidatedTime(const string&);
