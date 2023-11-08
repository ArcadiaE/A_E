//适度编程益脑，过度编程伤身
//合理安排时间，享受健康生活
//copyright: @A_E 
//email: yz50u22@soton.ac.uk

#include<iostream>


#include"copyright.h"

using namespace std;

class AbstractDrinking
{
    public:
    virtual void Boil () = 0;
    virtual void Brew () = 0;
    virtual void Boot () = 0;
    virtual void Ingr () = 0; 

    void MakeDrinks (){
        Boil();
        Brew();
        Boot();
        Ingr();
    }
};

class Coffee : public AbstractDrinking
{
    public:
    virtual void Boil (){
        cout << "Hot Water" << endl;
    }
    virtual void Brew (){
        cout << "Coffee" << endl;
    }
    virtual void Boot (){
        cout << "Medium cup" << endl;
    }
    virtual void Ingr (){
        cout << "Milk(DONT PUT THAT FUCKING SUGER INTO THIS BLOODY COFFEE!!!)" << endl;
    }

};

class Tea : public AbstractDrinking
{
    public:
    virtual void Boil (){
        cout << "Hot Water" << endl;
    }
    virtual void Brew (){
        cout << "Tea-Leaf" << endl;
    }
    virtual void Boot (){
        cout << "Medium cup" << endl;
    }
    virtual void Ingr (){
        cout << "Milk & Sugger" << endl;
    }

};

void doWork(AbstractDrinking * abs){
    abs->MakeDrinks();
    delete abs;
}

void apply1(){
    doWork(new Coffee);
}

void apply2(){
    doWork(new Tea);
}

void finalmake(){
    cout << "What kind of drinks do you want?" << endl;
    cutline();
    cout << "1. Coffee " << endl;
    cout << "2. Tea" << endl;
    cout << "Sorry, other drinks are out of the order because of the strike." << endl;
    cutline();
    int DrinkType;
    cin >> DrinkType ;
    if(DrinkType = 1){
        apply1();
    }
    else if (DrinkType = 2){
        apply2();
    }
    else{
        cout << "Sorry, the drink is out of the order because of the strike. Comming soon!" << endl;
    }
}

int main()
{
    finalmake();

    copyright();
    system("pause");

    return 0;
}
