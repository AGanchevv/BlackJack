#pragma once
#include"Deck.h"
#include<iostream>

using std::ostream;
using std::istream;

class Player
{
private:
	char* name; // using dynamic memory for the player name
	int age;
	int wins;
	double winRate;
	int currentPoints;

	void copy(const Player& other); // creating bix six, because using dynamic memory
	void destroy();

public:

	Player();
	Player(const Player& other);
	Player& operator=(const Player& other);
	~Player();

	Player(const char* newName, int newAge, int newWins, double newWinRate, int newCurrentPoints);
	Player(const char* newName, int newWins, double newWinRate);

	void setName(const char* newName); // seters and geters
	const char* getName()const;

	void setAge(int newAge);
	int getAge()const;

	void setWins(int newWins);
	int getWins()const;

	void setWinRate(double newWinRate);
	double getWinRate()const;

	void setCurrentPoints(int newCurrentPoints);
	int getCurrentPoints()const;

	void play(); // function for playing the game

	int getRankPoints(Card other, int points, bool check); // taking the points which respond to the drown card

	void printPlayer(); // displays the players from which the user can choose
	                    // each player is on a new line
	friend ostream& operator<<(ostream& out, const Player& other);
	friend istream& operator>>(istream& in, Player& other);
};

