/*
	Title: hw07: Inheritance - Separate Compilation
	Author: Anik Barua
	Version: 1.0
	Date: 04-12-2022
    
	Description: This program is an updated version of our game of Warriors and Nobles. Now we will 
    have more than one type of Noble - Lord and PersonWithStrengthToFight. In fact warriors aren't 
    the only people they can hire for fighting. There will be wizards as well and two kind of 
    warriors - Archer and Swordsman, and all are known as protectors. Here, Lord is same as our 
    Noble from last program who can hire warriors to fight for him, but PersonWithStrengthToFight
    type Noble only fights by himself with his own strength. Each protectors defends their Noble 
    in different way and implemented it using inheritance.
*/

// To run this in terminal - 
// g++ -std=c++11 hw07.cpp Protector.cpp Noble.cpp
// ./a.out

//including the header files
#include "Noble.h"
#include "Protector.h"
using namespace std;
using namespace WarriorCraft; //WarriorCraft namespace

//Main
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