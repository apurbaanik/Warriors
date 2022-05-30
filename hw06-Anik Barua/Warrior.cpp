/*
	Title: Warrior.cpp - Separate Compilation
	Author: Anik Barua
    Date: 03-24-2022

	Description: This is the implementation file for Warrior class. It includes 
    the definition of the function prototypes of the warrior header file.
*/

#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {
    // Warrior Class
    Warrior::Warrior(const string& name, double strength): name(name), strength(strength), myNoble(nullptr) {}
    //Hire status is false in constructor i.e. available for hire and myNoble is set to nullptr (not hired by any noble yet)

    //returns warrior name
    const string& Warrior::getName() const {
        return name;
    }

    //returns warrior strength
    double Warrior::getStrength() const {
        return strength;
    }

    //sets warrior strength
    void Warrior::setStrength(double newStrength) {
        strength = newStrength;
    }
    
    //sets noble pointer for warrior's noble
    void Warrior::setNoble(Noble* noble) {
        myNoble = noble;
    }

    //returns warrior hire status
    bool Warrior::isHired() const {
        return myNoble;
    }

    // runaway() calls the Noble's removeFromArmy() method to remove the warrior from his army
    bool Warrior::runaway(){
        // checking if the noble exists and the noble is alive
        if(myNoble && myNoble->getAliveStatus()){
            cout << name << " flees in terror, abandoning his lord, " << myNoble->getName() << endl;
            return myNoble->removeFromArmy(this); //calls the Noble's removeFromArmy() method
        }
        return false;
    }

    /*
    operator<< is a friend function for Warrior class that outputs Warrior's name and strength
    */ 
    ostream& operator<<(ostream& output, const Warrior& warrior) {
        output << "\t" << warrior.name << ": " << warrior.strength;
        return output;
    }
}