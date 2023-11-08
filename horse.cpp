//适度编程益脑，过度编程伤身
//合理安排时间，享受健康生活
//copyright: @A_E 
//email: yz50u22@soton.ac.uk

#include<iostream>


#include"copyright.h"

using namespace std;

class Horse {
public:
    Horse() : horseName("No name yet"), horseAge(0) {}
    Horse(const string& theName, const int& theAge) : horseName(theName), horseAge(theAge) {}

    void setName(const string& newName){
        horseName = newName;
    }
    string getName() const{
        return horseName;
    }

    void setAge(const int& newAge) {
       horseAge = newAge;
    }
    int getAge() const {
        return horseAge;
    }

    void printInfo() const {
        cout << "Is that a unicorn? Program terminates!"; 
        exit (1); 
    }

private:
    string horseName;
    int horseAge;
};

class DraftHorse : public Horse{
public:
    DraftHorse() : Horse(), horsePower (0) {} 
    DraftHorse(const string& theName, const int& theAge, const double& thePower) 
                : Horse(theName, theAge), horsePower (thePower) {}
    
    double getPower() const { 
        return horsePower; 
    }
    
    void setPower(const double& newPower) { 
        horsePower = newPower; 
    }
    
    void printInfo() const { 
        cout << getName() << " is a draft horse of age " << getAge() << " who can deliver power at " << 
                getPower() << " units.\n";
    }
private:
    double horsePower;
};

class RaceHorse : public Horse {
public:
    RaceHorse() : Horse(), horseSpeed(0) {}
    RaceHorse(const string& theName, const int& theAge, const double& theSpeed) 
                : Horse(theName, theAge), horseSpeed(theSpeed) {}

    double getSpeed() const { 
        return horseSpeed; 
    }

    void setSpeed(const double& newSpeed) { 
        horseSpeed=newSpeed; 
    }
    
    void printInfo() const { 
        cout << getName() << " is a race horse of age " << getAge() << " who can dash at " << getSpeed() << 
            " km per hour.\n";
    }
private:
    double horseSpeed;
};

int operator +(const Horse& horse1, const Horse& horse2){
    return (horse1.getAge()+horse2.getAge());
}

int main()
{

    DraftHorse daniel("Daniel", 6, 1.56);
    RaceHorse ryan("Ryan", 8, 75.1);
    daniel.printInfo();
    ryan.printInfo();
 
    cout << "The two horses have been with us for a total of "
        << daniel+ryan << " years.\n";
 
    Horse harrison;
    harrison.printInfo();

    copyright();
    system("pause");

    return 0;
}
