/*

===== cyberdemon.cpp ========================================================

*/

#include <iostream>
//#include <sstream>
//#include <cmath>
//#include <cstdlib>

using namespace std;

#include "cyberdemon.h"


void Cyberdemon::TakeStrength(){
return;
}

void Cyberdemon::TakeHitpoints(){
return;
}

void Cyberdemon::Killed(){
return;
}



int Cyberdemon::getDamage() const {

//    cout <<"from Cyberdemon \n";
//    const Demon * ptr_d = this;
//    int damage(ptr_d->getDamage());
    int damage(Demon::getDamage());

    cout << getSpecies( ) << " inflicts " <<
         damage << " damage!" << endl;

    return damage;

}


string Cyberdemon::getSpecies() const{
    return "Cyberdemon";
}
