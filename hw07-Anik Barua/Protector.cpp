/*
	Title: Protector.cpp
	Author: Anik Barua
    Date: 04-12-2022
    
	Description: This is the implementation file for Protector class, Wizard class, 
    Warrior class,  Archer class and  Swordsman class. It includes the definition 
    of the function prototypes of the protector header file.
*/

//including the header files
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft {
    //Protector Class
    Protector::Protector(const string& name, double strength) : name(name), strength(strength), myLord(nullptr) {} //constructor
    //Hire status is false in constructor i.e. available for hire and myLord is set to nullptr (not hired by any lord yet)

    //returns protector name
    const string& Protector::getName() const { 
        return name; 
    }

    //returns protector strength
    double Protector::getStrength() const {
        return strength; 
    }

    //returns if protector is alive
    bool Protector::isAlive() const { 
        return strength > 0; 
    }  

    //returns protector hire status
    bool Protector::isHired() const { 
        return myLord; 
    }

    //sets the lord for protector's noble
    void Protector::setNoble(Lord* lord) { 
        myLord = lord; 
    }

    //sets protector strength
    void Protector::setStrength(double newStrength) { 
        strength = newStrength; 
    }

    //returns protector Lord's name
    const string& Protector::getLordName() const { 
        return myLord->getName(); 
    }

    // runaway() calls the Lord's removeFromArmy() method to remove the protector from his army
    bool Protector::runaway(){
        // checking if the lord exists and the lord is alive
        if(myLord && myLord->getAliveStatus()) {
            cout << name << " flees in terror, abandoning his lord, " << myLord->getName() << endl;
            return myLord->removeFromArmy(this); //calls the Noble's removeFromArmy() method
        }
        return false;
    }

    //Wizard class - Inherits from protector class, so calling Protector constructor to initialize the name and strength
    Wizard::Wizard(const string& name, double strength) : Protector(name, strength) {}

    //overrides the defend() virtual method
    void Wizard::defend() const { 
        cout << "POOF!" << endl; 
    };

    //Warrior class - Inherits from protector class, so calling Protector constructor to initialize the name and strength
    Warrior::Warrior(const string& name, double strength) : Protector(name, strength) {}

    //Archer class - Inherits from warrior class, so calling warrior constructor to initialize the name and strength
    Archer::Archer(const string& name, double strength) : Warrior(name, strength) {}

    //overrides the defend() virtual method
    void Archer::defend() const {
        cout << "TWANG!  " << this->getName() << " says: Take that in the name of my lord, " << this->getLordName() << endl;
    };

    //Swordsman - Inherits from warrior class, so calling warrior constructor to initialize the name and strength
    Swordsman::Swordsman(const string& name, double strength) : Warrior(name, strength) {}

    //overrides the defend() virtual method
    void Swordsman::defend() const {
        cout << "CLANG!  " << this->getName() << " says: Take that in the name of my lord, " << this->getLordName() << endl;
    }
    
    /*
    operator<< is a friend function for protector class that outputs protector's name and strength
    */
    ostream& operator<<(ostream& output, const Protector& protector) {
        output << "\t" << protector.name << ": " << protector.strength;
        return output;
    }
}