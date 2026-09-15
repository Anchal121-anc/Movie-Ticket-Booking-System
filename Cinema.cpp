// OOP: Composition - Cinema owns its Screen objects.
class Cinema {
private:
    std::string name;
    std::vector<Screen> screens;

public:
    explicit Cinema(const std::string& name) : name(name) {}

    void addScreen(int screenNumber) {
        screens.emplace_back(screenNumber);
    }

    const std::string& getName() const { return name; }
    const std::vector<Screen>& getScreens() const { return screens; }

    const Screen* findScreen(int screenNumber) const {
        for (const Screen& screen : screens) {
            if (screen.getScreenNumber() == screenNumber) return &screen;
        }
        return nullptr;
    }
};
