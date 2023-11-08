//=============================================================================
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================


#ifndef __DEMON_H__
#define __DEMON_H__


//
// demon.h
//

//#include <sstream>
//#include <cmath>
//#include <cstdlib>

//using namespace std;


#ifndef __CREATURE_H__
#include "creature.h"
#endif

class Demon : public Creature
{
public:
    Demon(int newStrength = 10, int newHit = 10) : Creature(newStrength, newHit), strength(newStrength), hitpoints(newHit) {}

    int getDamage() const ;

/*
    virtual void TakeStrength( void ) { return; }
    virtual void TakeHitpoints( void ) { return; }
    virtual void Killed( void ) { return; }
    virtual int getDamage( void ) { return; }
*/

private:
    int strength; // How much damage we can inflict
    int hitpoints; // How much damage we can sustain
    string getSpecies( void ) const = 0;

};





#endif  //__DEMON_H__
