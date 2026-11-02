#include <iomanip>
#include <iostream>
using namespace std;

class Money {
    long long paise;

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    Money operator+(const Money& other) const {
        return Money(0, static_cast<int>(paise + other.paise));
    }

    Money operator-(const Money& other) const {
        return Money(0, static_cast<int>(paise - other.paise));
    }

    Money& operator+=(const Money& other) {
        paise += other.paise;
        return *this;
    }

    bool operator==(const Money& other) const {
        return paise == other.paise;
    }

    bool operator<(const Money& other) const {
        return paise < other.paise;
    }

    friend ostream& operator<<(ostream& os, const Money& m) {
        long long absolutePaise = m.paise < 0 ? -m.paise : m.paise;
        if (m.paise < 0) os << "-";
        os << "Rs " << absolutePaise / 100 << '.'
           << setw(2) << setfill('0') << absolutePaise % 100
           << setfill(' ');
        return os;
    }

    friend istream& operator>>(istream& is, Money& m) {
        long long rupees;
        int p;
        if (is >> rupees >> p) m.paise = rupees * 100 + p;
        return is;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    cout << c << '\n' << boolalpha << (c == Money(200)) << '\n';

    Money x(0, 75), y(0, 50);
    cout << x + y << '\n';

    Money d(1, 0), e(2, 0);
    cout << d - e << '\n';
    return 0;
}
