//=============================================================================
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================


#ifndef __ELF_H__
#define __ELF_H__


//
// elf.h
//

//#include <sstream>
//#include <cmath>
//#include <cstdlib>

//using namespace std;


#ifndef __CREATURE_H__
#include "creature.h"
#endif

class Elf : public Creature
{
public:
    Elf(int newStrength = 10, int newHit = 10) : Creature(newStrength, newHit), strength(newStrength), hitpoints(newHit) {}

    void TakeStrength();
    void TakeHitpoints();
    void Killed();
    int getDamage() const;

private:
    int strength; // How much damage we can inflict
    int hitpoints; // How much damage we can sustain
    string getSpecies() const;

};





#endif  //__ELF_H__
