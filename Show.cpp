// OOP: Aggregation - a Show refers to an existing Movie and Screen.
// OOP: Composition - Show creates and owns its ShowSeat objects.
class Show {
private:
    int showId;
    const Movie* movie;
    const Screen* screen;
    std::string startTime;
    std::vector<ShowSeat> showSeats;

public:
    Show(int showId, const Movie* movie, const Screen* screen, const std::string& startTime)
        : showId(showId), movie(movie), screen(screen), startTime(startTime) {
        for (const Seat& seat : screen->getSeats()) {
            showSeats.emplace_back(&seat);
        }
    }

    int getShowId() const { return showId; }
    const Movie& getMovie() const { return *movie; }
    const Screen& getScreen() const { return *screen; }
    const std::string& getStartTime() const { return startTime; }
    const std::vector<ShowSeat>& getShowSeats() const { return showSeats; }

    ShowSeat* findShowSeat(int seatNumber) {
        for (ShowSeat& showSeat : showSeats) {
            if (showSeat.getNumber() == seatNumber) return &showSeat;
        }
        return nullptr;
    }

    const ShowSeat* findShowSeat(int seatNumber) const {
        for (const ShowSeat& showSeat : showSeats) {
            if (showSeat.getNumber() == seatNumber) return &showSeat;
        }
        return nullptr;
    }

    void displaySeats() const {
        std::cout << "\nSeat Layout (S=Silver, G=Gold, P=Platinum)\n";
        for (const ShowSeat& seat : showSeats) {
            std::cout << "[" << seat.getNumber() << " "
                      << (seat.isAvailable() ? "AVAILABLE" : "BOOKED") << "]";
            if (seat.getNumber() % 4 == 0) std::cout << '\n';
            else std::cout << "  ";
        }
        std::cout << "\nPrices: SILVER=Rs.150, GOLD=Rs.250, PLATINUM=Rs.400\n";
    }
};
