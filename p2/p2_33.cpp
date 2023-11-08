//适度编程益脑，过度编程伤身
//合理安排时间，享受健康生活
//copyright: @A_E 

#include <iostream>
#include <bitset>
#include <cmath>

#include "copyright.h"

using namespace std;

// 补码
int getTwoComplement(bitset<8> binNum) {
    binNum.flip();
    int carry = 1;
    for (int i = 0; i < 8; i++) {
        if (binNum[i] == 0 && carry == 1) {
            binNum.set(i, 1);
            carry = 0;
        } else if (binNum[i] == 1 && carry == 1) {
            binNum.set(i, 0);
            carry = 1;
        }
    }
    return (int)binNum.to_ulong();
}

int main() {
int A, B;
cout << "Input your first number (A): ";
cin >> A;
cout << "Input your second number (B): ";
cin >> B;
char op;
cout << "Select operation (+ or -): ";
cin >> op;

//从A的正负判断是否进行补码运算
bitset<8> a;
if (A >= 0) {
    a = bitset<8>(A);
} else {
    a = getTwoComplement(bitset<8>(abs(A)));
    cout << "A is a negative number, need to convert from 2's complement to decimal." << endl;
    cout << a << endl;
    cout << "The decimal equivalent is " << -1 * (pow(2, 8) - a.to_ulong()) << endl;
}

//从B的正负判断是否进行补码运算
bitset<8> b;
if (B >= 0) {
    b = bitset<8>(B);
} else {
    b = getTwoComplement(bitset<8>(abs(B)));
    cout << "B is a negative number, need to convert from 2's complement to decimal." << endl;
    cout << b << endl;
    cout << "The decimal equivalent is " << -1 * (pow(2, 8) - b.to_ulong()) << endl;
}

//低位进位
int C;
if (op == '-') {
    C = 1;
    b = getTwoComplement(b);
} else {
    C = 0;
}

bitset<8> Cin(C);
bitset<8> sum;
bitset<8> carry;

//8—bit full adder 前一个的输出是后一个的输入
for (int i = 0; i < 8; i++) {
    sum[i] = (a[i] ^ b[i]) ^ Cin[i];
    carry[i] = (a[i] & b[i]) | (b[i] & Cin[i]) | (Cin[i] & a[i]);
    Cin[i + 1] = carry[i];
}

int Carry = carry[7];

cout << "Corresponding value A in binary: " << a << endl;
cout << "Corresponding value B in binary: " << b << endl;
cout << "C_In Value is: " << C << endl;
cout << "Sum in binary: " << sum << endl;
cout << "Sum in decimal: " << sum.to_ulong() << endl;
cout << "Carry = " << Carry << endl;

//溢出检测
int Overflow = ((B & A & ~sum[7]) | (~A & ~B & sum[7])) & 1;
cout <<"Overflow = "<<Overflow << endl;

//没错我加入了版权
copyright();

system("pause");

return 0;
}
