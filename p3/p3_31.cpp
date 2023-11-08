#include<iostream>

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

    Complex c1(3, 4);
    Complex c2(2);
    Complex c3 = c1 + c2;
    Complex c4 = c1 - c2;
    Complex c5 = c1 * c2;
    Complex c6 = c1 / c2;
    Complex c7 = 3 + c1;
    Complex c8 = 3 - c1;
    Complex c9 = 3 * c1;
    Complex c10 = 3 / c1;

    std::cout << c3 << std::endl;
    std::cout << c4 << std::endl;
    std::cout << c5 << std::endl;
    std::cout << c6 << std::endl;
    std::cout << c7 << std::endl;
    std::cout << c8 << std::endl;
    std::cout << c9 << std::endl;
    std::cout << c10 << std::endl;

    copyright();
    Ryo();

    system("pause");

    return 0;
}