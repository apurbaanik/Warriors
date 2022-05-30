/*
	Title: Noble.cpp - Separate Compilation
	Author: Anik Barua
    Date: 03-24-2022

	Description: This is the implementation file for Noble class. It includes 
    the definition of the function prototypes of the noble header file.
*/

#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {
    // Noble Class
    Noble::Noble(const string& name): name(name), isAlive(true) {}

    //returns Noble name
    const string& Noble::getName() const {
        return name;
    }

    //returns Noble's alive status
    const bool& Noble::getAliveStatus() const {
        return isAlive;
    }

    //Hire's warrior in Noble's army
    bool Noble::hire(Warrior& warrior) {
        if (isAlive == true) {// Checks if the Noble is alive
            if (warrior.isHired() == false) { // checks if available for hire
                warrior.setNoble(this); // warrior's noble 
                army.push_back(&warrior); // warrior is in the army 
                return true;
            }
        }
        return false; // Either the noble is dead or the warrior is not available for hire
    }

    // removeFromArmy() removes the warrior from Nobles Army
    bool Noble::removeFromArmy(Warrior* warrior){ //takes the warrior pointer
        for(size_t i = 0; i < army.size(); ++i){
            if(army[i] == warrior){ // checks if the warrior is in the current army by checking the same memory address
                warrior->setNoble(nullptr); // setting warrior's noble to nullptr i.e. he is not in any noble's army
                for (size_t index = i; index < army.size() - 1; ++index) {
                    army[index] = army[index + 1]; //moving the warrior location to the end of the vector
                }
                army.pop_back(); //removing it from the vector
                return true;
            }
        }
        return false; // the warrior is not in the army
    }

    //To fire a warrior from the noble's army
    bool Noble::fire(Warrior& warrior) {
    if (isAlive == true && warrior.isHired() == true) { // Checks if the Noble is alive and the warrior is already hired
        bool check = removeFromArmy(&warrior); // calls the removeFromArmy() method to remove the warrior
            if(check) {
                cout << "You don't work for me anymore " << warrior.getName() << "! -- " << name << "." << endl;
                return true;
            }
        }
        return false; // Either the noble is dead or the warrior is not in his army
    }

    //returns total army strength
    double Noble::getArmyStrength() const {
        double total = 0;
        for (size_t i = 0; i < army.size(); ++i) {
            total += army[i]->getStrength();
        }
        return total; // returns stength of the noble (army strength)
    }

    //changes strength of each warrior based on the ratio of opponent army
    void Noble::changeStrength(double ratio) {
        for (size_t i = 0; i < army.size(); ++i) {
            double strength = army[i]->getStrength() - (army[i]->getStrength() * ratio);
            army[i]->setStrength(strength);
        }
    }

    //changes strength of each warrior to zero
    void Noble::changeStrengthtoZero() {
        isAlive = false; //Noble is now dead
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->setStrength(0);
        }
    }

    /*
    Changes the Army's Strength - used by the battle method. The passed noble is the losing noble.
    */
    void Noble::changeArmyStrength(Noble& noble2) {
        double ratio = noble2.getArmyStrength()/getArmyStrength();
        changeStrength(ratio);
        noble2.changeStrengthtoZero();
        cout << name << " defeats " << noble2.getName() << endl; 
    }

    /*
    battle() method between two nobles. It displays one line to says who is fighting whom 
    and a second line to report the results.
    */
    void Noble::battle(Noble& noble2) {
        cout << name << " battles " << noble2.getName() << endl;
        if (!isAlive && !noble2.isAlive) { // if both noble's are dead
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if(!isAlive) { // if noble1 is dead and noble2 is alive
            cout << "He's dead, " << noble2.getName() << endl;
        } else if(!noble2.isAlive) { // if noble2 is dead and noble1 is alive
            cout << "He's dead, " << name << endl;
        } else { // if both participants are alive 
            double noble1Strength = getArmyStrength();
            double noble2Strength = noble2.getArmyStrength();
            if (noble1Strength > noble2Strength) { // if noble 1 strength is greater than noble 2's strength
                this->changeArmyStrength(noble2);
            } else if (noble1Strength < noble2Strength) { // if noble 1 strength is less than noble 2's strength  
                noble2.changeArmyStrength(*this);
            } else { // if noble 1 strength is same as noble 2's strength 
                this->changeStrengthtoZero(); // noble 1 is dead
                noble2.changeStrengthtoZero(); // noble 2 is dead
                cout << "Mutual Annihilation: " << name << " and " << noble2.getName() << " die at each other's hands" << endl;
            }
        }
    }

    /*
    operator<< is a friend function for Noble class that outputs Noble's name, size and calls the warrior's operator<< function
    */
    ostream& operator<<(ostream& output, const Noble& noble) {
        output << noble.name << " has an army of " << noble.army.size() << endl;
        for (size_t i = 0; i < noble.army.size(); ++i) {
            output << *noble.army[i] << endl;
        }
        return output;
    }
}