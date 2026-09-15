// OOP: Abstraction - Payment defines the common contract.
// OOP: Polymorphism - pay() is resolved at runtime through Payment*.
class Payment {
public:
    virtual bool pay(double amount) = 0;
    virtual std::string methodName() const = 0;
    virtual ~Payment() = default;
};
