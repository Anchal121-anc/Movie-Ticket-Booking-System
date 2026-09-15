#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <set>
#include <iomanip>
#include <limits>

// No header files are used, as required by the assignment.
// Each class is kept in its own .cpp file and included here to build one program.
#include "Movie.cpp"
#include "Seat.cpp"
#include "Screen.cpp"
#include "Cinema.cpp"
#include "ShowSeat.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Booking.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"
#include "CinemaMenu.cpp"

int main() {
    Cinema cinema("PVR Dehradun");
    cinema.addScreen(1);
    cinema.addScreen(2);

    std::vector<Movie> movies;
    movies.emplace_back("Interstellar", "English", 169);
    movies.emplace_back("3 Idiots", "Hindi", 170);
    movies.emplace_back("Demon Slayer", "Japanese", 120);

    std::vector<Show> shows;
    int showId = 1;
    shows.emplace_back(showId++, &movies[0], cinema.findScreen(1), "10:00 AM");
    shows.emplace_back(showId++, &movies[0], cinema.findScreen(2), "06:30 PM");
    shows.emplace_back(showId++, &movies[1], cinema.findScreen(1), "01:30 PM");
    shows.emplace_back(showId++, &movies[2], cinema.findScreen(2), "09:00 PM");

    BookingService bookingService;
    CinemaMenu menu(cinema, movies, shows, bookingService);
    menu.run();

    return 0;
}
