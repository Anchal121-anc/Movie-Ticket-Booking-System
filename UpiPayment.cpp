// OOP: Inheritance - UpiPayment is a Payment.
class UpiPayment : public Payment {
private:
    std::string upiId;

public:
    explicit UpiPayment(const std::string& upiId) : upiId(upiId) {}

    bool pay(double amount) override {
        std::cout << "Processing UPI payment of Rs." << std::fixed << std::setprecision(2)
                  << amount << "...\n";
        if (upiId == "FAIL") {
            std::cout << "UPI payment failed.\n";
            return false;
        }
        std::cout << "UPI payment successful.\n";
        return true;
    }

    std::string methodName() const override { return "UPI"; }
};
