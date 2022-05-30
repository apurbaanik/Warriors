/*
	Title: Noble.cpp
	Author: Anik Barua
    Date: 04-12-2022

	Description: This is the implementation file for Noble class, Lord class, and
    PersonWithStrengthToFight class. It includes the definition of the function 
    prototypes of the noble header file.
*/

//including the header files
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {
    //Noble class 
    Noble::Noble(const string& name) : name(name), isAlive(true) {} //constructor

    //returns Noble name
    const string& Noble::getName() const { 
        return name; 
    }

    //returns Noble's alive status
    bool Noble::getAliveStatus() const { 
        return isAlive; 
    } 

    //sets Noble's alive status
    void Noble::setAliveStatus(bool status) { 
        isAlive = status; 
    }

    /*
        battle() method between two nobles. It displays one line to says who is fighting whom 
        and a second line to report the results.
    */
    void Noble::battle(Noble &noble2) {
        cout << name << " battles " << noble2.getName() << endl;
        if (isAlive) { //fights when noble1 is alive
            //calls the defend method of Noble's
            this->defend();
        }
        if (noble2.isAlive) { //fights when noble2 is alive
            //calls the defend method of Noble's 
            noble2.defend();
        } 
        if (!isAlive && !noble2.isAlive) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        } else if (!isAlive) { // if noble1 is dead and noble2 is alive
            cout << "He's dead, " << noble2.getName() << endl;
        } else if (!noble2.isAlive) { // if noble2 is dead and noble1 is alive
            cout << "He's dead, " << name << endl;
        } else { // if both participants are alive 
            double noble1Strength = getStrength();
            double noble2Strength = noble2.getStrength();
            if (noble1Strength > noble2Strength) { // if noble 1 strength is greater than noble 2's strength
                double ratio = noble2Strength / noble1Strength;
                this->changeStrength(ratio);
                noble2.changeStrengthToZero();
                cout << name << " defeats " << noble2.getName() << endl;
            } else if (noble1Strength < noble2Strength) { // if noble 1 strength is less than noble 2's strength
                double ratio = noble1Strength/noble2Strength;
                noble2.changeStrength(ratio);
                this->changeStrengthToZero();
                cout << noble2.getName() << " defeats " << name << endl;
            } else { // if noble 1 strength is same as noble 2's strength
                this->changeStrengthToZero();  // noble 1 is dead
                noble2.changeStrengthToZero(); // noble 2 is dead
                cout << "Mutual Annihilation: " << name << " and " << noble2.getName() << " die at each other's hands" << endl;
            }
        }
    }

    //Lord
    Lord::Lord(const string& name) : Noble(name) {} //constructor

    //Hire's protectors in Lords's army
    bool Lord::hires(Protector& protector) {
        if (getAliveStatus() == true) { // Checks if the Lord is alive
            if (protector.isHired() == false && protector.isAlive() == true) { // checks if available for hire and alive
                protector.setNoble(this); // protector's noble 
                army.push_back(&protector); // protector is in the army 
                return true;
            }
        }
        return false; // Either the lord is dead or the protector is not available for hire
    }

    //To fire a protector from lord's army
    bool Lord::fires(Protector& protector) {
        //Checks if the lord is alive and the protector is already hired
        if (getAliveStatus() == true && protector.isHired() == true) { 
            //calls the removeFromArmy() method to remove the protector
            bool check = removeFromArmy(&protector); 
            if(check) {
                cout << "You don't work for me anymore " << protector.getName() << "! -- " << getName() << "." << endl;
                return true;
            }
        }
        return false; // Either the lord is dead or the protector is not in his army
    }

    //removeFromArmy() removes the protector from lord's Army
    bool Lord::removeFromArmy(Protector* protector) { //takes the protector pointer
        for(size_t i = 0; i < army.size(); ++i){
            if(army[i] == protector){ // checks if the protector is in the current army by checking the same memory address
                protector->setNoble(nullptr); // setting protector's noble to nullptr i.e. he is not in any lord's army
                for (size_t index = i; index < army.size() - 1; ++index) {
                    army[index] = army[index + 1]; //moving the protector location to the end of the vector
                }
                army.pop_back(); //removing it from the vector
                return true;
            }
        }
        return false; // the protector is not in the army
    }

    //returns total army strength
    double Lord::getStrength() const { 
        double total = 0;
        for (size_t i = 0; i < army.size(); ++i) {
            total += army[i]->getStrength();
        }
        return total; // returns stength of the lord (army strength)
    }

    //changes strength of each protector based on the ratio of opponent noble
    void Lord::changeStrength(double ratio) {
        for (size_t i = 0; i < army.size(); ++i) {
            double strength = army[i]->getStrength() - (army[i]->getStrength() * ratio);
            army[i]->setStrength(strength);
        }
    }

    //changes strength of each protector to zero
    void Lord::changeStrengthToZero() {
        setAliveStatus(false); //Lord is now dead
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->setStrength(0); 
        }
    }

    //Lord's defend() method calls each protector's indivdual defend() method
    void Lord::defend() const {
        for(size_t i = 0; i < army.size(); ++i){
            army[i]->defend();
        }
    }

    //display method used by the output operator<< 
    ostream& Lord::display(ostream& output) const {
        output << getName() << " has an army of " << army.size() << endl;
        for (size_t i = 0; i < army.size(); ++i) {
            // since each protector is a pointer, we have to dereference it
            output << *(army[i]) << endl;
        }
        return output;
    }

    //PersonWithStrengthToFight
    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, 
        double strength) : Noble(name), strength(strength) {} //constructor

    //returns noble's strength
    double PersonWithStrengthToFight::getStrength() const { 
        return strength; 
    }

    //defend() method for PersonWithStrengthToFight type noble
    void PersonWithStrengthToFight::defend() const {
        cout << "Ugh!" << endl;
    }

    //changes strength of noble based on the ratio of opponent noble
    void PersonWithStrengthToFight::changeStrength(double ratio) { 
        strength = strength - (strength * ratio); 
    }

    //changes the strength of noble to zero
    void PersonWithStrengthToFight::changeStrengthToZero() {
        setAliveStatus(false);
        strength = 0;
    }

    //display method for PersonWithStrengthToFight used by the output operator<< 
    ostream& PersonWithStrengthToFight::display(ostream& output) const {
        output << getName() << " has an strength of " << strength;
        return output;
    }

    /*
    operator<< is a friend function for Noble class that calls the display method of individual noble's display 
    */
    ostream& operator<<(ostream& output, const Noble& noble) {
        return noble.display(output);
    }
}