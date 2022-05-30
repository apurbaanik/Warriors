/*
    Title: hw07: Inheritance
    Author: Anik Barua
    Version: 1.0
    Date: 04-07-2022

    Description: This program is an updated version of our game of Warriors and Nobles. Now we will 
    have more than one type of Noble - Lord and PersonWithStrengthToFight. In fact warriors aren't 
    the only people they can hire for fighting. There will be Wizards as well and two kind of 
    warriors - Archer and Swordsman, and all are known as protectors. Here Lord is same as our 
    Noble from last program who can hire warriors to fight for him, but PersonWithStrengthToFight
    type Noble only fight by himself with his strength. Each protectors defends their Noble in 
    different way and we have to implement it using inheritance.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Forward class declaration
class Lord;

//Protector Class
class Protector {
    //friend function operator<< for Protector class
    friend ostream& operator<<(ostream& output, const Protector& protector);
public:
    Protector(const string& name, double strength); //constructor
    virtual void defend() const = 0; //used by the battle method and overidden for each warrior
    bool runaway(); //runaway method for warrior
    bool isAlive() const; //returns if protector is alive
    bool isHired() const; //returns protector hire status
    const string& getName() const; //returns protector name
    const string& getLordName() const; //returns protector Lord's name
    void setNoble(Lord* lord); //sets the lord for protector's noble
    double getStrength() const; //returns protector strength
    void setStrength(double newStrength); //sets protector strength
private:
    string name;
    double strength;
	Lord* myLord; // a pointer to his Load
};

//Wizard
class Wizard : public Protector { //Inherits from protector class
public:
    Wizard(const string& name, double strength);
    void defend() const; //overrides the defend() virtual method
};

//Warrior class 
class Warrior : public Protector { //Inherits from protector class
public:
    Warrior(const string& name, double strength); //constructor
};

//Archer
class Archer : public Warrior { //Inherits from warrior class
public:
    Archer(const string& name, double strength); //constructor
    void defend() const; //overrides the defend() virtual method
};

//Swordsman
class Swordsman : public Warrior { //Inherits from warrior class
public:
    Swordsman(const string& name, double strength); //constructor
    void defend() const; //overrides the defend() virtual method
}; 

//Noble class
class Noble {
    //friend function operator<< for noble class
    friend ostream& operator<<(ostream& output, const Noble& noble);
public:
    Noble(const string& name); //constructor
    const string& getName() const; //returns Noble name
    void battle(Noble& noble2); //battle between between two nobles
    bool getAliveStatus() const; //returns Noble's alive status
    void setAliveStatus(bool status); //sets Noble's alive status
    virtual void defend() const = 0; //virtual defend method for each noble
    virtual double getStrength() const = 0; //virtual method that returns Noble's strength
    virtual void changeStrength(double ratio) = 0; //virtual method that changes strength based on the ratio 
    virtual void changeStrengthToZero() = 0; //virtual method that changes strength to zero
    virtual ostream& display(ostream& output) const = 0; //virtual display method used by the output operator<< 
private:
    string name;
    bool isAlive;
};

//Lord
class Lord : public Noble { //Inherits from Noble class
public:
    Lord(const string& name); //constructor
    void defend() const; //overrides the defend method specific to lord
    bool hires(Protector& protector); //Hire's protector in Lords's army
    bool fires(Protector& protector); //Fire's a protector from the noble's army
    double getStrength() const; //overidden method that return the strength of the army
    void changeStrengthToZero(); //overidden method that return the strength of the army
    void changeStrength(double ratio); //overidden method that changes strength of each protector based on the ratio
    bool removeFromArmy(Protector* protector); //Removes protector from the army (used by fires and protector's runaway method)
    ostream& display(ostream& output) const; //overidden method that displays the loard information along with his protectors
private:
    vector<Protector*> army; //Lords's army is a vector of pointers to protectors
};

//PersonWithStrengthToFight 
class PersonWithStrengthToFight : public Noble {
public:
    PersonWithStrengthToFight(const string& name, double strength); //constructor
    void defend() const; //overrides the defend method specific to PersonWithStrengthToFight
    double getStrength() const; //overidden method that returns the strength of the Noble
    void changeStrength(double ratio); //overidden method that changes strength based on the ratio
    void changeStrengthToZero(); //overidden method that changes the strength to zero
    ostream& display(ostream& output) const; //overidden method that displays the noble information 
private:
    double strength;
};

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    joe.battle(randy);	
    joe.battle(sam);	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    janet.battle(barclay);	
    janet.hires(samantha);	
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);	
    sam.battle(barclay);	
    joe.battle(barclay);
}

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

//Wizard class
//Inherits from protector class, so calling Protector constructor to initialize the name and strength
Wizard::Wizard(const string& name, double strength) : Protector(name, strength) {}

//overrides the defend() virtual method
void Wizard::defend() const { 
    cout << "POOF!" << endl; 
};

//Warrior class
//Inherits from protector class, so calling Protector constructor to initialize the name and strength
Warrior::Warrior(const string& name, double strength) : Protector(name, strength) {}

//Archer class
//Inherits from warrior class, so calling warrior constructor to initialize the name and strength
Archer::Archer(const string& name, double strength) : Warrior(name, strength) {}
void Archer::defend() const {
    cout << "TWANG!  " << this->getName() << " says: Take that in the name of my lord, " << this->getLordName() << endl;
};

//Swordsman
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
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
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