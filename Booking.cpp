// OOP: Encapsulation - booking state and amount are private.
// OOP: Static member - nextBookingId generates unique booking IDs.
class Booking {
private:
    inline static int nextBookingId = 1001;
    int bookingId;
    Customer customer;
    Show* show;
    std::vector<int> seatNumbers;
    double totalAmount;
    std::string status;

public:
    Booking(const Customer& customer, Show* show,
            const std::vector<int>& seatNumbers, double totalAmount)
        : bookingId(nextBookingId++), customer(customer), show(show),
          seatNumbers(seatNumbers), totalAmount(totalAmount), status("PENDING") {}

    int getBookingId() const { return bookingId; }
    const Customer& getCustomer() const { return customer; }
    Show& getShow() const { return *show; }
    const std::vector<int>& getSeatNumbers() const { return seatNumbers; }
    double getTotalAmount() const { return totalAmount; }
    const std::string& getStatus() const { return status; }

    void confirm() { status = "CONFIRMED"; }
    void cancel() { status = "CANCELLED"; }
};
