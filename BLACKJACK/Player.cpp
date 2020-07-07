#include "stdafx.h"
#include "Player.h"
#include<iostream>

using std::cin;
using std::cout;
using std::endl;

int playerPoints = 0, dealerPoints = 0; // global variables which are used to track player and dealer points

void Player::copy(const Player & other) // coping another player data to the current player
{
	setName(other.name);
	setAge(other.age);
	setWins(other.wins);
	setWinRate(other.winRate);
	setCurrentPoints(other.currentPoints);
}

void Player::destroy()
{
	delete[] this->name;
}

Player::Player():name(nullptr) // name must point nullptre to make sure there is no heap corruption
{                              // default constructor
	setName("Default Name");
	setAge(18);
	setWins(0);
	setWinRate(0.0);
	setCurrentPoints(0);
}

Player::Player(const Player & other) // copy constructor
{
	this->copy(other);
}

Player & Player::operator=(const Player & other) // redifine operator =
{
	if (this != &other)
	{
		this->destroy();
		this->copy(other);
	}

	return *this;
}

Player::~Player() // destructor
{
	this->destroy();
}

Player::Player(const char * newName, int newAge, int newWins, 
		       double newWinRate, int newCurrentPoints)  // constructor
			  :name(nullptr)  // again make sure name is pointing nullptr
{
	setName(newName);
	setAge(newAge);
	setWins(newWins);
	setWinRate(newWinRate);
	setCurrentPoints(newCurrentPoints);
}

Player::Player(const char * newName, int newWins, double newWinRate)
{                              // constructor for the players from which the user can choose
	setName(newName);
	setAge(18);
	setWins(newWins);
	setWinRate(newWinRate);
	setCurrentPoints(0);
}

void Player::setName(const char * newName)
{
	if (newName != NULL) // if newName is empty there will be no point of deleting and rewrting the memory
	{
		delete[] this->name;
		this->name = new char[strlen(newName) + 1];
		strcpy_s(this->name, strlen(newName) + 1, newName);
	}
}

const char * Player::getName() const
{
	return this->name;
}

void Player::setAge(int newAge) 
{
	this->age = newAge;
}

int Player::getAge() const
{
	return this->age;
}

void Player::setWins(int newWins)
{
	this->wins = newWins;
}

int Player::getWins() const
{
	return this->wins;
}

void Player::setWinRate(double newWinRate)
{
	this->winRate = newWinRate;
}

double Player::getWinRate() const
{
	return this->winRate;
}

void Player::setCurrentPoints(int newCurrentPoints)
{
	this->currentPoints = newCurrentPoints;
}

int Player::getCurrentPoints() const
{
	return this->currentPoints;
}

void Player::play() // the game function
{
	int deckSize; // declare deck size that user wants
	char choice[4], customDeckId[10]; // choice shows if the player wants to add new id which is declared as
	bool playerChoice = false, dealer = false;                                       // customDeckId
	// playerChoice is used in user options and dealer is used as a flag
	cout << "You will play as " << getName() << ". Choose the size of the deck: " << endl;
	cout << "$ ";
	cin >> deckSize; // user inputs the deck size, he wants to create

	Deck deckche(deckSize); // create a deck with only size and the id is automatically "Custom"

	cout << "Do you want to enter a custom deck id?(yes/no) " << endl;
	cout << "$ ";

	cin >> choice; // user inputs if he wants to create a new Id

	if (strcmp(choice, "yes") == 0) // compares if the player choice is equal to yes
	{
		cout << "Enter deck id: " << endl;
		cout << "$ ";

		cin >> customDeckId; // user inputs the new id 

		deckche.playWithCustomId(customDeckId); // new id replaces the old id
	}

	Card variable; // declaring a variable card which we are going to use to save the value the draw returns
	deckche.shuffle(); // shuffle the deck so the cards order is completly random

	cout << "Start!" << endl;
	
	variable = deckche.draw(); // assign the drawn card
	playerPoints = getRankPoints(variable, playerPoints, dealer); // assign player points up to the moment

	if (playerPoints == 11 || playerPoints == 1) // if the card is Ace a messege will appear and ask the user
	{                                            // if he wants to calculate it as 1 or 11 points and if this 
		deckche.showRank(variable);              // happens than the cards rank and suit will display again
		cout << " ";
		deckche.showSuit(variable);
	}

	cout << "  (Point: " << playerPoints << ")" << endl; // displays the current player points

	while (playerChoice == false)
	{
		if (deckche.isEmpty() == true) // covers the case if all the cards are drown
		{
			cout << "You cant draw more cards! You drew every card!" << endl;
			break;
		}

		char choice[16]; // declare user choice
		int pointsToCheck; //declare a variable which will be used for verification

		cout << "Hit / Stand / Probability " << endl;
		cout << "$ ";

		cin >> choice; // input user choice

		if (strcmp(choice, "Stand") == 0) // compare choice to user input
		{
			playerChoice = true; // if the user chooses to Stand the flag turns true and the loop stops
		}
		if (strcmp(choice, "Hit") == 0)
		{
			deckche.outputPlayerCards(); // displays all the drawn cards

			pointsToCheck = playerPoints; // assign player points to the variable
			variable = deckche.draw(); // draws a card and assigns its value to variable

			playerPoints = getRankPoints(variable, playerPoints, dealer); // updates player points
			                                                              // to be accurate for the dawn cards
			if (playerPoints - pointsToCheck == 11 || playerPoints - pointsToCheck == 1)
			{  // checks is the card is Ace and if it is, displays it again
				deckche.showRank(variable);
				cout << " ";
				deckche.showSuit(variable);
			}

			cout << "  (Points:  " << playerPoints << ")" << endl; // displays current player points
		}
		if (strcmp(choice, "Probability") == 0)
		{
			cout << deckche.probability(playerPoints) << endl; // displays the propability of drawing a card with
		}                                                      // value that rounds up to 21

		if (playerPoints >= 21)
		{
			playerChoice = true; // if player points are more or equal to 21 the the loop stops
		}
	}

	if (playerPoints <= 21) // dealer draws cards only if the players points are less than 21 and 
	{                       // hanst lost the game already
		dealer = true; // this flag is used when an Ace is drawn from the dealer it automatically gains points

		int outputCheck = 0;

		while (dealerPoints < 17 && dealerPoints <= playerPoints)
		{
			if (outputCheck == 0)
			{
				cout << "The dealers draw: ";

				outputCheck++;
			}
			if (deckche.isEmpty() == true)
			{
				cout << "No more cards!" << endl;
				break;
			}
			else
			{
				dealerPoints = getRankPoints(deckche.draw(), dealerPoints, dealer);
				// if 21 - dealerPoints < 11 , Ace gains only 1 point, if the difference is bigger or even
				cout << " ";                   // Ace gains 11 points

				if (dealerPoints >= 17 || dealerPoints > playerPoints)
				{ // if this case is satisfied the loop will stop and thats why the program displays 
					cout << " (Points:  " << dealerPoints << ")" << endl; // the current points
				}
			}
		}
		if (dealerPoints <= 21) // if player and dealer both have less or equal to 21 points
		{                       // deals with different cases
			if (playerPoints > dealerPoints)
			{
				cout << getName() << " is the winner!" << endl; // player wins
			}
			else if (playerPoints < dealerPoints)
			{
				cout << "You lose!" << endl; // player loses
			}
			else
			{
				cout << "Parity!" << endl; // equality
			}

		}
		else
		{
			cout << getName() << " is the winner!" << endl; // player wins
		}
	}
	else
	{
		cout << "You lose!" << endl; // player loses
	}
}

int Player::getRankPoints(Card other, int points, bool check)
{                              // function returns points from the drown card
	switch (other.getCardRank())
	{
	case 1:
	{
		if (check == false) // this condition is valid that mean that it is the player turn
		{                  // therefore he must choose his Ace points alone and not automatically
			int choice;

			cout << endl;
			cout << "Do you want 1 or 11 points? ";

			cin >> choice;

			if (choice == 1)
			{
				points += 1;
			}
			if (choice == 11)
			{
				points += 11;
			}
		}
		else // this means it is the dealers turn
		{
			if (21 - points >= 11)
			{
				points += 11;
			}
			else
			{
				points += 1;
			}
		}
		break;
	}
	case 2:
	{
		points += 2;
		break;
	}
	case 3:
	{
		points += 3;
		break;
	}
	case 4:
	{
		points += 4;
		break;
	}
	case 5:
	{
		points += 5;
		break;
	}
	case 6:
	{
		points += 6;
		break;
	}
	case 7:
	{
		points += 7;
		break;
	}
	case 8:
	{
		points += 8;
		break;
	}
	case 9:
	{
		points += 9;
		break;
	}
	case 10:
	{
		points += 10;
		break;
	}
	case 11:
	{
		points += 10;
		break;
	}
	case 12:
	{
		points += 10;
		break;
	}
	case 13:
	{
		points += 10;
		break;
	}

	}

	return points; // return the points
}

void Player::printPlayer() // displays the player choices in the beging of the program form witch
{                          // the user chooses
	std::cout << getName() << " " << getWins() << " " << getWinRate() << std::endl;
}

ostream & operator<<(ostream & out, const Player & other) // operator for exit
{
	out << "Name: " << other.name << endl
		<< "Age: " << other.age << endl
		<< "Wins: " << other.wins << endl
		<< "Win rate: " << other.winRate << endl
		<< "Current points: " << other.currentPoints << endl;

	return out;
}

istream & operator>>(istream & in, Player & other) // input operator
{
	bool capitalFirst = false, capitalSecond = false, condition = false;
	// these are flags to check if the name is correctly entered
	while (condition == false) // condition is true only if the other two flags are true as well
	{
		capitalFirst = false; // each time the loop goes flags value is set to false, because each time
		capitalSecond = false; // a the user enters a new name

		char newName[128];

		cout << "Please write your name again: ";
		in.sync();
		in.getline(newName, 128); // user inputs the player name
		other.setName(newName);
		

		for (unsigned int i = 0; i < strlen(other.name); i++)
		{
			if (other.name[0] >= 'A' && other.name[0] <= 'Z') // verification if the first letter from the first 
			{                                                 // name is capital letter
				capitalFirst = true;
			}
			if (other.name[i] == ' ') // searches for space between the names
			{
				if (other.name[i + 1] >= 'A' && other.name[i + 1] <= 'Z') // verification if the first word from 
				{                                                         // the second name is capital letter
					capitalSecond = true;

					if (capitalFirst == true && capitalSecond == true) // if all the conditions are true
					{
						condition = true; // flag is true and loop stops
						break;
					}
				}
			}
		}

		if (capitalFirst == false && capitalSecond == false) // all the different cases
		{
			cout << "Wrong input! You have to enter two nameñ as if each one starts with capital letter and there is space between them!" << endl;
		}
		if (capitalFirst == true && capitalSecond == false)
		{
			cout << "Wrong input! There is no space between the names or the second one doesnt start with cappital letter!" << endl;
		}
		if (capitalFirst == false && capitalSecond == true)
		{
			cout << "Wrong input! The first name doesnt star with cappital letter!" << endl;
		}
	}

	bool ageCheck = false; // flag is false

	while (ageCheck == false)
	{
		cout << "Age:(must be between 18 and 90 years) ";
		in >> other.age;

		if (other.age >= 18 && other.age <= 90)
		{
			ageCheck = true; // if the condition is satisfied, flag is true and loop stops
		}
	}

	cout << "Wins: ";
	in >> other.wins;

	cout << "Win Rate: ";
	in >> other.winRate;

	cout << "Current Points: ";
	in >> other.currentPoints;

	return in;
	
}
