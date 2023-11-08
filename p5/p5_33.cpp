//适度编程益脑，过度编程伤身
//合理安排时间，享受健康生活
//copyright: @A_E 
//email: yz50u22@soton.ac.uk
//面向对象设计一个8比特逻辑电路计算加减乘除

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

class Subtract : public Gate {
private:
    Gate* in1;
    Gate* in2;
public:
    Subtract(Gate* i1, Gate* i2) : in1(i1), in2(i2) {}
    bool Evaluate() { return in1->Evaluate() && !in2->Evaluate(); }
};

class Multiply : public Gate {
private:
    Gate* in1;
    Gate* in2;
public:
    Multiply(Gate* i1, Gate* i2) : in1(i1), in2(i2) {}
    bool Evaluate() { return in1->Evaluate() && in2->Evaluate(); }
};

class Add : public Gate {
private:
    Gate* in1;
    Gate* in2;
public:
    Add(Gate* i1, Gate* i2) : in1(i1), in2(i2) {}
    bool Evaluate() { return in1->Evaluate() || in2->Evaluate(); }
};

class Subtraction : public Output {
public:
    Subtraction(Gate* a, Gate* b) : Output(new Subtract(a, b)) {}
    bool Evaluate() { return input->Evaluate(); }
};

class Multiplication : public Output {
public:
    Multiplication(Gate* a, Gate* b) : Output(new Multiply(a, b)) {}
    bool Evaluate() { return input->Evaluate(); }
};

int main() {
    Input* A[8];
    Input* B[8];
    Input* Cin = new Input();

    int a, b, c;
    cout << "Please input the first number: ";
    cin >> a;
    cout << "Please input the second number: ";
    cin >> b;
    cout << "Please input the Cin value (0 or 1): ";
    cin >> c;

    // Convert the numbers to binary and store them in the input arrays
    bitset<8> binary_a(a);
    bitset<8> binary_b(b);
    for (int i = 0; i < 8; i++) {
        A[i] = new Input();
        B[i] = new Input();
        A[i]->SetValue(binary_a[7-i]);
        B[i]->SetValue(binary_b[7-i]);
    }
    Cin->SetValue(c);

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

    cout << "Cin: " << Cin->Evaluate() << endl;

    cutline();

    //Add
    cout << "Sum: ";
    for (int i = 7; i >= 0; i--) {
        cout << S[i]->Evaluate();
    }
    cout << " (" << a + b + Cin->Evaluate() << ")" << endl;

    //Substraction
    cout << "Substraction: ";
    for (int i = 7; i >= 0; i--){
        cout << S[i]->Evaluate();
    }
    cout << "(" << a - b + Cin->Evaluate() << ")" << endl;

    //Production
    cout << "Product: ";
    bitset<16> product(a * b);
    for (int i = 15; i >= 0; i--) {
        cout << product[i];
    }
    cout << " (" << a * b << ")" << endl;

    //Multiplication
    bitset<8> quotient(a / b);
    cout << "A / B: ";
    for (int i = 7; i >= 0; i--) {
        cout << quotient[7-i];
    }
    cout << " (" << a / b << ")" << endl;

    //Check "Carry"
    cout << "Carry: ";
    cout << (Cin->Evaluate() ? 0 : 1) << endl;

    //Copyright information
    copyright();

    system("pause");

    //Free the memory
    for (int i = 0; i < 8; i++) {
        delete A[i];
        delete B[i];
        delete S[i];
        delete C[i];
    }
    delete Cin;

    return 0;
}