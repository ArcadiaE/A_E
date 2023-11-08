/*

===== human.cpp ========================================================

*/

#include <iostream>
//#include <sstream>
//#include <cmath>
#include <cstdlib>

using namespace std;

#include "elf.h"


void Elf::TakeStrength()
{
    return;
}

void Elf::TakeHitpoints()
{
    return;
}

void Elf::Killed()
{
    return;
}



int Elf::getDamage() const
{

//    cout <<"from elf \n";
    int damage(Creature::getDamage());
    if ((rand( ) % 10)==0)
    {
        cout << "Magical attack ! "<< endl;
        damage = damage * 2;
    }
    cout << getSpecies( ) << " inflicts " <<
         damage << " damage!" << endl;
    return damage;

}


string Elf::getSpecies() const
{
    return "Elf";
}
