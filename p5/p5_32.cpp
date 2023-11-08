#include <iostream>
#include <bitset>
#include<cmath>

#include"copyright.h"

using namespace std;

class Gate {
public:
    virtual bool Evaluate() = 0;
};

class Input : public Gate {
protected:
    bool value;
public:
    Input() : value(0) {}
    void SetValue(bool v) { value = v; }
    bool Evaluate() { return value; }
};

class Output : public Gate {
protected:
    Gate* input;
public:
    Output(Gate* g) : input(g) {}
};

class And : public Gate {
private:
    Gate* in1;
    Gate* in2;
public:
    And(Gate* i1, Gate* i2) : in1(i1), in2(i2) {}
    bool Evaluate() { return in1->Evaluate() && in2->Evaluate(); }
};

class Or : public Gate {
private:
    Gate* in1;
    Gate* in2;
public:
    Or(Gate* i1, Gate* i2) : in1(i1), in2(i2) {}
    bool Evaluate() { return in1->Evaluate() || in2->Evaluate(); }
};

class Xor : public Gate {
private:
    Gate* in1;
    Gate* in2;
public:
    Xor(Gate* i1, Gate* i2) : in1(i1), in2(i2) {}
    bool Evaluate() { return in1->Evaluate() != in2->Evaluate(); }
};

class Sum : public Output {
public:
    Sum(Gate* a, Gate* b, Gate* c) : Output(new Xor(new Xor(a, b), c)) {}
    bool Evaluate() { return input->Evaluate(); }
};

class Carry : public Output {
public:
    Carry(Gate* a, Gate* b, Gate* c) : Output(new Or(new Or(new And(a, b), new And(b, c)), new And(a, c))) {}
    bool Evaluate() { return input->Evaluate(); }
};

int main() {
    Input* A[8];
    Input* B[8];
    Input* Cin = new Input();

    int a, b;
    cout << "Please input the first number: ";
    cin >> a;
    cout << "Please input the second number: ";
    cin >> b;

    // Convert the numbers to binary and store them in the input arrays
    bitset<8> binary_a(a);
    bitset<8> binary_b(b);
    for (int i = 0; i < 8; i++) {
        A[i] = new Input();
        B[i] = new Input();
        A[i]->SetValue(binary_a[7-i]);
        B[i]->SetValue(binary_b[7-i]);
    }

    Sum* S[8];
    Carry* C[8];

    // Create the single bit adders for each bit position
    for (int i = 0; i < 8; i++) {
        if (i == 0) {
            C[i] = new Carry(A[i], B[i], Cin);
        }
        else {
            C[i] = new Carry(A[i], B[i], C[i-1]);
        }
        S[i] = new Sum(A[i], B[i], C[i]);
    }

    // Output binary and decimal values for A and B
    cutline();
    cout << "A: ";
    for (int i = 7; i >= 0; i--) {
        cout << A[i]->Evaluate();
    }
    cout << " (" << a << ")" << endl;

    cout << "B: ";
    for (int i = 7; i >= 0; i--) {
        cout << B[i]->Evaluate();
    }
    cout << " (" << b << ")" << endl;
    cutline();

    // Output carry and sum values in binary and decimal
    cout << "Carry: ";
    cout << (Cin->Evaluate() ? 1 : 0) << endl;

    cout << "Sum: ";
    int sum = 0;
    for (int i = 7; i >= 0; i--) {
        cout << S[i]->Evaluate();
        if (S[i]->Evaluate()) {
            sum += pow(2, 7-i);
        }
    }
    cout << " (" << sum << ")" << endl;

    // Output value of cin
    cout << "Cin: " << Cin->Evaluate() << endl;

    copyright();

    // Delete allocated memory
    for (int i = 0; i < 8; i++) {
        delete A[i];
        delete B[i];
        delete S[i];
        delete C[i];
    }
    delete Cin;

    system("pause");

    return 0;
}