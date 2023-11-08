//
//
//
// file: main_p5.cpp
// last modified:
// copyright:
// version:
//
// email:
// web:
//



#include <iostream>
#include <cstdlib>
//#include <iomanip>
//#include <iterator>


#include "human.h"
#include "elf.h"
#include "cyberdemon.h"
#include "balrog.h"

using namespace std;


void Human::TakeStrength(){
return;
}

void Human::TakeHitpoints(){
return;
}

void Human::Killed(){
return;
}



int Human::getDamage() const {

//    cout <<"from human \n";
//    const Creature * ptr_c = this;
//    int damage(ptr_c->getDamage());
    int damage(Creature::getDamage());

    cout << getSpecies( ) << " inflicts " <<
         damage << " damage!" << endl;

    return damage;

}


string Human::getSpecies() const{
    return "Human";
}

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

int Creature::getDamage() const {

//    cout <<"from base \n";
    int damage;
// All creatures inflict damage, which is a
// random number up to their strength
    damage = (rand( ) % strength) + 1;
    return damage;

}

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




int main(/* int argc, char *argv[] */ )
{

    srand(1500);

    Human h0(10,10);
    Elf e0(10,10);
    Cyberdemon c0(10,10);
    Balrog b0(10,10);

    Creature * Entity[] = { &h0, &e0, &c0, &b0};

    for(int i=0;;i++)
    {
        cout<<"Turn "<<i<<":"<<endl;
        cout<<"\t";
        Entity[0]->getDamage();
        cout<<"\t";
        Entity[1]->getDamage();
        cout<<"\t";
        Entity[2]->getDamage();
        cout<<"\t";
        Entity[3]->getDamage();
        cout<<"\t";
        cout<<endl;
//        _sleep(1000);
        system("pause");
    }

/*
    for(int i=0;;i++)
    {
        cout<<"Turn "<<i<<":"<<endl;
        cout<<"\t";
        h0.getDamage();
        cout<<"\t";
        e0.getDamage();
        cout<<"\t";
        c0.getDamage();
        cout<<"\t";
        b0.getDamage();
        cout<<"\t";
        cout<<endl;
//        _sleep(1000);
        system("pause");
    }
*/

    return 0;
}
