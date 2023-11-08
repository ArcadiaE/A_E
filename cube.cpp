/*
立方体类，求面积体积，比较大小
*/

#include<iostream>
#include<string>
#include<ctime>

#include"copyright.h"

using namespace std;

class cube{
private:
    int Length;
    int Width;
    int Height;

public:
//获取长宽高，接入私有变量
    void setLength(int l){
        Length = l;
    }

    int getLength(){
        return Length;
    }

    void setWidth(int w){
        Width = w;
    }

    int getWidth(){
        return Width;
    }

    void setHeight(int h){
        Height = h;
    }

    int getHeight(){
        return Height;
    }

//计算长方体面积、体积
    int calculate_s(){
        return 2 * Length * Width+ 2 * Width * Height + 2 * Length * Height;
    }

    int calculate_v(){
        return Length * Width * Height;
    }
};

//全局函数，判断大小
bool is_same(cube &c1, cube &c2){
    if(c1.getLength() == c2.getLength()  && c1.getWidth() == c2.getWidth() && c1.getHeight() == c2.getHeight()){
        return true;
    }
    else{
        return false;
    }
};

int main(){
    int A, B, C;

    cout << "Please input the length of cube 1: " << endl;
    cin >> A;
    cout << "Please input the width of cube 1: " << endl;
    cin >> B;
    cout << "Please input the Height of cube 1: " << endl;
    cin >> C;
    cutline();

//创建立方体
    cube c1;

    c1.setLength(A);
    c1.setWidth(B);
    c1.setHeight(C);
   
//检验
/*
    cutline();
    
    cout << "The volume of Cube is: " << c1.calculate_s() << endl;
    cout << "The superficial area of Cube is: " << c1.calculate_v() << endl;
*/
//创建第二个立方体
    cube c2;
    int X, Y, Z;

    cout << "Please input the length of cube 2: " << endl;
    cin >> X;
    cout << "Please input the width of cube 2: " << endl;
    cin >> Y;
    cout << "Please input the Height of cube 2: " << endl;
    cin >> Z;
    cutline();

    c2.setLength(X);
    c2.setWidth(Y);
    c2.setHeight(Z);

    bool check = :: is_same (c1, c2);

    if(check){
        cout << "Two cubes are same." << endl;
    }
    else{
        cout << "Two cubes are different." << endl;
    }

    copyright();
    Ryo();

    system("pause");

    return 0;
}