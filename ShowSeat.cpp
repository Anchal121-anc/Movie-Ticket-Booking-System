// OOP: Encapsulation - booking status changes only through bookSeat/cancelSeat.
enum class SeatStatus { AVAILABLE, BOOKED };

class ShowSeat {
private:
    const Seat* physicalSeat;
    SeatStatus status;

public:
    explicit ShowSeat(const Seat* physicalSeat)
        : physicalSeat(physicalSeat), status(SeatStatus::AVAILABLE) {}

    int getNumber() const { return physicalSeat->getNumber(); }
    SeatType getType() const { return physicalSeat->getType(); }
    double getPrice() const { return Seat::price(getType()); }
    SeatStatus getStatus() const { return status; }

    bool isAvailable() const { return status == SeatStatus::AVAILABLE; }

    bool bookSeat() {
        if (!isAvailable()) return false;
        status = SeatStatus::BOOKED;
        return true;
    }

    void cancelSeat() { status = SeatStatus::AVAILABLE; }

    std::string statusName() const {
        return isAvailable() ? "AVAILABLE" : "BOOKED";
    }
};
