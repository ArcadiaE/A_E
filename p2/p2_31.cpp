#include <iostream>

using namespace std;

int main() {
    int A = 0, B = 0, Cin = 0;

    cout << "please input A: " << endl;
    cin >> A;
    cout << "please input B: " << endl;
    cin >> B;
    cout << "please input Cin: " << endl;
    cin >> Cin;

    int Sum = (A ^ B ^ Cin);
    int Carry = (A & B) | (B & Cin) | (A & Cin);

    cout << "Sum: " << Sum << endl;
    cout << "Carry: " << Carry << endl;

    system("pause");

    return 0;
}