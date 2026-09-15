// OOP: Single Responsibility - this class only calculates price.
class PriceCalculator {
public:
    double calculate(const std::vector<ShowSeat*>& selectedSeats) const {
        double total = 0.0;
        for (const ShowSeat* seat : selectedSeats) {
            total += seat->getPrice();
        }
        return total;
    }

    // Compile-time polymorphism: overloaded method for a single seat.
    double calculate(const ShowSeat& seat) const {
        return seat.getPrice();
    }
};
