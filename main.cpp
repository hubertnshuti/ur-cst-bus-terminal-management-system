#include "TerminalSystem.h"
#include <iostream>
using namespace std;

int main() {
    int choice;

    while (true) {
        showMenu();
        cout << "\nEnter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid menu choice. Please enter a number from 1 to 8.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        cin.ignore(10000, '\n');

        switch (choice) {
        case 1:
            addBus();
            break;
        case 2:
            addPassenger();
            break;
        case 3:
            showBusSchedule();
            break;
        case 4:
            showPassengers();
            break;
        case 5:
            startBoarding();
            break;
        case 6:
            delayBus();
            break;
        case 7:
            cancelBus();
            break;
        case 8:
            cout << "Exiting system...\n";
            return 0;
        default:
            cout << "Invalid option. Please choose from 1 to 8.\n";
        }
    }
}
