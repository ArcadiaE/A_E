//适度编程益脑，过度编程伤身
//合理安排时间，享受健康生活
//copyright: @A_E 
//email: yz50u22@soton.ac.uk

#include"copyright.h"

#include <string>
#include <iostream>

using namespace std;

class Pet {
public:
    Pet(string p_name, int p_age, int p_weight ) 
        : name(p_name), age(p_age), weight(p_weight){}

    void setName(string p_name) const {
        p_name = name;
    }
    string getName() {
        return name;
    }

    void setAge(int p_age) const {
        p_age = age;
    }
    int getAge() {
        return age;
    }

    void setWeight(int p_weight){
        p_weight = weight;
    }
    int getWeight(){
        return weight;
    }

    string getLifespan(){
        return "unkown lifespan";
    }

private:
    string name, lifespan;
    int age;
    int weight;

};

class Dog : public Pet {
public:
    Dog(string p_name, int p_age, int p_weight, string p_breed) :  
        Pet(p_name, p_age, p_weight), breed(p_breed) {}

    void setBreed(string p_breed){
        p_breed = breed;
    }
    string getBreed(){
        return breed;
    }

    string getLifespan(){
        if (getWeight() > 100){
            return "Approximately 7 years.";
        }
        else if (getWeight() < 100){
            return "Approximately 13 years";
        }
        else{
            return "Unable to get lifespan, please check the weight you entered";
        }
    }
private:
    string breed;
};

void test_pet(){
    Pet Cat("P", 3, 30);

    cout << Cat. getName() << endl;
    cout << Cat. getAge() << endl;
    cout << Cat. getWeight() << endl;
    cout << Cat. getLifespan() << endl;
}

void test_dog(){
    Dog Dog1("D", 5, 59, "Meat");

    cout << Dog1. getName() << endl;
    cout << Dog1. getAge() << endl;
    cout << Dog1. getWeight() << endl;
    cout << Dog1. getBreed() << endl;
    cout << Dog1. getLifespan() << endl;
}

int main(){

    test_pet();
    test_dog();

    Ryo();
    copyright();

    system("pause");
    return 0;

}