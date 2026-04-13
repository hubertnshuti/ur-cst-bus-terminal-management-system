#pragma once
#include "Bus.h"

class CompareBus {
public:
    bool operator()(const Bus& a, const Bus& b) const {
        if (a.priority != b.priority) {
            return a.priority > b.priority;
        }

        return a.departureMinutes > b.departureMinutes;
    }
};
