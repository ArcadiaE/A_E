#include<iostream>
#include<cmath>

#include"copyright.h"

using namespace std;


class Complex {
  public:
    Complex() : real(0), imag(0) {}
    Complex(double r) : real(r), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    double real;
    double imag;

    Complex operator+(const Complex &c) const {
        return Complex(real + c.real, imag + c.imag);
    }

    Complex operator-(const Complex &c) const {
        return Complex(real - c.real, imag - c.imag);
    }

    Complex operator*(const Complex &c) const {
        return Complex(real * c.real - imag * c.imag, 
                       real * c.imag + imag * c.real);
    }

    Complex operator/(const Complex &c) const {
        double denominator = c.real * c.real + c.imag * c.imag;
        return Complex((real * c.real + imag * c.imag) / denominator,
                       (imag * c.real - real * c.imag) / denominator);
    }

    friend std::ostream& operator<<(std::ostream &out, const Complex &c) {
        out << c.real << " + " << c.imag << "i";
        return out;
    }
};

Complex operator+(double d, const Complex &c) {
    return Complex(d + c.real, c.imag);
}

Complex operator-(double d, const Complex &c) {
    return Complex(d - c.real, -c.imag);
}

Complex operator*(double d, const Complex &c) {
    return Complex(d * c.real, d * c.imag);
}

Complex operator/(double d, const Complex &c) {
    double denominator = c.real * c.real + c.imag * c.imag;
    return Complex(d * c.real / denominator, 
                   -d * c.imag / denominator);
}

int main() {
    const double pi = 3.14159265358979;
    double resistance = 50.0;
    double inductance = 0.1;
    double capacitance = 0.000001;
    double frequency = 1000.0;

    Complex impedance(resistance, 2 * pi * frequency * inductance);
    impedance = impedance + Complex(0, -1.0 / (2 * pi * frequency * capacitance));

    std::cout << "The complex impedance is: " << impedance << std::endl;

    copyright();

    system("pause");

    return 0;
}