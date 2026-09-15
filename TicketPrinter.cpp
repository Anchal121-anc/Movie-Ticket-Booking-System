// OOP: Single Responsibility - this class only formats/prints tickets.
class TicketPrinter {
public:
    void print(const Booking& booking, const Payment& payment) const {
        const Show& show = booking.getShow();

        std::cout << "\n========================================\n";
        std::cout << "                 TICKET\n";
        std::cout << "========================================\n";
        std::cout << "Booking ID : " << booking.getBookingId() << '\n';
        std::cout << "Customer   : " << booking.getCustomer().getName() << '\n';
        std::cout << "Movie      : " << show.getMovie().getTitle() << '\n';
        std::cout << "Screen     : " << show.getScreen().getScreenNumber() << '\n';
        std::cout << "Start Time : " << show.getStartTime() << '\n';
        std::cout << "Seats      : ";
        for (std::size_t i = 0; i < booking.getSeatNumbers().size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << booking.getSeatNumbers()[i];
        }
        std::cout << "\nAmount     : Rs." << std::fixed << std::setprecision(2)
                  << booking.getTotalAmount() << '\n';
        std::cout << "Payment    : " << payment.methodName() << '\n';
        std::cout << "Status     : " << booking.getStatus() << '\n';
        std::cout << "========================================\n";
    }
};
