/*
Title: hw04 - Classes, pointers and association
Author: Anik Barua
Version: 1.0
Date: 02-24-2022

Description: This program is an updated version of the warrior game. Now the world is filled
with not only warriors but also nobles. Nobles can hire and fire warriors and battle with
other nobles with their army. Nobles will lose if they don't have warriors to defend them
so nobles winning depends on the warriors strengths.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Warrior Class
class Warrior
{
    //friend function operator<< for warrior class
    friend ostream& operator<<(ostream& output, const Warrior* const warrior);

public:
    Warrior(const string& name, double strength) : name(name), strength(strength), hireStatus(false) {}
    //hire status is false in constructor i.e. available for hire

    //returns warrior name
    const string& getName() const
    {
        return name;
    }

    //returns warrior strength
    double getStrength() const
    {
        return strength;
    }

    //sets warrior strength
    void setStrength(double strength)
    {
        this->strength = strength;
    }

    //returns warrior hire status
    bool ishired() const
    {
        return hireStatus;
    }

    //sets warrior hire status
    void setHireStatus(bool hireStatus)
    {
        this->hireStatus = hireStatus;
    }

private:
    string name;
    double strength;
    bool hireStatus;
};

//Noble Class
class Noble
{
    //friend function operator<< for noble class
    friend ostream& operator<<(ostream& output, const Noble& noble);

public:
    Noble(const string& name) : name(name), isAlive(true) {}

    //returns Noble name
    const string& getName() const
    {
        return name;
    }

    //Hire's warrior in Noble's army
    bool hire(Warrior& warrior)
    {
        if(isAlive == true) // Checks if the Noble is alive
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
    bool fire(Warrior& warrior)
    {
        if(isAlive == true) // Checks if the Noble is alive 
        {
            for (size_t i = 0; i < army.size(); ++i)
            {
                if (army[i] == &warrior) // checks if the warrior is in the current army by checking the same memory address
                {
                    warrior.setHireStatus(false); // Now warrior is available for hire
                    cout << "You don't work for me anymore " << warrior.getName() << "! -- " << name << "." << endl;
                    for(size_t index = i; index < army.size() - 1; ++index) {
                        army[index] = army[index+1]; //moving the warrior location to the end of the vector
                    }
                    army.pop_back(); //removing it from the vector
                    return true;
                }
            }
        }
        return false; // Either the noble is dead or the warrior is not in his army
    }

    //returns total army strength
    double getArmyStrength() const 
    {
        double total = 0;
        for (size_t i = 0; i < army.size(); ++i)
        {
            total += army[i]->getStrength();
        }
        return total; // returns stength of the noble (army strength)
    }

    //changes strength of each warrior based on the ratio of opponent army
    void changeStrength(double ratio)
    {
        for (size_t i = 0; i < army.size(); ++i)
        {
            double strength = army[i]->getStrength()-(army[i]->getStrength()*ratio);
            army[i]->setStrength(strength);
        }
    }

    //changes strength of each warrior to zero
    void changeStrengthtoZero()
    {
        isAlive = false; //Noble is now dead
        for (size_t i = 0; i < army.size(); ++i)
        {
            army[i]->setStrength(0);
        }
    }

    /*
    battle() method between two nobles. It displays one line to says who is fighting whom 
    and a second line to report the results.
    */
    void battle(Noble& noble2)
    {
        cout << name << " battles " << noble2.getName() << endl;
        // if noble 1 strength is greater than noble 2's strength
        if (getArmyStrength() > noble2.getArmyStrength())
        {
            // checks if both participants are alive
            if (isAlive == true && noble2.isAlive == true)
            {
                double ratio = noble2.getArmyStrength()/getArmyStrength();
                changeStrength(ratio);
                noble2.changeStrengthtoZero(); // noble 2 is dead
                cout << name << " defeats " << noble2.getName() << endl;
            }
            else
            {
                // one of the participants is dead and the other is alive
                if (isAlive == false)
                {
                    cout << "He's dead, " << noble2.getName() << endl;
                }
                else
                {
                    cout << "He's dead, " << name << endl;
                }
            }
        }
        // if noble 1 strength is less than noble 2's strength
        else if (getArmyStrength() < noble2.getArmyStrength())
        {
            // checks if both participants are alive
            if (isAlive == true && noble2.isAlive == true)
            {
                double ratio = getArmyStrength()/noble2.getArmyStrength();
                noble2.changeStrength(ratio);
                changeStrengthtoZero(); // noble 1 is dead
                cout << noble2.getName() << " defeats " << name << endl;
            }
            else
            {
                // one of the participants is dead and the other one is alive
                if (isAlive == false)
                {
                    cout << "He's dead, " << noble2.getName() << endl;
                }
                else
                {
                    cout << "He's dead, " << name << endl;
                }
            }
        }
        // if noble 1 strength is same as noble 2's strength
        else if (getArmyStrength() == noble2.getArmyStrength())
        {
            // checks if both participants are alive
            if (isAlive == true && noble2.isAlive == true)
            {
                changeStrengthtoZero(); // noble 1 is dead
                noble2.changeStrengthtoZero(); // noble 2 is dead
                cout << "Mutual Annihilation: " << name << " and " << noble2.getName() << " die at each other's hands" << endl;
            }
            else
            {
                // both noble's are dead
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
        }
    }

private:
    string name; // name of the noble
    vector<Warrior*> army; // Noble's army is a vector of pointers to warriors
    bool isAlive; // to check if noble is alive or dead
};

int main()
{
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
	
    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
    art.fire(cheetah);
    cout << art << endl;
	
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
    return 0;
} // end of main
 
// operator<< is a friend function for Warrior class that outputs Warrior's name and strength
ostream& operator<<(ostream& output, const Warrior* const warrior)
{
    output << "\t" << warrior->name << ": " << warrior->strength;
    return output;
}

// operator<< is a friend function for Noble class that outputs Noble's name, size and calls the warrior's operator<< function
ostream& operator<<(ostream& output, const Noble& noble)
{   
    output << noble.name << " has an army of " << noble.army.size() << endl;
    for (size_t i = 0; i != noble.army.size(); ++i)
    {
        output << noble.army[i];
        if (i == noble.army.size() - 2)
        {
            output << "\n";
        }
    }
    return output;
}