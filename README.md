# Warriors
Warriors - a game of medieval times

Version 1: 
A game of medieval times warriors who likes to fight until they are dead. Each
warrior has a name and a certain amount of strength. Each time he fights, he loses some
strength. If his opponent is stronger than he is, then he loses all of his strength, in
which case he is dead, or at the very least pretty useless as a fighter. Otherwise he
loses as much strength as his opponent had. If he and his opponent had the same strength
then they are both losers. Even losers are allowed to pick a fight. It doesn't require
having any strength in order to do battle with someone else.

Version 2:
This program is a updated version of the warrior game. Now each warrior will have 
a weapon and it is created together with the warrior (inside constructor). It can only be accessed 
by the warrior class. When a Warrior's weapon loses all of its strength, the Warrior himself dies.

Version 3:
This program is an updated version of the warrior game. Now the world is filled
with not only warriors but also nobles. Nobles can hire and fire warriors and battle with
other nobles with their army. Nobles will lose if they don't have warriors to defend them
so nobles winning depends on the warriors strengths.

Version 4:
This program is an updated version of the warrior game. Now we will be using dynamic 
memory to allocate our warriors and nobles. The main differences are: each time a warrior or a 
noble is defined, we will create it on the heap, and we will keep track of the nobles in a vector 
of pointers to nobles, and warriors using a vector of pointers to warriors. Everying else stays 
the same from the last version of the game.

Version 5:
This program is an updated version of the warrior game. Now we will be adding a new feature 
where not only can warriors be fired, they can also runaway from their nobles. When a warrior runs away, 
he has to inform his noble, which means the warrior has to know who hired him and be able to communicate 
with him. So we need a pointer to his noble in the warrior class. 

Version 6:
This program is an updated version of our game of Warriors and Nobles. Now we will 
have more than one type of Noble - Lord and PersonWithStrengthToFight. In fact warriors aren't 
the only people they can hire for fighting. There will be Wizards as well and two kind of 
warriors - Archer and Swordsman, and all are known as protectors. Here Lord is same as our 
Noble from last program who can hire warriors to fight for him, but PersonWithStrengthToFight
type Noble only fight by himself with his strength. Each protectors defends their Noble in 
different way and we have to implement it using inheritance.
