#pragma once
#include"Enumerators.h" // include file with enums 
#include<iostream>

using std::ostream;
using std::istream;

class Card
{
private:
	rank cardRank; 
	suit cardSuit;
	char id[25]; // declare unique card id

public:
	Card();  // no need of " big 6 " because no dynamic mermory is used

	void setCardRank(rank newCardRank);  // set value for card rank
	rank getCardRank()const;

	void setCardSuit(suit newCardSuit); // set value for suit
	suit getCardSuit()const;

	void setId(); // set unique id for each card
	const char* getId()const;

	void changeId(const char* other); // change card id, this function is used to add deck id to card id
	                                  
	friend ostream& operator<<(ostream& out, const Card& other); // output operator
	friend istream& operator>>(istream& in, Card& other); // input operator
};


