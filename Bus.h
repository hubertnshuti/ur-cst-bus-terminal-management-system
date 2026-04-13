#pragma once
#include <string>
using namespace std;

class Bus {
public:
    int busID;
    string route;
    string departureTime;
    int departureMinutes;
    int priority;
    int capacity;
    bool cancelled;
    bool delayed;
    int delayMinutes;

    Bus(int id, string r, string dTime, int dMinutes, int p, int c)
        : busID(id),
          route(r),
          departureTime(dTime),
          departureMinutes(dMinutes),
          priority(p),
          capacity(c),
          cancelled(false),
          delayed(false),
          delayMinutes(0) {}
};
