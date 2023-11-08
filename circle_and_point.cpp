/*
设计一个圆类和一个点类，并找到他们间的关系
*/

#include<iostream>
#include<string>
#include<ctime>

#include"copyright.h"

using namespace std;

class Point{
private:
    int m_x, m_y;

public:
    void setX(int x){
        m_x = x;
    }
    int getX(){
        return m_x;
    }

    void setY(int y){
        m_y = y;
    }
    int getY(){
        return m_y;
    }
};


class Circle{
private:
    int Rad;
    Point Center;

public:
    void setR(int r){
        Rad = r;
    }
    int getR(){
        return Rad;
    }

    void setC(Point c){
        Center = c;
    }
    Point getC(){
        return Center;
    }
};

void judgeCir(Circle &c, Point &p){
    int distance =
        (c.getC().getX() - p.getX()) * (c.getC().getX() - p.getX()) + 
            (c.getC().getY() - p.getY()) * (c.getC().getY() - p.getY());

    int rdistance = c.getR() * c.getR();

    if (distance = rdistance){
        cout << "The point is on the circle." << endl;
    }
    else if (distance > rdistance){
        cout << "The point is outside the circle." << endl;
    }
    else if (distance < rdistance){
        cout << "The point is inside the circle." << endl;
    }
    else{
        cout << "ERROR!" << endl;
    }
}



int main(){

    int r, x, y;

    cout << "Please input the radius of the circle: " << endl;
    cin >> r;
    cout << "Please input the x-axis of the center: " << endl;
    cin >> x;
    cout << "Please input the y-axis of the center: " << endl;
    cin >> y;
    
    Circle c;
    c.setR(r);
    Point center;
    center.setX(x);
    center.setY(y);
    c.setC(center);

    int a, b;

    cout << "Please input the x-axis of the point: " << endl;
    cin >> a;
    cout << "Please input the y-axis of the point: " << endl;
    cin >> b;

    Point p;
    p.setX(a);
    p.setY(b);

    judgeCir(c, p);

    copyright();
    Ryo();

    system("pause");

    return 0;
}