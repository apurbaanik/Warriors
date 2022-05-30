/*
	Title: hw06 - Cyclic Association
	Author: Anik Barua
	Version: 1.0
	Date: 03-24-2022

	Description: This program is an updated version of the warrior game. Now we will be adding a new feature 
	where not only can warriors be fired, they can also runaway from their nobles. When a warrior runs away, 
	he has to inform his noble, which means the warrior has to know who hired him and be able to communicate 
	with him. So we need a pointer to his noble in the warrior class. 
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Forward class declaration
class Noble;

// Warrior Class
class Warrior {
	//friend function operator<< for warrior class
    friend ostream& operator<<(ostream& output, const Warrior& warrior);
public:
    Warrior(const string& name, double strength); //constructor
    const string& getName() const;  //returns warrior name
    double getStrength() const;  //returns warrior strength
    void setStrength(double strength); //sets warrior strength
	void setNoble(Noble* noble); // sets the noble for warrior's noble
    bool isHired() const; //returns warrior hire status
	bool runaway(); //runaway method for warrior
private:
    string name;
    double strength;
	Noble* myNoble; // a pointer to his noble
};

//Noble Class
class Noble {
	//friend function operator<< for noble class
    friend ostream& operator<<(ostream& output, const Noble& noble);
public:
	Noble(const string& name); //constructor
    const string& getName() const; //returns Noble name
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
    string name; // Noble's name
    vector <Warrior*> army; // Noble's army is a vector of pointers to warriors
    bool isAlive; // To check if noble is alive or dead
};

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 4);
	Warrior sky("Leia", 6);
	Warrior wizard("Merlin", 9);
	Warrior jaffa("Teal'c", 9);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	
	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(jaffa);
	art.hire(cheetah);
	art.hire(wizard);
	art.hire(sky);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(nimoy);
	

	cout << "================ Initial Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;
	cout << "===============================================\n\n";

	art.fire(cheetah);
	wizard.runaway();

	cout << endl << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
	
	cout << "\n================ Final Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;

	// Tarzan and Merlin should be unemployed
	cout << "Tarzan's Hire Status: " << boolalpha 
	     << cheetah.isHired() << endl;
	cout << "Merlin's Hire Status: " << boolalpha 
	     << wizard.isHired() << endl;
	cout << "===============================================\n\n";
}

// Warrior Class
Warrior::Warrior(const string& name, double strength): name(name), strength(strength), myNoble(nullptr) {}
//Hire status is false in constructor i.e. available for hire and myNoble is set to nullptr (not hired by any noble yet)

//returns warrior name
const string& Warrior::getName() const {
    return name;
}

//returns warrior strength
double Warrior::getStrength() const {
    return strength;
}

//sets warrior strength
void Warrior::setStrength(double newStrength) {
    strength = newStrength;
}
 
//sets noble pointer for warrior's noble
void Warrior::setNoble(Noble* noble) {
	myNoble = noble;
}

//returns warrior hire status
bool Warrior::isHired() const {
    return myNoble;
}

// runaway() calls the Noble's removeFromArmy() method to remove the warrior from his army
bool Warrior::runaway(){
	// checking if the noble exists and the noble is alive
	if(myNoble && myNoble->getAliveStatus()){
		cout << name << " flees in terror, abandoning his lord, " << myNoble->getName() << endl;
		return myNoble->removeFromArmy(this); //calls the Noble's removeFromArmy() method
	}
	return false;
}

/*
operator<< is a friend function for Warrior class that outputs Warrior's name and strength
*/ 
ostream& operator<<(ostream& output, const Warrior& warrior) {
    output << "\t" << warrior.name << ": " << warrior.strength;
    return output;
}

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