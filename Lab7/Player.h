#ifndef PLAYER_H
#define PLAYER_H

typedef char gameboard[10][10];

class Player
{
	float cumulativeHits;
	float cumulativeMisses;

public:
	//Two 10 x 10 arrays are generated for both the player and the computer
	gameboard guessArray;
	gameboard shipArray;

	//Class constructor
	Player();

	void SetNumOfHits(int hits);
	//Pre:The game has terminated and the number of hits has been passed as an argument
	//Post The total number of hits during program execution is updated

	void SetNumOfMisses(int misses);
	//Pre: The game has terminated and the number of misses has been passed as an argument
	//Post: The total number of misses during program execution is updated

	float GetHits();
	//Pre: None - initialized to zero
	//Post: The number hits on enemy ships is printed to the console

	float GetMisses();
	//Pre: None - initialized to zero
	//Post: The number of missed shots is printed to the console

	float PrintAccuracy();
	//Pre: None - both cumulative hits and misses are initialized to zero.
	//Post: Prints the ratio of his to shots taken for both the user and the computer.

};

#endif