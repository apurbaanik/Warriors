/*
Title: hw05 - dynamic memory
Author: Anik Barua
Version: 2.0
Date: 03-15-2022

Description: This program is an updated version of the warrior game. Now we will be using dynamic 
memory to allocate our warriors and nobles. The main differences are: each time a warrior or a 
noble is defined, we will create it on the heap, and we will keep track of the nobles in a vector 
of pointers to nobles, and warriors using a vector of pointers to warriors. Everying else stays 
the same from the last version of the game.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
 
// Warrior Class
class Warrior {
    //friend function operator<< for warrior class
    friend ostream& operator<<(ostream& output, const Warrior& warrior);

    public:
    Warrior(const string& name, double strength): name(name), strength(strength), hireStatus(false) {}
    //hire status is false in constructor i.e. available for hire

    //returns warrior name
    const string& getName() const {
        return name;
    }

    //returns warrior strength
    double getStrength() const {
        return strength;
    }

    //sets warrior strength
    void setStrength(double strength) {
        this->strength = strength;
    }

    //returns warrior hire status
    bool ishired() const {
        return hireStatus;
    }

    //sets warrior hire status
    void setHireStatus(bool hireStatus) {
        this->hireStatus = hireStatus;
    }

    private:
    string name;
    double strength;
    bool hireStatus;
};

//Noble Class
class Noble {
    //friend function operator<< for noble class
    friend ostream& operator<<(ostream& output, const Noble& noble);

    public:
        Noble(const string& name): name(name), isAlive(true) {}

    //returns Noble name
    const string& getName() const {
        return name;
    }

    //Hire's warrior in Noble's army
    bool hire(Warrior& warrior) {
        if (isAlive == true) // Checks if the Noble is alive
        {
            if (warrior.ishired() == false) // checks if available for hire
            {
                warrior.setHireStatus(true); // Now he is hired
                army.push_back(&warrior); // warrior is in the army 
                return true;
            }
        }
        return false; // Either the noble is dead or the warrior is not available for hire
    }

    //To fire a warrior from the noble's army
    bool fire(Warrior& warrior) {
        if (isAlive == true && warrior.ishired() == true) // Checks if the Noble is alive and the warrior is already hired
        {
            for (size_t i = 0; i < army.size(); ++i) 
            {
                if (army[i] == &warrior) // checks if the warrior is in the current army by checking the same memory address
                {
                    warrior.setHireStatus(false); // Now warrior is available for hire
                    cout << "You don't work for me anymore " << warrior.getName() << "! -- " << name << "." << endl;
                    for (size_t index = i; index < army.size() - 1; ++index) 
                    {
                        army[index] = army[index + 1]; //moving the warrior location to the end of the vector
                    }
                    army.pop_back(); //removing it from the vector
                    return true;
                }
            }
        }
        return false; // Either the noble is dead or the warrior is not in his army
    }

    //returns total army strength
    double getArmyStrength() const {
        double total = 0;
        for (size_t i = 0; i < army.size(); ++i) {
            total += army[i]->getStrength();
        }
        return total; // returns stength of the noble (army strength)
    }

    //changes strength of each warrior based on the ratio of opponent army
    void changeStrength(double ratio) {
        for (size_t i = 0; i < army.size(); ++i) {
            double strength = army[i]->getStrength() - (army[i]->getStrength() * ratio);
            army[i]->setStrength(strength);
        }
    }

    //changes strength of each warrior to zero
    void changeStrengthtoZero() {
        isAlive = false; //Noble is now dead
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->setStrength(0);
        }
    }

    /*
    battle() method between two nobles. It displays one line to says who is fighting whom 
    and a second line to report the results.
    */
    void battle(Noble& noble2) {
        cout << name << " battles " << noble2.getName() << endl;
        if (isAlive == false && noble2.isAlive == false) {
            // if both noble's are dead
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if(isAlive == false) {
            // if noble1 is dead and noble2 is alive
            cout << "He's dead, " << noble2.getName() << endl;
        } else if(noble2.isAlive == false) {
            // if noble2 is dead and noble1 is alive
            cout << "He's dead, " << name << endl;
        } else if(isAlive == true && noble2.isAlive == true){
            // if both participants are alive
            if (getArmyStrength() > noble2.getArmyStrength()) {
                // if noble 1 strength is greater than noble 2's strength
                double ratio = noble2.getArmyStrength()/getArmyStrength();
                changeStrength(ratio);
                noble2.changeStrengthtoZero(); // noble 2 is dead
                cout << name << " defeats " << noble2.getName() << endl;
            } else if (getArmyStrength() < noble2.getArmyStrength()) {     
                // if noble 1 strength is less than noble 2's strength  
                double ratio = getArmyStrength()/noble2.getArmyStrength();
                noble2.changeStrength(ratio);
                changeStrengthtoZero(); // noble 1 is dead
                cout << noble2.getName() << " defeats " << name << endl; 
            } else if (getArmyStrength() == noble2.getArmyStrength()) {
                // if noble 1 strength is same as noble 2's strength      
                changeStrengthtoZero(); // noble 1 is dead
                noble2.changeStrengthtoZero(); // noble 2 is dead
                cout << "Mutual Annihilation: " << name << " and " << noble2.getName() << " die at each other's hands" << endl;
            }
        }
    }

    private:
    string name; // name of the noble
    vector <Warrior*> army; // Noble's army is a vector of pointers to warriors
    bool isAlive; // to check if noble is alive or dead
};

// Function Prototypes
size_t findWarrior(const string& warriorName, const vector <Warrior*>& warriors);
size_t findNoble(const string& nobleName, const vector <Noble*>& nobles);

int main() {
    ifstream reader("nobleWarriors.txt"); // reading the "nobleWarriors.txt" file
    if (!reader) {
        cerr << "Failed to open nobleWarriors.txt file";
        exit(1);
    }

    //Variables used to read from the file
    string command, nobleName, warriorName;
    double warriorStrength;
    string noble1, warrior1;
    bool checkWarrior;
    vector <Noble*> nobles; // a vector of pointers to nobles
    vector <Warrior*> warriors; // a vector of pointers to warriors

    while (reader >> command) {
        if (command == "Noble") { // Noble Command
            reader >> nobleName;
            size_t position1 = findNoble(nobleName, nobles);
            if(position1 == nobles.size()){
                // Not on the vector
                nobles.push_back(new Noble(nobleName)); // add it to the vector - created on the heap
            } else {
                // Already in the vector
                cout << "Error: Noble with a given name already exists" << endl;
            }
        } else if (command == "Warrior") { // Warrior Command
            reader >> warriorName >> warriorStrength;
            size_t position2 = findWarrior(warriorName, warriors);
            if(position2 == warriors.size()){
                // Not in vector
                warriors.push_back(new Warrior(warriorName, warriorStrength)); // add it to the vector - created on the heap
            } else {
                // Already in vector
                 cout << "Error: Warrior with a given name already exists" << endl;
            }
        } else if (command == "Hire") { // Hire Command
            reader >> noble1 >> warrior1;
            bool check, found = false;
            size_t noblePosition = findNoble(noble1, nobles);
            size_t warriorPosition = findWarrior(warrior1, warriors);
            if(noblePosition != nobles.size() && warriorPosition != warriors.size()){
                found = true; // found both warrior and noble
                check = nobles[noblePosition]->hire(*warriors[warriorPosition]); // noble hires the warrior (check returns true if hiring is successful)
                if (check == false) {
                    // check is false if the the noble is dead 
                    cout << "Attempt to hire " << warrior1 << " by " << noble1 << " failed!" << endl;
                }
            }
            if (found == false) {
                // if found is false then the warrior doesn't exist in the army
                cout << "Attempting to hire using unknown warrior: " << warrior1 << endl;
            }
        } else if (command == "Status") { // Status Command
            cout << "Status\n======\nNobles:" << endl;
            if(nobles.size() > 0){
                for (size_t i = 0; i < nobles.size(); ++i) {
                    cout << *nobles[i]; // uses the output operator for the nobles class
                }
            } else {
                // if nobles vector is empty
                cout << "NONE" << endl;
            }
            bool check = false;
            cout << "\nUnemployed Warriors:" << endl;
            for (size_t i = 0; i < warriors.size(); ++i) {
                if(warriors[i]->ishired() == false) {
                    cout << *warriors[i] << endl; // uses the output operator for the nobles class
                    check = true;
                }
            }
            if(check == false) {
                cout << "NONE" << endl;
            }
        } else if (command == "Fire") { // Fire Command
            reader >> noble1 >> warrior1;
            bool check, found = false;
            size_t noblePosition = findNoble(noble1, nobles);
            size_t warriorPosition = findWarrior(warrior1, warriors);
            if(noblePosition != nobles.size() && warriorPosition != warriors.size()){
                found = true; // found both warrior and noble
                check = nobles[noblePosition]->fire(*warriors[warriorPosition]); // noble fires the warrior (check returns true if firing is successful)
                if (check == false) {
                    // check is false if the the noble is dead 
                    cout << "Attempt to fire " << warrior1 << " by " << noble1 << " failed!" << endl;
                }
            }
            if (found == false) {
                // if found is false then the warrior doesn't exist in the army
                cout << "Attempting to fire using unknown warrior: " << warrior1 << endl;
            }
        } else if (command == "Battle") { // Battle Command
            string noble1, noble2;
            reader >> noble1 >> noble2;
            size_t noble1Position = findNoble(noble1, nobles);
            size_t noble2Position = findNoble(noble2, nobles);
            if(noble1Position != nobles.size() && noble2Position != nobles.size()){
                nobles[noble1Position]->battle(*nobles[noble2Position]); // Calls the Noble's battle method
            }
            if (noble1Position == nobles.size()) {
                // if noble1 not found
                cout << "Attempting to battle with unknown Noble: " << noble1 << endl;
            }
            if (noble2Position == nobles.size()) {
                // if noble2 not found
                cout << "Attempting to battle with unknown Noble: " << noble2 << endl;
            }
        } else if (command == "Clear") { // Clear Command
            for (size_t i = 0; i < warriors.size(); ++i) {
                delete warriors[i]; // deleting the warriors from the memory
            }
            for (size_t j = 0; j < nobles.size(); ++j) {
                delete nobles[j]; // deleting the nobles from the memory
            }
            warriors.clear(); // clearing the dangling pointers of the warriors vector
            nobles.clear(); // clearing the dangling pointers of the nobles vector
        }
    }
    reader.close(); //closing the reader file
    return 0;
} // end of main

// findWarrior() function
size_t findWarrior(const string& warriorName, const vector <Warrior*>& warriors) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i]->getName() == warriorName) {
            return i;
        }
    }
    return warriors.size();
}

// findNoble() functions
size_t findNoble(const string& nobleName, const vector <Noble*>& nobles) {
    for (size_t i = 0; i < nobles.size(); ++i) {
        if (nobles[i]->getName() == nobleName) {
            return i;
        }
    }
    return nobles.size();
}

/*
operator<< is a friend function for Warrior class that outputs Warrior's name and strength
*/ 
ostream& operator<<(ostream& output, const Warrior& warrior) {
    output << "\t" << warrior.name << ": " << warrior.strength;
    return output;
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