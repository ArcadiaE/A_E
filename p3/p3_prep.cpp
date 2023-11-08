#include <iostream>

class Complex {
public:
    Complex(double real = 0, double imag = 0) : real_(real), imag_(imag) {}

    double real() const { return real_; }
    double imag() const { return imag_; }

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