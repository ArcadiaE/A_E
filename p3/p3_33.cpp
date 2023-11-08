//适度编程益脑，过度编程伤身
//合理安排时间，享受健康生活
//copyright: @A_E 
//email: yz50u22@soton.ac.uk

#include<iostream>
#include<cmath>

#include"copyright.h"

using namespace std;

//复数类
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
        out << c.real_ << " + " << c.imag_ << "j";
        return out;
    }

private:
    double real_;
    double imag_;
};

class SeriesRLC {
public:
    SeriesRLC(double resistance, double inductance, double capacitance, double frequency)
        : resistance_(resistance), inductance_(inductance), capacitance_(capacitance), frequency_(frequency) {}

    double getResistance() const { return resistance_; }
    double getInductance() const { return inductance_; }
    double getCapacitance() const { return capacitance_; }
    double getFrequency() const { return frequency_; }

    Complex getImpedance() const {
        const double pi = 3.14159265358979;
        Complex impedance(resistance_, 2 * pi * frequency_ * inductance_);
        impedance = impedance + Complex(0, -1.0 / (2 * pi * frequency_ * capacitance_));
        return impedance;
    }

private:
    double resistance_;
    double inductance_;
    double capacitance_;
    double frequency_;
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

int main()
{
    double resistance, inductance, capacitance, frequency, amplitude;
    double phase;
    
    std::cout << "Enter the resistance: ";
    std::cin >> resistance;

    std::cout << "Enter the inductance: ";
    std::cin >> inductance;

    std::cout << "Enter the capacitance: ";
    std::cin >> capacitance;

    std::cout << "Enter the frequency of the voltage source: ";
    std::cin >> frequency;

    std::cout << "Enter the amplitude of the voltage source: ";
    std::cin >> amplitude;

    std::cout << "Enter the phase of the voltage source in degrees: ";
    std::cin >> phase;

    SeriesRLC circuit(resistance, inductance, capacitance, frequency);
    Complex impedence;
    Complex impedance = circuit.getImpedance();
    double voltage_magnitude = amplitude;
    double voltage_phase = phase * M_PI / 180.0;
    double current_real = (voltage_magnitude * cos(voltage_phase)) / impedance.real();
    double current_imag = (voltage_magnitude * sin(voltage_phase)) / impedance.imag();

   cutline();

    std::cout << "The complex impedance is: " << impedance << std::endl;
    std::cout << "The voltage source has an amplitude of " << amplitude << "V and a frequency of "
                << frequency << "Hz." << std::endl;
    std::cout << "The complex current is: " << current_real << " + " << current_imag << "i" << std::endl;
    std::cout << "The phase difference between the voltage source and the current is " 
                << atan2(current_imag, current_real) * 180.0 / M_PI << " degrees." << std::endl;

    copyright();

    //Yamada_Ryo();
    //Ryo();

    system("pause");

    return 0;
}

