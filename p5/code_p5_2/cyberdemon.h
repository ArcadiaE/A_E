//=============================================================================
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================


#ifndef __CYBERDEMON_H__
#define __CYBERDEMON_H__


//
// cyberdemon.h
//

//#include <sstream>
//#include <cmath>
//#include <cstdlib>

//using namespace std;


#ifndef __DEMON_H__
#include "demon.h"
#endif

class Cyberdemon : public Demon
{
public:
    Cyberdemon(int newStrength = 10, int newHit = 10) : Demon(newStrength, newHit), strength(newStrength), hitpoints(newHit) {}

    void TakeStrength();
    void TakeHitpoints();
    void Killed();
    int getDamage() const ;

private:
    int strength; // How much damage we can inflict
    int hitpoints; // How much damage we can sustain
    string getSpecies() const;

};



#endif  //__CYBERDEMON_H__
