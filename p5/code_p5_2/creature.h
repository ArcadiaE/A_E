//=============================================================================
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================

/*

Class Hierachy

Creature
	Elf
	Human
	Demon
        Cyberdemon
        Balrog
*/


#ifndef __CREATURE_H__
#define __CREATURE_H__

//
// creature.h
//

//#include <iostream>
//#include <sstream>
//#include <cmath>
//#include <cstdlib>

using namespace std;




class Creature
{
public:
//    Creature( );
// Initialize to human, 10 strength, 10 hit points
    Creature(int newStrength = 10, int newHit = 10) : strength(newStrength), hitpoints(newHit) {}
// Initialize creature to new type, strength, hit points
// Also add appropriate accessor and mutator functions
// for type, strength, and hit points
//    virtual void setType() = 0;
/*
    virtual void TakeStrength() = 0;
    virtual void TakeHitpoints() = 0;
    virtual void Killed() = 0;
    virtual int getDamage() const = 0;
*/
    virtual void TakeStrength( void ) { return; }
    virtual void TakeHitpoints( void ) { return; }
    virtual void Killed( void ) { return; }
    virtual int getDamage( void ) const ;

// Returns amount of damage this creature
// inflicts in one round of combat

private:
//    int type; // 0 human, 1 cyberdemon, 2 balrog, 3 elf
    int strength; // How much damage we can inflict
    int hitpoints; // How much damage we can sustain
    virtual string getSpecies( void ) const = 0;// Returns type of species
//    virtual string getSpecies( void ) const { return "Unknown"; }// Returns type of species

};





#endif  //__CREATURE_H__
