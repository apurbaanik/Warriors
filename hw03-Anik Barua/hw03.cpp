/*
Title: Homework 03: Data hiding, encapsulation, delegation, overloading the output operator
Author: Anik Barua
Version: 2.0
Date: 02-17-2022

Description: This program is a updated version of the warrior game. Now each warrior will have 
a weapon and it is created together with the warrior (inside constructor). It can only be accessed 
by the warrior class. When a Warrior's weapon loses all of its strength, the Warrior himself dies.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

//Class Warrior
class Warrior{
    friend ostream& operator<<(ostream& output, const Warrior& warrior); // friend function for operator << in Warrior Class
    public:
    // Constructor
    Warrior(const string& warriorName, const string& weaponName, int strength) : warriorName(warriorName), weapon(weaponName, strength) {}

    // getName() returns the name of the warrior
    const string& getName() const {
	    return warriorName;
    }

    //battle() method displays one line to says who is fighting whom and a second line to report the results
    void battle(Warrior& warrior2) {
        cout << warriorName << " battles " << warrior2.warriorName << endl;
        // if warrior 1 weapon strength is greater than warrior 2's weapon
        if(weapon.getStrength() > warrior2.weapon.getStrength()){
            // checks if one of the participants is dead and the other is alive
            if(weapon.getStrength() != 0 && warrior2.weapon.getStrength() != 0){
                // subtracts the strength from warrior 1 weapon to warrior 2 weapon
                int newStrength = weapon.getStrength() - warrior2.weapon.getStrength();
                weapon.setStrength(newStrength);
                warrior2.weapon.setStrength(0);
                cout << warriorName << " defeats " << warrior2.warriorName << endl;
            } else {
                // one of the participants is dead and the other is alive
                if(weapon.getStrength() == 0) {
                    cout << "He's dead, " << warrior2.warriorName << endl;
                } else {
                    cout << "He's dead, " << warriorName << endl;
                }
            }
            // if warrior 1 weapon strength is less than warrior 2's weapon
        } else if(weapon.getStrength() < warrior2.weapon.getStrength()){
            // checks if one of the participants is dead and the other is alive
            if(weapon.getStrength() != 0 && warrior2.weapon.getStrength() != 0){
                // subtracts the strength from warrior 2 weapon to warrior 1's weapon
                int newStrength = warrior2.weapon.getStrength() - weapon.getStrength();
                warrior2.weapon.setStrength(newStrength);
                weapon.setStrength(0);
                cout << warrior2.warriorName << " defeats " << warriorName << endl;
            } else {
                // one of the participants is dead and the other is alive
                if(weapon.getStrength() == 0) {
                    cout << "He's dead, " << warrior2.warriorName << endl;
                } else {
                    cout << "He's dead, " << warriorName << endl;
                }
            }
            // if warrior 1 weapon strength is same as warrior 2 weapon
        } else if(weapon.getStrength() == warrior2.weapon.getStrength()){
            // checks if one of the participants is dead and the other is alive
            if(weapon.getStrength() != 0 && warrior2.weapon.getStrength() != 0){
                weapon.setStrength(0); // warrior 1 is dead
                warrior2.weapon.setStrength(0); // warrior 2 is dead
                cout << "Mutual Annihilation: " << warriorName << " and " << warrior2.warriorName << " die at each other's hands" << endl;
            } else {
                // both warriors are dead
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
        }
    } // end of battle() method

    private:    
    //private Weapon class
    class Weapon{
        friend ostream& operator<<(ostream& output, const Weapon& weapon); // friend function
        public:
        Weapon(const string& weaponName, int strength) : weaponName(weaponName), strength(strength) {} // Constructor

        // returns weapons strength
        int getStrength() const {
	        return strength;
        }

        // sets weapons strength
        void setStrength(int strength1) {
            strength = strength1;
        }
        private:
        string weaponName;
        int strength;
    };

    friend ostream& operator<<(ostream& output, const Warrior::Weapon& weapon); // friend function for operator<< Weapon Class
    string warriorName;
    Weapon weapon;
};

//Prototypes for functions
size_t check(const string& warriorName, const vector<Warrior>& warriors);
void insertWarrior(const string& name, const string& weaponName,int strength, vector<Warrior>& warriors);

// Main
int main(){
    ifstream reader("warriors.txt"); // reading the "warriors.txt" file
    if (!reader) {
        cerr << "Failed to open encrypted.txt";
        exit(1);
    }
    string line; // line reads the first command
    int strength; // reads the weapons strength
    string name, weaponName; // name reads the warrior name and weaponName reads the weapon's name
    string warrior1, warrior2; // for battle command, reads two warriors name
    vector<Warrior> warriors; // vectors that will store the warriors
    while(reader >> line){
        // Warrior Command
        if(line == "Warrior"){
            reader >> name >> weaponName >> strength;
            insertWarrior(name, weaponName, strength, warriors); //creates and inserts new Warrior if the Warrior's name is unique  
        } else if(line == "Status"){
            // Status Command - lists all warriors with their weapons name, alive or dead, and their weapons strengths
            cout << "There are: " << warriors.size() << " warriors\n";
            for (size_t i = 0; i != warriors.size(); i++){
                operator<< warriors[i]; // uses class's output operator.
            }
        } else if(line == "Battle"){
            // Battle Command
            reader >> warrior1 >> warrior2;
            size_t position1 = check(warrior1, warriors);
            size_t position2 = check(warrior2, warriors);
            // checks if one or both warriors doesn't exits
            if (position1 != warriors.size() && position2 != warriors.size()){
                warriors[position1].battle(warriors[position2]); // calls the warrior class battle method
            } else {
                // if one or both of them have not been defined yet
                cout << "Error: One or both warriors doesn't exits." << endl;
            }
        }
    }
    reader.close(); //closing the file
    return 0;
} // end of main

/*
check() function takes the warrior name and the warriors vector, and returns the positon of the warrior in the vector
*/
size_t check(const string& warriorName, const vector<Warrior>& warriors) {
    for (size_t i = 0; i != warriors.size(); ++i) {
        if (warriors[i].getName() == warriorName) {
            return i;
        }
    }
    return warriors.size();
} // end of check()

/*
insertWarrior() takes the name, and strength, creates a new warrior and adds it to warriors vector
*/
void insertWarrior(const string& name, const string& weaponName,int strength, vector<Warrior>& warriors) {
    size_t position = check(name, warriors);
    // checks if the warrior is already in the vector 
    if (position == warriors.size()) {
        Warrior warrior (name, weaponName, strength);
        warriors.push_back(warrior);
    } else {
        // display an error message if already in the vector
        cout << "Error: Same warrior name already exits." << endl;
    }
} // end of insertWarrior()

// operator<< is a friend function for Weapon class that outputs weapon's name and strength
ostream& operator<<(ostream& output, const Warrior::Weapon& weapon) {
    output << ", weapon: " <<  weapon.weaponName << ", " << weapon.strength << endl;
    return output;
}

// operator<< is a friend function for Warrior class that outputs warrior's name and calls the weapon's operator<< function
ostream& operator<<(ostream& output, const Warrior& warrior) {
  output << "Warrior: " << warrior.warriorName << warrior.weapon;
  return output;
}