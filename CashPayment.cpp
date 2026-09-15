// OOP: Inheritance - CashPayment is a Payment.
class CashPayment : public Payment {
private:
    bool accepted;

public:
    explicit CashPayment(bool accepted) : accepted(accepted) {}

    bool pay(double amount) override {
        std::cout << "Processing Cash payment of Rs." << std::fixed << std::setprecision(2)
                  << amount << "...\n";
        if (!accepted) {
            std::cout << "Cash payment failed/not accepted.\n";
            return false;
        }
        std::cout << "Cash payment accepted.\n";
        return true;
    }

    std::string methodName() const override { return "CASH"; }
};
