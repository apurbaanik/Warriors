/*
	Title: Noble.h
	Author: Anik Barua
    Date: 04-12-2022

	Description: This is the header file for our Noble class. It also includes the 
    derived Lord and PersonWithStrengthToFight class. It is used by the Noble.cpp,
    Protector.cpp and main for Separate Compilation.
*/

// Include Guards
#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    //Forward class declaration
    class Protector;

    //Noble class
    class Noble {
        //friend function operator<< for noble class
        friend std::ostream& operator<<(std::ostream& output, const Noble& noble);
    public:
        Noble(const std::string& name); //constructor
        const std::string& getName() const; //returns Noble name
        void battle(Noble& noble2); //battle between between two nobles
        bool getAliveStatus() const; //returns Noble's alive status
        void setAliveStatus(bool status); //sets Noble's alive status
        virtual void defend() const = 0; //virtual defend method for each noble
        virtual double getStrength() const = 0; //virtual method that returns Noble's strength
        virtual void changeStrength(double ratio) = 0; //virtual method that changes strength based on the ratio 
        virtual void changeStrengthToZero() = 0; //virtual method that changes strength to zero
        virtual std::ostream& display(std::ostream& output) const = 0; //virtual display method used by the output operator<< 
    private:
        std::string name; //Noble's name
        bool isAlive; //To check if noble is alive or dead
    };

    //Lord
    class Lord : public Noble { //Inherits from Noble class
    public:
        Lord(const std::string& name); //constructor
        void defend() const; //overrides the defend method specific to lord
        bool hires(Protector& protector); //Hire's protector in Lords's army
        bool fires(Protector& protector); //Fire's a protector from the noble's army
        double getStrength() const; //overidden method that return the strength of the army
        void changeStrengthToZero(); //overidden method that return the strength of the army
        void changeStrength(double ratio); //overidden method that changes strength of each protector based on the ratio
        bool removeFromArmy(Protector* protector); //Removes protector from the army (used by fires and protector's runaway method)
        std::ostream& display(std::ostream& output) const; //overidden method that displays the loard information along with his protectors
    private:
        std::vector<Protector*> army; //Lords's army is a vector of pointers to protectors
    };

    //PersonWithStrengthToFight 
    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string& name, double strength); //constructor
        void defend() const; //overrides the defend method specific to PersonWithStrengthToFight
        double getStrength() const; //overidden method that returns the strength of the Noble
        void changeStrength(double ratio); //overidden method that changes strength based on the ratio
        void changeStrengthToZero(); //overidden method that changes the strength to zero
        std::ostream& display(std::ostream& output) const; //overidden method that displays the noble information 
    private:
        double strength; // Strength of PersonWithStrengthToFight
    };
}
#endif