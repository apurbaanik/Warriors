/*
	Title: Protector.h
	Author: Anik Barua
    Date: 04-12-2022

	Description: This is the header file for our Protector class. It also includes the 
    derived Wizard, Warrior, Archer and Swordsman class. It is used by the Protector.cpp, 
    Noble.cpp, and main for Separate Compilation.
*/

// Include Guards
#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    //Forward class declaration
    class Lord;

    //Protector Class
    class Protector {
        //friend function operator<< for Protector class
        friend std::ostream& operator<<(std::ostream& output, const Protector& protector);
    public:
        Protector(const std::string& name, double strength); //constructor
        bool runaway(); //runaway method for warrior
        bool isAlive() const; //returns if protector is alive
        bool isHired() const; //returns protector hire status
        const std::string& getName() const; //returns protector name
        const std::string& getLordName() const; //returns protector Lord's name
        void setNoble(Lord* lord); //sets the lord for protector's noble
        double getStrength() const; //returns protector strength
        void setStrength(double newStrength); //sets protector strength
        virtual void defend() const = 0; //virtual defend() method used by the battle method and overidden for each warrior
    private:
        std::string name; //Protector's name
        double strength; //Protector's strength
        Lord* myLord; //a pointer to Protector's Load
    };

    //Wizard
    class Wizard : public Protector { //Inherits from protector class
    public:
        Wizard(const std::string& name, double strength);
        void defend() const; //overrides the defend() virtual method
    };

    //Warrior class 
    class Warrior : public Protector { //Inherits from protector class
    public:
        Warrior(const std::string& name, double strength); //constructor
    };

    //Archer
    class Archer : public Warrior { //Inherits from warrior class
    public:
        Archer(const std::string& name, double strength); //constructor
        void defend() const; //overrides the defend() virtual method
    };

    //Swordsman
    class Swordsman : public Warrior { //Inherits from warrior class
    public:
        Swordsman(const std::string& name, double strength); //constructor
        void defend() const; //overrides the defend() virtual method
    }; 
}
#endif