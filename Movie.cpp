// OOP: Encapsulation - movie data is private and exposed through getters.
class Movie {
private:
    std::string title;
    std::string language;
    int durationMinutes;

public:
    Movie(const std::string& title, const std::string& language, int durationMinutes)
        : title(title), language(language), durationMinutes(durationMinutes) {}

    Movie(const std::string& title, int durationMinutes)
        : Movie(title, "Hindi", durationMinutes) {} // Compile-time polymorphism: overloaded constructor.

    const std::string& getTitle() const { return title; }
    const std::string& getLanguage() const { return language; }
    int getDurationMinutes() const { return durationMinutes; }
};
