// OOP: Composition - Screen owns its Seat objects.
class Screen {
private:
    int screenNumber;
    std::vector<Seat> seats;

    void createDefaultSeats() {
        for (int number = 1; number <= 20; ++number) {
            SeatType type = number <= 8 ? SeatType::SILVER
                           : number <= 15 ? SeatType::GOLD
                                          : SeatType::PLATINUM;
            seats.emplace_back(number, type);
        }
    }

public:
    explicit Screen(int screenNumber) : screenNumber(screenNumber) {
        createDefaultSeats();
    }

    int getScreenNumber() const { return screenNumber; }
    const std::vector<Seat>& getSeats() const { return seats; }

    const Seat* findSeat(int seatNumber) const {
        for (const Seat& seat : seats) {
            if (seat.getNumber() == seatNumber) return &seat;
        }
        return nullptr;
    }
};
