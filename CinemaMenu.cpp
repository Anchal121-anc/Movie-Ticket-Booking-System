// OOP: Single Responsibility - console menu and input handling only.
class CinemaMenu {
private:
    Cinema& cinema;
    std::vector<Movie>& movies;
    std::vector<Show>& shows;
    BookingService& bookingService;

    int readInt(const std::string& prompt, int minimum, int maximum) const {
        while (true) {
            std::cout << prompt;
            int value;
            if (std::cin >> value && value >= minimum && value <= maximum) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
            std::cout << "Invalid input. Please enter a number from "
                      << minimum << " to " << maximum << ".\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::string readText(const std::string& prompt) const {
        std::cout << prompt;
        std::string value;
        std::getline(std::cin, value);
        while (value.empty()) {
            std::cout << "Input cannot be empty. " << prompt;
            std::getline(std::cin, value);
        }
        return value;
    }

    void listMovies() const {
        std::cout << "\nCurrently Playing\n";
        for (const Movie& movie : movies) {
            std::cout << movie.getTitle() << " | "
                      << movie.getLanguage() << " | "
                      << movie.getDurationMinutes() << " min\n";
        }
    }

    std::vector<Show*> showsForMovie(int movieIndex) {
        std::vector<Show*> result;
        for (Show& show : shows) {
            if (&show.getMovie() == &movies[movieIndex]) result.push_back(&show);
        }
        return result;
    }

    Show* chooseShow() {
        listMovies();
        const int movieChoice = readInt("Choose movie (1-" + std::to_string(movies.size()) + "): ",
                                        1, static_cast<int>(movies.size()));
        const int movieIndex = movieChoice - 1;
        std::vector<Show*> movieShows = showsForMovie(movieIndex);

        std::cout << "\nShows for " << movies[movieIndex].getTitle() << '\n';
        for (std::size_t i = 0; i < movieShows.size(); ++i) {
            std::cout << i + 1 << ". Screen " << movieShows[i]->getScreen().getScreenNumber()
                      << " | " << movieShows[i]->getStartTime() << '\n';
        }

        const int showChoice = readInt("Choose show: ", 1, static_cast<int>(movieShows.size()));
        return movieShows[showChoice - 1];
    }

    void displaySeats() {
        Show* show = chooseShow();
        show->displaySeats();
    }

    void bookTicket() {
        Show* show = chooseShow();
        show->displaySeats();

        const std::string name = readText("Customer name: ");
        const std::string phone = readText("Phone number: ");
        Customer customer(name, phone);

        const int seatCount = readInt("How many seats? ", 1, 20);
        std::vector<int> seatNumbers;
        for (int index = 0; index < seatCount; ++index) {
            seatNumbers.push_back(readInt(
                "Enter seat number " + std::to_string(index + 1) + " (1-20): ", 1, 20));
        }

        std::cout << "\nPayment Method\n1. UPI\n2. Card\n3. Cash\n";
        const int paymentChoice = readInt("Choose payment method: ", 1, 3);

        std::unique_ptr<Payment> payment;
        if (paymentChoice == 1) {
            const std::string upiId = readText("Enter UPI ID (type FAIL to simulate failure): ");
            payment = std::make_unique<UpiPayment>(upiId);
        } else if (paymentChoice == 2) {
            const std::string cardNumber = readText("Enter card number (type FAIL to simulate failure): ");
            payment = std::make_unique<CardPayment>(cardNumber);
        } else {
            const int accepted = readInt("Cash accepted? (1=Yes, 2=No): ", 1, 2);
            payment = std::make_unique<CashPayment>(accepted == 1);
        }

        bookingService.bookTicket(customer, *show, seatNumbers, *payment);
    }

    void cancelBooking() {
        const int bookingId = readInt("Enter booking ID to cancel (1001+): ", 1001, 999999);
        bookingService.cancelBooking(bookingId);
    }

public:
    CinemaMenu(Cinema& cinema, std::vector<Movie>& movies,
               std::vector<Show>& shows, BookingService& bookingService)
        : cinema(cinema), movies(movies), shows(shows), bookingService(bookingService) {}

    void run() {
        while (true) {
            std::cout << "\n===== " << cinema.getName() << " MOVIE TICKET BOOKING =====\n";
            std::cout << "1. List movies\n"
                      << "2. List shows\n"
                      << "3. Display seat layout\n"
                      << "4. Book ticket\n"
                      << "5. Cancel booking\n"
                      << "6. Show booking records\n"
                      << "7. Exit\n";

            const int choice = readInt("Enter choice: ", 1, 7);

            try {
                switch (choice) {
                    case 1: listMovies(); break;
                    case 2: chooseShow(); break;
                    case 3: displaySeats(); break;
                    case 4: bookTicket(); break;
                    case 5: cancelBooking(); break;
                    case 6: bookingService.printAllBookings(); break;
                    case 7:
                        std::cout << "Thank you for using the system.\n";
                        return;
                }
            } catch (const std::exception& exception) {
                std::cout << "Operation failed safely: " << exception.what() << '\n';
            }
        }
    }
};
