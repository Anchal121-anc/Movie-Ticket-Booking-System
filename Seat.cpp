// OOP: Encapsulation - seat number/type are private and immutable through controlled access.
enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    int number;
    SeatType type;

public:
    Seat(int number, SeatType type) : number(number), type(type) {}

    int getNumber() const { return number; }
    SeatType getType() const { return type; }

    static std::string typeName(SeatType type) {
        switch (type) {
            case SeatType::SILVER: return "SILVER";
            case SeatType::GOLD: return "GOLD";
            case SeatType::PLATINUM: return "PLATINUM";
        }
        return "UNKNOWN";
    }

    static double price(SeatType type) {
        constexpr double SILVER_PRICE = 150.0;
        constexpr double GOLD_PRICE = 250.0;
        constexpr double PLATINUM_PRICE = 400.0;
        switch (type) {
            case SeatType::SILVER: return SILVER_PRICE;
            case SeatType::GOLD: return GOLD_PRICE;
            case SeatType::PLATINUM: return PLATINUM_PRICE;
        }
        return 0.0;
    }
};
