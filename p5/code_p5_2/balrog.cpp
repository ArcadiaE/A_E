/*

===== balrog.cpp ========================================================

*/

#include <iostream>
//#include <sstream>
//#include <cmath>
#include <cstdlib>

using namespace std;

#include "balrog.h"


void Balrog::TakeStrength()
{
    return;
}

void Balrog::TakeHitpoints()
{
    return;
}

void Balrog::Killed()
{
    return;
}



int Balrog::getDamage() const
{

//    cout <<"from balrog \n";
//    const Demon * ptr_d = this;
//    int damage(ptr_d->getDamage());
    int damage(Demon::getDamage());

// Balrogs are so fast they get to attack twice
    int damage2 = (rand() % strength) + 1;
//    cout << "Balrog speed attack inflicts " << damage2 <<
//         " additional damage points!" << endl;
    damage = damage + damage2;
    cout << getSpecies( ) << " inflicts " <<
         damage << " damage!" << endl;

    return damage;

}


string Balrog::getSpecies() const
{
    return "Balrog";
}
