// OOP: Dependency Inversion - BookingService receives a Payment abstraction.
// OOP: Association - Customer uses BookingService; service does not own Customer.
class BookingService {
private:
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;
    std::vector<std::unique_ptr<Booking>> bookings;

    bool validateSeatSelection(Show& show, const std::vector<int>& seatNumbers,
                               std::vector<ShowSeat*>& selectedSeats) const {
        if (seatNumbers.empty()) {
            std::cout << "No seats selected.\n";
            return false;
        }

        for (int seatNumber : seatNumbers) {
            ShowSeat* seat = show.findShowSeat(seatNumber);
            if (seat == nullptr) {
                std::cout << "Invalid seat number: " << seatNumber << '\n';
                return false;
            }
            if (!seat->isAvailable()) {
                std::cout << "Seat " << seatNumber << " is already BOOKED.\n";
                return false;
            }
            selectedSeats.push_back(seat);
        }
        return true;
    }

    bool hasDuplicateSeats(const std::vector<int>& seatNumbers) const {
        std::set<int> uniqueSeats(seatNumbers.begin(), seatNumbers.end());
        return uniqueSeats.size() != seatNumbers.size();
    }

    void releaseSeats(Show& show, const std::vector<int>& seatNumbers) const {
        for (int seatNumber : seatNumbers) {
            ShowSeat* seat = show.findShowSeat(seatNumber);
            if (seat != nullptr) seat->cancelSeat();
        }
    }

public:
    // Dependency Injection: payment is supplied by caller; service does not create a
    // concrete CardPayment/UpiPayment/CashPayment.
    Booking* bookTicket(Customer& customer, Show& show,
                        const std::vector<int>& seatNumbers, Payment& payment) {
        if (hasDuplicateSeats(seatNumbers)) {
            std::cout << "Duplicate seat number entered. Booking rejected.\n";
            return nullptr;
        }

        std::vector<ShowSeat*> selectedSeats;
        if (!validateSeatSelection(show, seatNumbers, selectedSeats)) {
            return nullptr;
        }

        const double total = priceCalculator.calculate(selectedSeats);
        std::cout << "Total amount: Rs." << std::fixed << std::setprecision(2) << total << '\n';

        // Temporarily reserve seats before payment; failed payment releases them.
        for (ShowSeat* seat : selectedSeats) seat->bookSeat();

        std::unique_ptr<Booking> pendingBooking =
            std::make_unique<Booking>(customer, &show, seatNumbers, total);

        // Runtime polymorphism: Payment* can refer to UPI/Card/Cash.
        Payment* paymentPointer = &payment;
        const bool paid = paymentPointer->pay(total);

        if (!paid) {
            releaseSeats(show, seatNumbers);
            std::cout << "Payment failed. Booking NOT confirmed. Seats released.\n";
            return nullptr;
        }

        pendingBooking->confirm();
        bookings.push_back(std::move(pendingBooking));
        Booking* confirmedBooking = bookings.back().get();

        ticketPrinter.print(*confirmedBooking, payment);
        return confirmedBooking;
    }

    bool cancelBooking(int bookingId) {
        for (const auto& booking : bookings) {
            if (booking->getBookingId() == bookingId) {
                if (booking->getStatus() != "CONFIRMED") {
                    std::cout << "Only a confirmed booking can be cancelled.\n";
                    return false;
                }

                releaseSeats(booking->getShow(), booking->getSeatNumbers());
                booking->cancel();
                std::cout << "Booking " << bookingId
                          << " cancelled. Seats are AVAILABLE again.\n";
                return true;
            }
        }

        std::cout << "Booking ID not found.\n";
        return false;
    }

    void printAllBookings() const {
        if (bookings.empty()) {
            std::cout << "No bookings found.\n";
            return;
        }

        std::cout << "\nBooking Records\n";
        for (const auto& booking : bookings) {
            std::cout << "ID: " << booking->getBookingId()
                      << " | Movie: " << booking->getShow().getMovie().getTitle()
                      << " | Seats: ";
            for (int seat : booking->getSeatNumbers()) std::cout << seat << ' ';
            std::cout << "| Amount: Rs." << std::fixed << std::setprecision(2)
                      << booking->getTotalAmount()
                      << " | Status: " << booking->getStatus() << '\n';
        }
    }
};
