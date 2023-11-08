#include <iostream>
#include <cmath>

#include"copyright.h"

class Angle {
public:
    Angle(double degrees = 0) : degrees_(degrees) {}

    double degrees() const { return degrees_; }

    double radians() const { return degrees_ * M_PI / 180; }

    void set_degrees(double degrees) { degrees_ = degrees; }

    void set_radians(double radians) { degrees_ = radians * 180 / M_PI; }

private:
    double degrees_;
};

class Complex {
public:
    Complex(double real = 0, double imag = 0) : real_(real), imag_(imag) {}

    Complex(double mag, const Angle& angle) {
        real_ = mag * std::cos(angle.radians());
        imag_ = mag * std::sin(angle.radians());
        }

    double real() const { return real_; }
    double imag() const { return imag_; }

    double magnitude() const { return std::hypot(real_, imag_); }
    Angle angle() const { return Angle(std::atan2(imag_, real_) * 180 / M_PI); }

    Complex operator+(const Complex& rhs) const {
        return Complex(real_ + rhs.real_, imag_ + rhs.imag_);
    }

    Complex operator-(const Complex& rhs) const {
        return Complex(real_ - rhs.real_, imag_ - rhs.imag_);
    }

    Complex operator*(const Complex& rhs) const {
        return Complex(real_ * rhs.real_ - imag_ * rhs.imag_,
                   real_ * rhs.imag_ + imag_ * rhs.real_);
    }

    Complex operator/(const Complex& rhs) const {
        double denominator = rhs.real_ * rhs.real_ + rhs.imag_ * rhs.imag_;
        return Complex((real_ * rhs.real_ + imag_ * rhs.imag_) / denominator,
                   (imag_ * rhs.real_ - real_ * rhs.imag_) / denominator);
    }

    Complex operator-() const { return Complex(-real_, -imag_); }

    friend std::ostream& operator<<(std::ostream& out, const Complex& c) {
            out << c.real_ << " + " << c.imag_ << "i";
            return out;
    }

private:
    double real_;
    double imag_;
};

Complex operator+(double d, const Complex &c) {
    return Complex(d + c.real(), c.imag());
}

Complex operator-(double d, const Complex &c) {
    return Complex(d - c.real(), -c.imag());
}

Complex operator*(double d, const Complex &c) {
    return Complex(d * c.real(), d * c.imag());
}

Complex operator/(double d, const Complex &c) {
    double denominator = c.real() * c.real() + c.imag() * c.imag();
    return Complex(d * c.real() / denominator, 
                   -d * c.imag() / denominator);
}

int main() {
    Complex c1(3, 4); // Cartesian form
    std::cout << "c1 = " << c1 << std::endl;

    Complex c2(5, Angle(53.13)); // Phasor form
    std::cout << "c2 = " << c2 << std::endl;

  // Conversion between Cartesian and polar form
    std::cout << "c1 magnitude: " << c1.magnitude() << std::endl;
    std::cout << "c1 angle: " << c1.angle().degrees() << " degrees" << std::endl;

    std::cout << "Phasor form: " << c1.magnitude() << "∠" << c1.angle().degrees() << std::endl;

    Complex c3(10, Angle(30)); // Phasor form
    std::cout << "c3 = " << c3 << std::endl;

    Complex c4 = c2 * c3; // Multiplication in phasor form
    std::cout << "c4 = " << c4 << std::endl;

    Complex c5(c4.magnitude(), Angle(60)); // Phasor form
    std::cout << "c5 = " << c5 << std::endl;

    Complex c6 = c5 / c3; // Division in phasor form
    std::cout << "c6 = " << c6 << std::endl;

    copyright();

    //Ryo();

    system("pause");

}

