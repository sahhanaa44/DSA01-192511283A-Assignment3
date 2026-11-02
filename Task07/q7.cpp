#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;

class Complex {
    double realPart;
    double imaginaryPart;

public:
    Complex() : realPart(0), imaginaryPart(0) {}
    Complex(double r) : realPart(r), imaginaryPart(0) {}
    Complex(double r, double i) : realPart(r), imaginaryPart(i) {}

    double real() const { return realPart; }
    double imag() const { return imaginaryPart; }
    double magnitude() const { return sqrt(realPart * realPart + imaginaryPart * imaginaryPart); }

    Complex operator+(const Complex& z) const {
        return Complex(realPart + z.realPart, imaginaryPart + z.imaginaryPart);
    }

    Complex operator-(const Complex& z) const {
        return Complex(realPart - z.realPart, imaginaryPart - z.imaginaryPart);
    }

    Complex operator*(const Complex& z) const {
        return Complex(realPart * z.realPart - imaginaryPart * z.imaginaryPart,
                       realPart * z.imaginaryPart + imaginaryPart * z.realPart);
    }

    Complex operator/(const Complex& z) const {
        double denominator = z.realPart * z.realPart + z.imaginaryPart * z.imaginaryPart;
        if (denominator == 0.0) throw domain_error("Division by zero impedance");
        return Complex((realPart * z.realPart + imaginaryPart * z.imaginaryPart) / denominator,
                       (imaginaryPart * z.realPart - realPart * z.imaginaryPart) / denominator);
    }

    bool operator==(const Complex& z) const {
        return realPart == z.realPart && imaginaryPart == z.imaginaryPart;
    }

    friend ostream& operator<<(ostream& os, const Complex& z) {
        os << z.realPart;
        if (z.imaginaryPart >= 0) os << " + j" << z.imaginaryPart;
        else os << " - j" << -z.imaginaryPart;
        return os;
    }
};

int main() {
    try {
        const double omega = 100.0;
        const double inductance = 0.02;
        const double capacitance = 0.001;

        Complex resistor(10.0, 0.0);
        Complex inductor(0.0, omega * inductance);
        Complex capacitor(0.0, -1.0 / (omega * capacitance));

        Complex series = resistor + inductor + capacitor;
        cout << "Series impedance: " << series << '\n';
        cout << "Series magnitude: " << series.magnitude() << '\n';

        Complex z1(10.0, 5.0), z2(20.0, -3.0);
        Complex parallel = (z1 * z2) / (z1 + z2);
        cout << "Parallel impedance: " << parallel << '\n';
        cout << "Parallel magnitude: " << parallel.magnitude() << '\n';

        try {
            Complex invalid = z1 / Complex(0.0, 0.0);
            cout << invalid << '\n';
        } catch (const domain_error& e) {
            cout << "Error: " << e.what() << '\n';
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
