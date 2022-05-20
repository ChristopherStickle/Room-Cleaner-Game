This is a small text-based game in C. 
The game was designed for OOP, which C does not support naturally. 
Thus this lab was designed to simultaneously teach the specifics of the C language, and the difference between structured programming and OOP.


Game Challenge Description and requirements:

http://cs.oswego.edu/~alex/teaching/csc241/hw/project.pdf
A few changes were made from the description above:
There will be no names and descriptions for anything in the game, only numbers (as in room number 0)
When the game starts, it takes from stdin input, rather than an XML, in the following format:

n (integer, the number of rooms, 1 < n < 100)
The next n lines are the following:
state north south east west (five integers, signifying the cleanliness of the room and the numbers of the respective neighbors.
State can be 0 for clean, 1 for half-dirty, 2 for dirty. -1 signifies no neighbor. Numbering of the rooms starts at 0)

The next line is:
m (integer, the number of creatures, 1 < m < 100)
The next m lines are:
creatureType location (two integers; creatureType is 0 for the PC, 1 for an animal, 2 for an NPC. 
Location is the number of the room the creature is in. Numbering starts at 0)
The input will be well-formed according to the above description and the game specification 
(i.e., you should not worry about checking for errors in the input such as putting an animal in a dirty room from the start and the like).

The game will continue to read game commands from stdin until:
1.) 'exit' is read. Upon which the game exits and the score is displayed.
2.) The player wins or loses by earning a respect value > 80 or <= 0 respectively.

Challenge Condition: The only globals allowed to use are: up to three global pointers and a global int for the respect value.
