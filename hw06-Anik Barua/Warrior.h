/*
	Title: Warrior.h - Separate Compilation
	Author: Anik Barua
    Date: 03-24-2022

	Description: This is the header file for Warrior class. It is used by the 
    warrior class, noble class and main for Separate Compilation assignment.
*/

// Include Guards
#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    class Noble; // Forward class declaration 
    
    // Warrior Class
    class Warrior {
        //friend function operator<< for warrior class
        friend std::ostream& operator<<(std::ostream& output, const Warrior& warrior);
    public:
        Warrior(const std::string& name, double strength); //constructor
        const std::string& getName() const;  //returns warrior name
        double getStrength() const;  //returns warrior strength
        void setStrength(double strength); //sets warrior strength
        void setNoble(Noble* noble); // sets the noble for warrior's noble
        bool isHired() const; //returns warrior hire status
        bool runaway(); //runaway method for warrior
    private:
        std::string name;
        double strength;
        Noble* myNoble; // a pointer to his noble
    };
}
#endif