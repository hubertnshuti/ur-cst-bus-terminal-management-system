# City Bus Terminal System

A C++ console-based application that simulates how a bus terminal manages buses and passengers using core data structures.

---

## Features

- Add buses with:
  - ID
  - Route
  - Departure time (HH:MM)
  - Priority
  - Capacity

- Add passengers to a waiting queue
- Display bus schedule
- Display passenger queue
- Delay a bus (updates actual departure time)
- Cancel a bus
- Start boarding process

---

## Data Structures Used

### Queue (FIFO)
Used for passengers:
- First come → first served

### Priority Queue
Used for buses:
- Lower priority number → higher importance
- If same priority → earlier departure time goes first

---

## How It Works

- Passengers wait in a normal queue
- Buses are managed using a priority queue
- Boarding always selects:
  1. Highest priority bus
  2. If equal priority → earliest departure time

---

## Time Handling

- Input format: HH:MM (example: 08:30)
- Internally converted to minutes for:
  - comparison
  - delay calculations

---

## How to Run

### Using script
```bash
./build.sh
```

### Manual compilation
```bash
g++ main.cpp Utils.cpp TerminalSystem.cpp -o app
./app
```

---

## Project Structure

```
Bus.h                - Bus class definition
CompareBus.h         - Comparator for priority queue
Utils.h / Utils.cpp  - Input validation and time utilities
TerminalSystem.cpp   - Core system logic
main.cpp             - Entry point and menu
```

---

## Authors

- Hubert  
- NSG  
- Enock  