/*

===== human.cpp ========================================================

*/

#include <iostream>
//#include <sstream>
//#include <cmath>
//#include <cstdlib>

using namespace std;

#include "human.h"


void Human::TakeStrength(){
return;
}

void Human::TakeHitpoints(){
return;
}

void Human::Killed(){
return;
}



int Human::getDamage() const {

//    cout <<"from human \n";
//    const Creature * ptr_c = this;
//    int damage(ptr_c->getDamage());
    int damage(Creature::getDamage());

    cout << getSpecies( ) << " inflicts " <<
         damage << " damage!" << endl;

    return damage;

}


string Human::getSpecies() const{
    return "Human";
}
