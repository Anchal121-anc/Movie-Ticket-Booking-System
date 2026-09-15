// OOP: Inheritance - CardPayment is a Payment.
class CardPayment : public Payment {
private:
    std::string cardNumber;

public:
    explicit CardPayment(const std::string& cardNumber) : cardNumber(cardNumber) {}

    bool pay(double amount) override {
        std::cout << "Processing Card payment of Rs." << std::fixed << std::setprecision(2)
                  << amount << "...\n";
        if (cardNumber == "FAIL") {
            std::cout << "Card payment failed.\n";
            return false;
        }
        std::cout << "Card payment successful.\n";
        return true;
    }

    std::string methodName() const override { return "CARD"; }
};
