#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Event {
    string name;
    int rows;
    int seatsPerRow;
    bool** seats;
    int booked;

public:
    Event(const string& eventName, int r, int s)
        : name(eventName), rows(r), seatsPerRow(s), seats(nullptr), booked(0) {
        if (r < 0 || s < 0) throw invalid_argument("Rows and seats must be non-negative");
        if (rows > 0) {
            seats = new bool*[rows]{};
            try {
                for (int i = 0; i < rows; ++i) {
                    seats[i] = new bool[seatsPerRow]{};
                }
            } catch (...) {
                for (int i = 0; i < rows; ++i) delete[] seats[i];
                delete[] seats;
                throw;
            }
        }
        cout << "Created event: " << name << " (" << rows << " x "
             << seatsPerRow << ")\n";
    }

    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    bool book(int row, int seat) {
        if (row < 0 || row >= rows || seat < 0 || seat >= seatsPerRow) {
            cout << "Invalid seat\n";
            return false;
        }
        if (seats[row][seat]) {
            cout << "Seat already booked\n";
            return false;
        }
        seats[row][seat] = true;
        ++booked;
        cout << "Booked seat (" << row << ", " << seat << ")\n";
        return true;
    }

    bool cancel(int row, int seat) {
        if (row < 0 || row >= rows || seat < 0 || seat >= seatsPerRow ||
            !seats[row][seat]) {
            cout << "Cannot cancel seat\n";
            return false;
        }
        seats[row][seat] = false;
        --booked;
        cout << "Cancelled seat (" << row << ", " << seat << ")\n";
        return true;
    }

    ~Event() {
        for (int i = 0; i < rows; ++i) delete[] seats[i];
        delete[] seats;
        cout << "Closing event: " << name << ", booked seats remaining: "
             << booked << '\n';
    }
};

int main() {
    Event local("College Fest", 2, 3);
    local.book(0, 1);
    local.book(1, 2);
    local.cancel(0, 1);

    {
        Event blockEvent("Workshop", 1, 2);
        blockEvent.book(0, 0);
    }

    Event* heapEvent = new Event("Concert", 2, 2);
    heapEvent->book(1, 1);
    delete heapEvent;

    Event zeroRows("Empty Event", 0, 5);
    return 0;
}
