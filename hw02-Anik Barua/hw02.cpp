/*
Title: Homework 02: Warriors - a game of medieval times
Author: Anik Barua
Version: 1.0
Date: 02-07-2022

Description: A game of medieval times warriors who likes to fight until they are dead. Each
warrior has a name and a certain amount of strength. Each time he fights, he loses some
strength. If his opponent is stronger than he is, then he loses all of his strength, in
which case he is dead, or at the very least pretty useless as a fighter. Otherwise he
loses as much strength as his opponent had. If he and his opponent had the same strength
then they are both losers. Even losers are allowed to pick a fight. It doesn't require
having any strength in order to do battle with someone else.
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Warrior is a struct with name and strength
struct Warrior
{
    string name;
    int strength;
};

// Prototypes
void status(const vector<Warrior> &warriors); // for status command
size_t check(const string& name, const vector<Warrior>& warriors);
void insertWarrior(const string& name, int strength, vector<Warrior>& warriors); // for warrior command
void battle(const string& warrior1,const string& warrior2, vector<Warrior>& warriors); // for battle command

// Main
int main()
{
    ifstream reader("warriors.txt"); // reading the "warriors.txt" file
    if (!reader)
    {
        cerr << "Failed to open encrypted.txt";
        exit(1);
    }

    int strength;              // reads the strength
    string line, name;         // line reads the first command, name reads the warrior name
    string warrior1, warrior2; // for battle command, reads two warriors name
    vector<Warrior> warriors;  // vector containing the warriors

    while (reader >> line)
    {
        // Warrior command
        if (line == "Warrior")
        {
            reader >> name;
            reader >> strength;
            insertWarrior(name, strength, warriors); // creates a new warrior with the specified name and strength
        }
        else if (line == "Status")
        {
            // Status command
            status(warriors); // lists all warriors, alive or dead, and their strengths
        }
        else if (line == "Battle")
        {
            // Battle command
            reader >> warrior1;
            reader >> warrior2;
            battle(warrior1, warrior2, warriors); // causes a battle to occur between two warriors
        }
    }
    reader.close();
    return 0;
} // end of main

/*
check() function takes the warrior name and the warriors vector, and returns the positon of the
warrior in the vector
*/
size_t check(const string& name, const vector<Warrior>& warriors)
{
    for (size_t i = 0; i != warriors.size(); ++i)
    {
        if (warriors[i].name == name)
        {
            return i;
        }
    }
    return warriors.size();
} // end of check()

/*
insertWarrior() takes the name, and strength, creates a new warrior and adds it to warriors vector
*/
void insertWarrior(const string& name, int strength, vector<Warrior>& warriors)
{
    size_t position = check(name, warriors);
    if (position == warriors.size()) // checks if the warrior is already in the vector
    {
        Warrior warrior;
        warrior.name = name;
        warrior.strength = strength;
        warriors.push_back(warrior);
    }
    else
    {
        // display an error message if already in the vector
        cout << "Error: Same warrior name already exits." << endl;
    }
} // end of insertWarrior()

/*
    status() function displays how many warriors are there, then displays each one with his strength
*/
void status(const vector<Warrior>& warriors)
{
    cout << "There are: " << warriors.size() << " warriors\n";
    for (size_t i = 0; i != warriors.size(); i++)
    {
        cout << "Warrior: " << warriors[i].name << ", strength: " << warriors[i].strength << endl;
    }
} // end of status()

/*
    battle() function displays one line to says who is fighting whom and a second line to report the results
*/
void battle(const string& warrior1,const string& warrior2, vector<Warrior>& warriors)
{
    size_t position1 = check(warrior1, warriors);
    size_t position2 = check(warrior2, warriors);
    // checks if one or both warriors doesn't exits
    if (position1 != warriors.size() && position2 != warriors.size())
    {
        cout << warrior1 << " battles " << warrior2 << endl;
        // if warrior 1 strength is greater than warrior 2
        if (warriors[position1].strength > warriors[position2].strength)
        {
            // checks if one of the participants is dead and the other is alive
            if (warriors[position1].strength != 0 && warriors[position2].strength != 0)
            {
                // subtracts the strength from warrior 1 to warrior 2
                warriors[position1].strength = warriors[position1].strength - warriors[position2].strength;
                warriors[position2].strength = 0; // warrior 2 is dead
                cout << warrior1 << " defeats " << warrior2 << endl;
            }
            else
            {
                // one of the participants is dead and the other is alive
                if (warriors[position1].strength == 0)
                {
                    cout << "He's dead, " << warrior2 << endl;
                }
                else
                {
                    cout << "He's dead, " << warrior1 << endl;
                }
            }
        }
        // if warrior 1 strength is less than warrior 2
        else if (warriors[position1].strength < warriors[position2].strength)
        {
            // checks if one of the participants is dead and the other is alive
            if (warriors[position1].strength != 0 && warriors[position2].strength != 0)
            {
                // subtracts the strength from warrior 2 to warrior 1
                warriors[position2].strength = warriors[position2].strength - warriors[position1].strength;
                warriors[position1].strength = 0; // warrior 1 is dead
                cout << warrior2 << " defeats " << warrior1 << endl;
            }
            else
            {
                // one of the participants is dead and the other is alive
                if (warriors[position1].strength == 0)
                {
                    cout << "He's dead, " << warrior2 << endl;
                }
                else
                {
                    cout << "He's dead, " << warrior1 << endl;
                }
            }
        }
        // if warrior 1 strength is same as warrior 2
        else if (warriors[position1].strength == warriors[position2].strength)
        {
            // checks if one of the participants is dead and the other is alive
            if (warriors[position1].strength != 0 && warriors[position2].strength != 0)
            {
                warriors[position1].strength = 0; // warrior 1 is dead
                warriors[position2].strength = 0; // warrior 2 is dead
                cout << "Mutual Annihilation: " << warrior1 << " and " << warrior2 << " die at each other's hands" << endl;
            }
            else
            {
                // both warriors are dead
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
        }
    }
    else
    {
        // if one or both of them have not been defined yet
        cout << "Error: One or both warriors doesn't exits." << endl;
    }
} // end of battle function