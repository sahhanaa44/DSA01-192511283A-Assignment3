#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Prescription {
    int n;
    string* medicines;

public:
    explicit Prescription(int count)
        : n(count), medicines(count > 0 ? new string[count] : nullptr) {
        if (count < 0) throw invalid_argument("Medicine count cannot be negative");
    }

    // Deep-copy constructor
    Prescription(const Prescription& other)
        : n(other.n), medicines(n > 0 ? new string[n] : nullptr) {
        for (int i = 0; i < n; ++i) medicines[i] = other.medicines[i];
    }

    // Deep-copy assignment operator
    Prescription& operator=(const Prescription& other) {
        if (this == &other) return *this;

        string* newMedicines = other.n > 0 ? new string[other.n] : nullptr;
        for (int i = 0; i < other.n; ++i) newMedicines[i] = other.medicines[i];

        delete[] medicines;
        medicines = newMedicines;
        n = other.n;
        return *this;
    }

    ~Prescription() {
        delete[] medicines;
    }

    void set(int i, const string& m) {
        if (i < 0 || i >= n) throw out_of_range("Medicine index out of range");
        medicines[i] = m;
    }

    string get(int i) const {
        if (i < 0 || i >= n) throw out_of_range("Medicine index out of range");
        return medicines[i];
    }
};

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p;
    p.set(0, "Ibuprofen");
    p = p; // self-assignment test

    cout << p.get(0) << ' ' << p.get(1) << " | "
         << q.get(0) << ' ' << q.get(1) << " | "
         << r.get(0) << ' ' << r.get(1) << '\n';
    return 0;
}
