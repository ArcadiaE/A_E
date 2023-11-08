//=============================================================================
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================


#ifndef __HUMAN_H__
#define __HUMAN_H__


//
// human.h
//

//#include <sstream>
//#include <cmath>
//#include <cstdlib>

//using namespace std;


#ifndef __CREATURE_H__
#include "creature.h"
#endif

class Human : public Creature
{
public:
    Human(int newStrength = 10, int newHit = 10) : Creature(newStrength, newHit), strength(newStrength), hitpoints(newHit) {}

    void TakeStrength();
    void TakeHitpoints();
    void Killed();
    int getDamage() const ;

private:
    int strength; // How much damage we can inflict
    int hitpoints; // How much damage we can sustain
    string getSpecies() const;

};





#endif  //__HUMAN_H__
