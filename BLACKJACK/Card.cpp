#include "stdafx.h"
#include "Card.h"
#include <stdlib.h>

using std::cin;
using std::cout;
using std::endl;

Card::Card() // default constructor
{
	setCardRank(Ace);
	setCardSuit(Hearths);
	setId(); // default id is AceHearths
}

void Card::setCardRank(rank newCardRank) // set value for rank
{
	switch (newCardRank)
	{
	case 1:
	{
		this->cardRank = Ace;
		break;
	}
	case 2:
	{
		this->cardRank = Two;
		break;
	}
	case 3:
	{
		this->cardRank = Three;
		break;
	}
	case 4:
	{
		this->cardRank = Four;
		break;
	}
	case 5:
	{
		this->cardRank = Five;
		break;
	}
	case 6:
	{
		this->cardRank = Six;
		break;
	}
	case 7:
	{
		this->cardRank = Seven;
		break;
	}
	case 8:
	{
		this->cardRank = Eight;
		break;
	}
	case 9:
	{
		this->cardRank = Nine;
		break;
	}
	case 10:
	{
		this->cardRank = Ten;
		break;
	}
	case 11:
	{
		this->cardRank = Jack;
		break;
	}
	case 12:
	{
		this->cardRank = Queen;
		break;
	}
	case 13:
	{
		this->cardRank = King;
		break;
	}
	default:
	{
		this->cardRank = Ace;
		break;
	}
	}
}

rank Card::getCardRank() const
{
	return this->cardRank; // return rank value
}

void Card::setCardSuit(suit newCardSuit) // set value for suit
{
	switch (newCardSuit)
	{
	case 0:
	{
		this->cardSuit = Clubs;
		break;
	}
	case 1:
	{
		this->cardSuit = Diamonds;
		break;
	}
	case 2:
	{
		this->cardSuit = Hearths;
		break;
	}
	case 3:
	{
		this->cardSuit = Spades;
		break;
	}
	default:
	{
		this->cardSuit = Hearths;
		break;
	}
	}
}

suit Card::getCardSuit() const
{
	return this->cardSuit; // return value for suit
}

void Card::setId() // set card id
{
	switch (this->cardRank) // number starts with card value 
	{                       // copy card value
	case 1:
	{
		strcpy_s(this->id, strlen("Ace") + 1, "Ace");
		break;
	}
	case 2:
	{
		strcpy_s(this->id, strlen("Two") + 1, "Two");
		break;
	}
	case 3:
	{
		strcpy_s(this->id, strlen("Three") + 1, "Three");
		break;
	}
	case 4:
	{
		strcpy_s(this->id, strlen("Four") + 1, "Four");
		break;
	}
	case 5:
	{
		strcpy_s(this->id, strlen("Five") + 1, "Five");
		break;
	}
	case 6:
	{
		strcpy_s(this->id, strlen("Six") + 1, "Six");
		break;
	}
	case 7:
	{
		strcpy_s(this->id, strlen("Seven") + 1, "Seven");
		break;
	}
	case 8:
	{
		strcpy_s(this->id, strlen("Eight") + 1, "Eight");
		break;
	}
	case 9:
	{
		strcpy_s(this->id, strlen("Nine") + 1, "Nine");
		break;
	}
	case 10:
	{
		strcpy_s(this->id, strlen("Ten") + 1, "Ten");
		break;
	}
	case 11:
	{
		strcpy_s(this->id, strlen("Jack") + 1, "Jack");
		break;
	}
	case 12:
	{
		strcpy_s(this->id, strlen("Queen") + 1, "Queen");
		break;
	}
	case 13:
	{
		strcpy_s(this->id, strlen("King") + 1, "King");
		break;
	}
	default:
	{
		strcpy_s(this->id, strlen("Ace") + 1, "Ace");
		break;
	}
	}

	switch (this->cardSuit) // merge with suit value 
	{
	case 0:
	{
		strcat_s(this->id, strlen(this->id) + strlen("Clubs") + 1, "Clubs");
		break;
	}
	case 1:
	{
		strcat_s(this->id, strlen(this->id) + strlen("Diamonds") + 1, "Diamonds");
		break;
	}
	case 2:
	{
		strcat_s(this->id, strlen(this->id) + strlen("Hearths") + 1, "Hearths");
		break;
	}
	case 3:
	{
		strcat_s(this->id, strlen(this->id) + strlen("Spades") + 1, "Spades");
		break;
	}
	default:
	{
		strcat_s(this->id, strlen(this->id) + strlen("Hearths") + 1, "Hearths");
		break;
	}
	}
}

const char * Card::getId() const
{
	return this->id; 
}

void Card::changeId(const char * other) // merger other with card id  
{                                       //  we use other as the deck id
	char* tempId = new char[25]; //  declare variable to rewrite the new id 
	strcpy_s(tempId, 25, other);
	strcat_s(tempId, 25, this->id);
	strcpy_s(this->id, 25, tempId); // rewrite id  from tempId to this-> id
}                                  

ostream & operator<<(ostream & out, const Card & other) // output operator
{
	out << "Card Rank: " << other.cardRank << endl // display values
		<< "Card Suit: " << other.cardSuit << endl
		<< "Card Id: " << other.id << endl;

	return out;
}

istream & operator>>(istream & in, Card & other) // input operator
{
	int rankC, suitC;

	cout << "Enter card Rank: (Ace,Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King)";
	in >> rankC;

	switch (rankC) // input card rank
	{
	case 1:
	{
		other.setCardRank(Ace);
		break;
	}
	case 2:
	{
		other.setCardRank(Two);
		break;
	}
	case 3:
	{
		other.setCardRank(Three);
		break;
	}
	case 4:
	{
		other.setCardRank(Four);
		break;
	}
	case 5:
	{
		other.setCardRank(Five);
		break;
	}
	case 6:
	{
		other.setCardRank(Six);
		break;
	}
	case 7:
	{
		other.setCardRank(Seven);
		break;
	}
	case 8:
	{
		other.setCardRank(Eight);
		break;
	}
	case 9:
	{
		other.setCardRank(Nine);
		break;
	}
	case 10:
	{
		other.setCardRank(Ten);
		break;
	}
	case 11:
	{
		other.setCardRank(Jack);
		break;
	}
	case 12:
	{
		other.setCardRank(Queen);
		break;
	}
	case 13:
	{
		other.setCardRank(King);
		break;
	}
	default:
	{
		other.setCardRank(Ace);
		break;
	}
	}

	cout << "Enter card Suit: (Clubs, Diamonds, Hearths, Spades)";
	in >> suitC;

	switch (suitC) // input card suit
	{
	case 0:
	{
		other.setCardSuit(Clubs);
		break;
	}
	case 1:
	{
		other.setCardSuit(Diamonds);
		break;
	}
	case 2:
	{
		other.setCardSuit(Hearths);
		break;
	}
	case 3:
	{
		other.setCardSuit(Spades);
		break;
	}
	default:
	{
		other.setCardSuit(Hearths);
		break;
	}
	}

	other.setId(); 

	return in;
}
