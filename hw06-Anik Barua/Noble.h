/*
	Title: Noble.h - Separate Compilation
	Author: Anik Barua
    Date: 03-24-2022

	Description: This is the header file for Noble class. It is used by the 
    warrior class, noble class and main for Separate Compilation assignment.
*/

// Include Guards
#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    class Warrior; // Forward class declaration
    
    //Noble Class
    class Noble {
        //friend function operator<< for noble class
        friend std::ostream& operator<<(std::ostream& output, const Noble& noble);
    public:
        Noble(const std::string& name); //constructor
        const std::string& getName() const; //returns Noble name
        const bool& getAliveStatus() const; //returns Noble's alive status
        bool hire(Warrior& warrior); //Hire's warrior in Noble's army
        bool removeFromArmy(Warrior* warrior); //Removes warrior from the army (used by fire and warrior's runaway method)
        bool fire(Warrior& warrior); //Fire's a warrior from the noble's army
        double getArmyStrength() const;  //returns total army strength
        void changeStrength(double ratio); //changes strength of each warrior based on the ratio of opponent army
        void changeStrengthtoZero(); //changes strength of each warrior to zero
        void changeArmyStrength(Noble& noble); // responsible for changing army's strength
        void battle(Noble& noble2); // battle between between two nobles
    private:
        std::string name; // Noble's name
        std::vector <Warrior*> army; // Noble's army is a vector of pointers to warriors
        bool isAlive; // To check if noble is alive or dead
    };
}
#endif