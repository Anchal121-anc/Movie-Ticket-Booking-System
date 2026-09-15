// OOP: Encapsulation - customer identity is private.
class Customer {
private:
    std::string name;
    std::string phone;

public:
    Customer(const std::string& name, const std::string& phone)
        : name(name), phone(phone) {}

    const std::string& getName() const { return name; }
    const std::string& getPhone() const { return phone; }
};
