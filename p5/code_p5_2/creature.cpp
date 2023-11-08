//
// creature.cpp
//
// implementation of creature class
//

#include <iostream>
//#include <sstream>
//#include <cmath>
#include <cstdlib>

using namespace std;

#include "creature.h"




/*
string Creature::getSpecies()
{
    switch (type)
    {
    case 0:
        return "Human";
    case 1:
        return "Cyberdemon";
    case 2:
        return "Balrog";
    case 3:
        return "Elf";
    }
    return "Unknown";
}
*/


int Creature::getDamage() const {

//    cout <<"from base \n";
    int damage;
// All creatures inflict damage, which is a
// random number up to their strength
    damage = (rand( ) % strength) + 1;
    return damage;

}

