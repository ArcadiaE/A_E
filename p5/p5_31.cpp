#include <iostream>

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
    bool Evaluate() { return value; } // default implementation for Evaluate()
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
    Input* A = new Input();
    Input* B = new Input();
    Input* Cin = new Input();

    cout << "please input A: " << endl;
    bool a;
    cin >> a;
    A->SetValue(a);
    cout << "please input B: " << endl;
    bool b;
    cin >> b;
    B->SetValue(b);
    cout << "please input Cin: " << endl;
    bool c;
    cin >> c;
    Cin->SetValue(c);

    cutline();

    Sum* s = new Sum(A, B, Cin);
    Carry* c_out = new Carry(A, B, Cin);

    cout << "Sum: " << s->Evaluate() << endl;
    cout << "Carry: " << c_out->Evaluate() << endl;

    copyright();

    delete A;
    delete B;
    delete Cin;
    delete s;
    delete c_out;

    system("pause");
    return 0;
}