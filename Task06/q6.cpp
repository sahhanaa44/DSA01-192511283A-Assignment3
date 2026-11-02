#include <cstring>
#include <iostream>
#include <stdexcept>
using namespace std;

class Text {
    char* data;

public:
    explicit Text(const char* s = "") {
        if (s == nullptr) s = "";
        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }

    Text(const Text& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    Text& operator=(const Text& other) {
        if (this == &other) return *this;
        char* replacement = new char[strlen(other.data) + 1];
        strcpy(replacement, other.data);
        delete[] data;
        data = replacement;
        return *this;
    }

    ~Text() { delete[] data; }

    Text operator+(const Text& other) const {
        size_t n1 = strlen(data), n2 = strlen(other.data);
        char* joined = new char[n1 + n2 + 1];
        strcpy(joined, data);
        strcat(joined, other.data);
        Text result(joined);
        delete[] joined;
        return result;
    }

    bool operator==(const Text& other) const {
        return strcmp(data, other.data) == 0;
    }

    bool operator!=(const Text& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const Text& t) {
        return os << t.data;
    }
};

int main() {
    Text first("Hello, ");
    Text second("world!");
    Text message = first + second;
    cout << message << '\n';

    Text copy = message;
    copy = copy; // self-assignment test
    cout << "Copy: " << copy << '\n';
    cout << boolalpha << "Equal: " << (copy == message) << '\n';

    Text empty;
    cout << "Empty text: [" << empty << "]\n";
    cout << "Not equal: " << (empty != message) << '\n';
    return 0;
}
