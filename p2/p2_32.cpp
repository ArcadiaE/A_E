#include <iostream>
#include <bitset>

using namespace std;

int main() {
    
    int A, B;
    cout << "Enter the value of A (decimal): ";
    cin >> A;
    cout << "Enter the value of B (decimal): ";
    cin >> B;

    int C;
    cout << "Enter the value of Cin (demical): ";
    cin >> C;

    bitset<8> a(A);
    bitset<8> b(B);
    bitset<8> Cin(C);
    bitset<8> sum;
    bitset<8> carry;

    for (int i = 0; i < 8; i++) {
        sum[i] = (a[i] ^ b[i]) ^ Cin[i];
        carry[i] = (a[i] & b[i]) | (b[i] & Cin[i]) | (Cin[i] & a[i]);
        Cin[i + 1] = carry[i];
    }

    cout << "A in binary is: " << a << endl;
    cout << "B in binary is: " << b << endl;
    cout << "Sum in binary: " << sum << endl;
    cout << "Sum in decimal: " << sum.to_ulong() << endl;
    cout << "Carry Out: " << carry.to_ulong() << endl;

    int Overflow = ((B & A & ~sum[8]) | (~A & ~B & sum[8])) & 1;
    cout << "Overflow: " << Overflow << endl;
    
    system("pause");

    return 0;
}