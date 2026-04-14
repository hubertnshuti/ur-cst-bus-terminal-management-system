#include "TerminalSystem.h"
#include "Bus.h"
#include "CompareBus.h"
#include "Utils.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

priority_queue<Bus, vector<Bus>, CompareBus> busQueue;
queue<string> passengerQueue;


// we copy the queue because priority_queue doesn't allow direct search
bool busIDExists(int id) {
    priority_queue<Bus, vector<Bus>, CompareBus> temp = busQueue;

    while (!temp.empty()) {
        if (temp.top().busID == id) {
            return true;
        }
        temp.pop();
    }

    return false;
}


void addBus() {
    int id, pri, cap, depMinutes;
    string route, depTime;

    while (true) {
        id = getValidatedInt("\nEnter Bus ID: ", 1);

        if (busIDExists(id)) {
            cout << "Bus ID already exists. Please enter a unique Bus ID.\n";
            continue;
        }
        break;
    }

    route = getValidatedLine("Enter Route: ");
    depTime = getValidatedTime("Enter Departure Time (HH:MM, example 08:30): ");

    // convert time once so comparisons later are easy
    parseTimeToMinutes(depTime, depMinutes);

    pri = getValidatedInt("Enter Priority (lower number = higher priority): ", 1);
    cap = getValidatedInt("Enter Capacity: ", 1);

    busQueue.push(Bus(id, route, depTime, depMinutes, pri, cap));

    cout << "Bus added successfully.\n";
}


void addPassenger() {
    string name = getValidatedLine("Enter Passenger Name: ");
    passengerQueue.push(name);

    cout << "Passenger added to waiting queue.\n";
}


void showPassengers() {
    if (passengerQueue.empty()) {
        cout << "No passengers waiting.\n";
        return;
    }

    // use a copy so original queue stays unchanged
    queue<string> temp = passengerQueue;

    while (!temp.empty()) {
        cout << "- " << temp.front() << endl;
        temp.pop();
    }
}


void showBusSchedule() {
    if (busQueue.empty()) {
        cout << "No buses scheduled.\n";
        return;
    }

    // priority_queue can't be iterated directly → copy it
    priority_queue<Bus, vector<Bus>, CompareBus> temp = busQueue;

    while (!temp.empty()) {
        Bus b = temp.top();
        temp.pop();

        cout << "Bus ID: " << b.busID
             << " | Route: " << b.route
             << " | Departure: " << b.departureTime
             << " | Priority: " << b.priority
             << " | Capacity: " << b.capacity;

        if (b.delayed) {
            cout << " | Delayed by " << b.delayMinutes << " mins";
        }

        if (b.cancelled) {
            cout << " | Cancelled";
        }

        cout << endl;
    }
}


void cancelBus() {
    if (busQueue.empty()) {
        cout << "No buses available.\n";
        return;
    }

    int id = getValidatedInt("Enter Bus ID to cancel: ", 1);

    bool found = false;
    priority_queue<Bus, vector<Bus>, CompareBus> temp;

    while (!busQueue.empty()) {
        Bus b = busQueue.top();
        busQueue.pop();

        // we must rebuild the queue because we can't update inside it directly
        if (b.busID == id) {
            b.cancelled = true;
            found = true;

            cout << "Bus " << id << " cancelled successfully.\n";
        }

        temp.push(b);
    }

    busQueue = temp;

    if (!found) {
        cout << "Bus ID not found.\n";
    }
}


void delayBus() {
    if (busQueue.empty()) {
        cout << "No buses available.\n";
        return;
    }

    int id = getValidatedInt("Enter Bus ID to delay: ", 1);
    int minutes = getValidatedInt("Enter delay in minutes: ", 1);

    bool found = false;
    priority_queue<Bus, vector<Bus>, CompareBus> temp;

    while (!busQueue.empty()) {
        Bus b = busQueue.top();
        busQueue.pop();

        if (b.busID == id) {
            // delay changes actual departure time (not just a label)
            b.delayed = true;
            b.delayMinutes += minutes;
            b.departureMinutes += minutes;

            // convert back to readable time
            b.departureTime = minutesToTime(b.departureMinutes);

            found = true;

            cout << "Bus " << id << " delayed by " << minutes
                 << " minutes. New departure time: " << b.departureTime << endl;
        }

        temp.push(b);
    }

    busQueue = temp;

    if (!found) {
        cout << "Bus ID not found.\n";
    }
}


void startBoarding() {
    if (busQueue.empty()) {
        cout << "No buses available.\n";
        return;
    }

    // skip cancelled buses before boarding
    while (!busQueue.empty() && busQueue.top().cancelled) {
        busQueue.pop();
    }

    if (busQueue.empty()) {
        cout << "No active buses available for boarding.\n";
        return;
    }

    Bus bus = busQueue.top();
    busQueue.pop();

    cout << "\nBoarding Bus " << bus.busID
         << " (Route: " << bus.route
         << ", Departure: " << bus.departureTime << ")\n";

    int seats = bus.capacity;

    // take passengers in FIFO order until full
    while (seats > 0 && !passengerQueue.empty()) {
        cout << passengerQueue.front() << " boarded.\n";
        passengerQueue.pop();
        seats--;
    }

    if (seats == 0)
        cout << "Bus is full.\n";

    if (passengerQueue.empty())
        cout << "No more passengers waiting.\n";

    cout << "Bus " << bus.busID << " departed.\n";
}


void showMenu() {
    cout << "\n========== CITY BUS TERMINAL SYSTEM ==========\n";
    cout << "1. Add Bus\n";
    cout << "2. Add Passenger\n";
    cout << "3. Show Bus Schedule\n";
    cout << "4. Show Passenger Queue\n";
    cout << "5. Start Boarding\n";
    cout << "6. Delay Bus\n";
    cout << "7. Cancel Bus\n";
    cout << "8. Exit\n";
}