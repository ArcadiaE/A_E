/*

===== demon.cpp ========================================================

*/

#include <iostream>
//#include <sstream>
//#include <cmath>
#include <cstdlib>

using namespace std;

#include "demon.h"








int Demon::getDamage() const {

//    cout <<"from demon \n";
    int damage(Creature::getDamage());
// Demons can inflict damage of 50 with a 5% chance
        if ((rand( ) % 100) < 5)
        {
            damage = damage + 50;
            cout << "Demonic attack ! " << endl;
        }

    return damage;

}

