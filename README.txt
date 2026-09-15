# TCS-504 Assignment 1 — Movie Ticket Booking System

## Build
Requirement: C++17 compiler.

### Windows / MinGW
```text
g++ -std=c++17 main.cpp -o MovieBooking.exe
MovieBooking.exe
```

### Linux / WSL
```text
g++ -std=c++17 main.cpp -o MovieBooking
./MovieBooking
```

The assignment explicitly says one class per file and no header files. Therefore every class is in its own `.cpp` file. `main.cpp` includes those `.cpp` files in dependency order so the project compiles as one translation unit.

## Features implemented
F1 movies, F2 shows, F3 seat layout, F4 booking with already-booked rejection, F5 Silver/Gold/Platinum pricing, F6 UPI/Card/Cash payment, F7 ticket printing, F8 cancellation and seat release.

## Demo edge cases
- Book an available seat, then try booking it again.
- Cancel the confirmed booking and display the same show's seats.
- Invalid menu/seat input is rejected without crashing.

## Important note about failed payment
The interactive demo payment classes are successful payment implementations. The design still explicitly handles a `false` result from `Payment::pay()` by releasing all temporarily booked seats and leaving the booking unconfirmed. This is the required failure behavior and can be unit-tested by adding a test Payment subclass that returns false.
