#include "Player.h"
#include <iostream>

//Constructor for Player class
Player::Player() {
	cumulativeHits = 0;
	cumulativeMisses = 0;
}

void Player::SetNumOfHits(int hits) { 
	cumulativeHits += hits;
}

void Player::SetNumOfMisses(int misses) { 
	cumulativeMisses += misses; 
}

float Player::GetHits() { 
	return cumulativeHits; 
}

float Player::GetMisses() { 
	return cumulativeMisses; 
}

float Player::PrintAccuracy() { 
	return cumulativeHits / (cumulativeHits + cumulativeMisses); 
}