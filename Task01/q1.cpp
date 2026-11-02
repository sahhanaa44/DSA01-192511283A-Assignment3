#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Book {
    string title;
    string author;
    int copies;

public:
    Book() : Book("Untitled", "Unknown", 0) {}
    explicit Book(const string& t) : Book(t, "Unknown", 0) {}
    Book(const string& t, int c) : Book(t, "Unknown", c) {}

    Book(const string& t, const string& a, int c)
        : title(t), author(a), copies(c) {
        if (c < 0) {
            throw invalid_argument("Copies cannot be negative");
        }
    }

    void display() const {
        cout << "Title: " << title << ", Author: " << author
             << ", Copies: " << copies << '\n';
    }
};

int main() {
    try {
        Book empty;
        Book donated("The Alchemist");
        Book limited("Atomic Habits", 3);
        Book full("Clean Code", "Robert C. Martin", 5);

        empty.display();
        donated.display();
        limited.display();
        full.display();

        try {
            Book invalid("Invalid Book", -2);
            invalid.display();
        } catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << '\n';
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
