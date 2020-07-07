#include "stdafx.h"
#include "Deck.h"
#include<iostream>

using std::cin;
using std::cout;
using std::endl;
//global variables
int moreThanStandart = 0; //we use it if the cards are more than 52 and we add 52 each time needed
int diamonds = 26, hearths = 39, spades = 52; // we use it to satisfie the algorith for the constructors
int drawCounter = 0; // counts each time the user draws a card

void Deck::increaseSizeDeck() // increase the deck size if the size is bigger than the capacity
{
	this->capacity *= 2;
	Card* variable = new Card[this->capacity]; // create a new array with the new bigger capacity

	for (int i = 0; i < this->capacity; i++)
	{
		variable[i] = this->cards[i];
	}

	this->destroy(); // we have to delete the previous memory, so there is no heap corruption
	this->cards = variable;
}

void Deck::resinSizeDeck() // resin the deck size
{
	this->capacity /= 2;

	if (this->size < this->capacity) // we make verification if the size is smaller than the capacity
	{                                // because we will lose data
		Card* variable = new Card[this->capacity];

		for (int i = 0; i < this->capacity; i++)
		{
			variable[i] = this->cards[i];
		}
		this->destroy();
		this->cards = variable;
	}
}

void Deck::copy(const Deck & other) // copy constructor
{
	setSize(other.size);
	setCapacity(other.capacity);
	strcpy_s(this->deckId, strlen(other.deckId) + 1, other.deckId);

	this->cards = new Card[this->capacity];

	for (int i = 0; i < this->capacity; i++)
	{
		this->cards[i] = other.cards[i]; // copy each card form the other deck
	}
}

void Deck::destroy()
{
	delete[] this->cards; // delete previous data, so there is no memory leak
}

Deck::Deck() // default constructor 
{
	setSize(0);
	setCapacity(52);
	strcpy_s(this->deckId, 8, "Default");
	this->cards = new Card[this->capacity];
}

Deck::Deck(const Deck & other) // copy constructor
{
	this->copy(other);
}

Deck & Deck::operator=(const Deck & other) // we declare operator = for this class
{
	if (this != &other) // if this == &other , there will be no point ot delete and rewrite the data
	{                   // because it is the same
		this->destroy();
		this->copy(other);
	}
	return *this;
}

Deck::~Deck() // destructor
{
	this->destroy();
}

Deck::Deck(const int & newSize) // constructor with only size given
{
	setSize(newSize);
	setCapacity(newSize);
	setDeckId("Custom"); // if the user doesnt want a new id we set the deck id to be "Custom"
	cards = new Card[size]; // we set aside memory for number of cards user wants to use

	for (int i = 0; i < size; i++)
	{
		int colour;
		int power;

		if (i - moreThanStandart <= 12) // algorithm for clubs
		{
			colour = 0;
			power = 12 - (11 - (i - moreThanStandart)); //each time differnt card from Ace to King
		}
		if (i - moreThanStandart > 12 && i - moreThanStandart <= 25) // algorithm for diamonds
		{
			colour = 1;
			power = diamonds - 25; //each time differnt card from Ace to King
			diamonds++;
		}
		if (i - moreThanStandart > 25 && i - moreThanStandart <= 38) // algorithm for hearths
		{
			colour = 2;
			power = hearths - 38; //each time differnt card from Ace to King
			hearths++;
		}
		if (i - moreThanStandart > 38 && i - moreThanStandart <= 51) // algorithm for spades
		{
			colour = 3;
			power = spades - 51; //each time differnt card from Ace to King
			spades++;
		}

		switch (colour) // set suit for each card
		{
		case 0:
		{
			cards[i].setCardSuit(Clubs);
			break;
		}
		case 1:
		{
			cards[i].setCardSuit(Diamonds);
			break;
		}
		case 2:
		{
			cards[i].setCardSuit(Hearths);
			break;
		}
		case 3:
		{
			cards[i].setCardSuit(Spades);
			break;
		}
		default:
		{
			cards[i].setCardSuit(Hearths);
			break;
		}
		}

		switch (power) // set rank for each card
		{
		case 1:
		{
			cards[i].setCardRank(Ace);
			break;
		}
		case 2:
		{
			cards[i].setCardRank(Two);
			break;
		}
		case 3:
		{
			cards[i].setCardRank(Three);
			break;
		}
		case 4:
		{
			cards[i].setCardRank(Four);
			break;
		}
		case 5:
		{
			cards[i].setCardRank(Five);
			break;
		}
		case 6:
		{
			cards[i].setCardRank(Six);
			break;
		}
		case 7:
		{
			cards[i].setCardRank(Seven);
			break;
		}
		case 8:
		{
			cards[i].setCardRank(Eight);
			break;
		}
		case 9:
		{
			cards[i].setCardRank(Nine);
			break;
		}
		case 10:
		{
			cards[i].setCardRank(Ten);
			break;
		}
		case 11:
		{
			cards[i].setCardRank(Jack);
			break;
		}
		case 12:
		{
			cards[i].setCardRank(Queen);
			break;
		}
		case 13:
		{
			cards[i].setCardRank(King);
			break;
		}
		default:
		{
			cards[i].setCardRank(Ace);
			break;
		}
		}

		cards[i].setId(); // set the card id
		cards[i].changeId("Custom"); // add "Custom" infront of the card id for each card

		if (i - moreThanStandart == 51)
		{
			moreThanStandart += 52; // if the cards are more than 52, we add 52 to satisfie the algorithm
			diamonds = 26, hearths = 39, spades = 52; // reset the global variables value

		}
	}
}

Deck::Deck(const int & newSize, const char * newDeckId) // constructor with given size and new deck id
{                        // the logistics are exactly the same as the previous constructor
	setSize(newSize);
	setCapacity(newSize);
	setDeckId(newDeckId); // the only exeption is that the user sets new deck id
	cards = new Card[size];

	for (int i = 0; i < size; i++)
	{
		int colour;
		int power;

		if (i - moreThanStandart <= 12)
		{
			colour = 0;
			power = 12 - (11 - (i - moreThanStandart));
		}
		if (i - moreThanStandart > 12 && i - moreThanStandart <= 25)
		{
			colour = 1;
			power = diamonds - 25;
			diamonds++;
		}
		if (i - moreThanStandart > 25 && i - moreThanStandart <= 38)
		{
			colour = 2;
			power = hearths - 38;
			hearths++;
		}
		if (i - moreThanStandart > 38 && i - moreThanStandart <= 51)
		{
			colour = 3;
			power = spades - 51;
			spades++;
		}

		switch (colour)
		{
		case 0:
		{
			cards[i].setCardSuit(Clubs);
			break;
		}
		case 1:
		{
			cards[i].setCardSuit(Diamonds);
			break;
		}
		case 2:
		{
			cards[i].setCardSuit(Hearths);
			break;
		}
		case 3:
		{
			cards[i].setCardSuit(Spades);
			break;
		}
		default:
		{
			cards[i].setCardSuit(Hearths);
			break;
		}
		}

		switch (power)
		{
		case 1:
		{
			cards[i].setCardRank(Ace);
			break;
		}
		case 2:
		{
			cards[i].setCardRank(Two);
			break;
		}
		case 3:
		{
			cards[i].setCardRank(Three);
			break;
		}
		case 4:
		{
			cards[i].setCardRank(Four);
			break;
		}
		case 5:
		{
			cards[i].setCardRank(Five);
			break;
		}
		case 6:
		{
			cards[i].setCardRank(Six);
			break;
		}
		case 7:
		{
			cards[i].setCardRank(Seven);
			break;
		}
		case 8:
		{
			cards[i].setCardRank(Eight);
			break;
		}
		case 9:
		{
			cards[i].setCardRank(Nine);
			break;
		}
		case 10:
		{
			cards[i].setCardRank(Ten);
			break;
		}
		case 11:
		{
			cards[i].setCardRank(Jack);
			break;
		}
		case 12:
		{
			cards[i].setCardRank(Queen);
			break;
		}
		case 13:
		{
			cards[i].setCardRank(King);
			break;
		}
		default:
		{
			cards[i].setCardRank(Ace);
			break;
		}
		}

		cards[i].setId();
		cards[i].changeId(newDeckId);

		if (i - moreThanStandart == 51) 
		{
			moreThanStandart += 52;
			diamonds = 26, hearths = 39, spades = 52;
		}
	}
}

void Deck::setDeckId(const char * newDeckId) // set the deck id
{
	strcpy_s(this->deckId, 10, newDeckId);
}

const char * Deck::getDeckId() const
{
	return this->deckId; // return the deck id
}

void Deck::setSize(int newSize) //set deck size
{
	if (newSize > 0)
	{
		this->size = newSize;
	}
	else
	{
		this->size = 0;
	}
}

int Deck::getSize() const
{
	return this->size;
}

void Deck::setCapacity(int newCapacity) // set capacity
{
	if (newCapacity > 0)
	{
		this->capacity = newCapacity;
	}
	else
	{
		this->capacity = 52;
	}
}

int Deck::getCapacity() const
{
	return this->capacity; // return capacity
}

void Deck::addCards(const Card & other) // function to add cards into the existing deck
{
	if (this->size == this->capacity)
	{
		increaseSizeDeck(); //  increase the deck size, so there is room for the new card
	}

	this->cards[size] = other; //  input the new card into the deck
	size++;
}

void Deck::removeCards(const int & index) // remove card from deck with given card index
{
	if (index < 0 || index > this->size - 1) // wrong index input
	{
		return;
	}
	for (int i = index; i < this->size - 1; i++) // the loop is going until the deck size - 1
	{                                            // it starts from the index and it rewrites the next card data
		this->cards[i] = this->cards[i + 1];     // that way the array is resizing and the size becomes one less
	}

	size--;
	resinSizeDeck();
}

Card * Deck::getAllCards() const // returns all cards from the deck
{
	return this->cards;
}

void Deck::playWithCustomId(const char* newId) // changes the deck id of already existing deck with new one
{           // we use this function if the user wants to enter a custom id for his deck
	setDeckId(newId); // change deck id

	for (int i = 0; i < getSize(); i++)
	{
		cards[i].setId(); // recreate the card id so we can put the new deck id infront of it instead "Custom"
		cards[i].changeId(newId); // merge the new deck id with standart card id
	}
}

void Deck::outputPlayerCards() // displays all the cards the player has already drawn each time
{
	for (int i = getSize() - drawCounter; i < getSize(); i++) // the loop bigns with the first drawn card
	{                                                         // and ends at the last 
		showRank(cards[i]);                                   // getSize() - drawCounter gives us the first drawn
		cout << " ";
		showSuit(cards[i]);
		cout << " ";
	}
}

bool Deck::isEmpty() // a verification is all the cards are drawn from the deck already
{
	if (drawCounter >= getSize()) // if the drawn cards are more or even it means the deck is empty
	{                            // and no more cards can be drown
		return true;
	}
	else
	{
		return false;
	}
}

double Deck::probability(int points) // calculates the chance of user drawing a card which will gain him 21 
{                                    // points summed up with the points he already has
	int br = 0;  // count cards which complete the condition
	double number1, number2; 

	if (21 - points <= 11) // if the difference between 21 and user points because if it is more than 11
	{                      // there is no card wich can suit his needs
		for (int i = 0; i < getSize() - drawCounter; i++) // the loop is going to the first drawn card
		{
			if (21 - points == cards[i].getCardRank() && 21 - points <= 10)
			{
				br++; // this case covers all the cards from 2 to 10 and Ace if the Ace is 1 point
			}
			else if (21 - points == 11 && cards[i].getCardRank() == 1)
			{
				br++; // this case covers Ace if it is 11 points
			}
		}
		
		number1 = br; // good cases
		number2 = getSize() - drawCounter; // all cases 

		return (number1 / number2);
	}
	else
	{
		return 0.0;
	}
}

void Deck::showRank(Card other) // displays the card rank
{
	switch (other.getCardRank())
	{
	case 1:
	{
		cout << "Ace";
		break;
	}
	case 2:
	{
		cout << "2";
		break;
	}
	case 3:
	{
		cout << "3";
		break;
	}
	case 4:
	{
		cout << "4";
		break;
	}
	case 5:
	{
		cout << "5";
		break;
	}
	case 6:
	{
		cout << "6";
		break;
	}
	case 7:
	{
		cout << "7";
		break;
	}
	case 8:
	{
		cout << "8";
		break;
	}
	case 9:
	{
		cout << "9";
		break;
	}
	case 10:
	{
		cout << "10";
		break;
	}
	case 11:
	{
		cout << "Jack";
		break;
	}
	case 12:
	{
		cout << "Queen";
		break;
	}
	case 13:
	{
		cout << "King";
		break;
	}
	}
}

void Deck::showSuit(Card other) // displays the card suit
{
	switch (other.getCardSuit())
	{
	case 0:
	{
		cout << "(clubs)";
		break;
	}
	case 1:
	{
		cout << "(diamonds)";
		break;
	}
	case 2:
	{
		cout << "(hearths)";
		break;
	}
	case 3:
	{
		cout << "(spades)";
		break;
	}
	}
}

void Deck::shuffle() // shuffles the deck, so the consistency of cards is random
{
	for (int i = 0; i < getSize(); i++)
	{
		swap(i, rand() % getSize()); // swaps the current card with a random one from the deck
	}
}

Card Deck::draw() // takes the first card value and returns it, then puts it on the last position
{
	drawCounter++; // a counter for everytime user draws a card

	Card temp; // declare a temporary Card so we can store the first card data in it

	for (int i = 0; i < getSize(); i++)
	{
		if (getSize() == 2)
		{
			swap(0, 1); // if there are only 2 cards, just swap them
		}
		else if (i == 0)
		{
			temp = cards[i]; // assigns first card data to temp
		}
		else if (i == getSize() - 1) // this is last card
		{
			cards[i - 1] = cards[i]; // assigns last card data to the previous
			cards[i] = temp; // assigns the first card data and put it as last card
		}
		else
		{
			cards[i - 1] = cards[i]; // decrease ever card position by 1
		}
	}

	showRank(temp);
	cout << " ";
	showSuit(temp);

	return temp;
}

void Deck::swap(int other, int another) // swaps to card places by given index
{
	Card temp; // declare a temporary Card so we can store the card on other position
	int variable; // declare variables so if other is bigger than another, they get swaped

	if (other < getSize() && another < getSize() && other != another)
	{
		if (another < other) // other must be smaller or even to another
		{                    //if this is not fulfilled other and another switch value
			variable = other;
			other = another;
			another = other;
		}
		
		  for (int i = 0; i < getSize(); i++)
		  {
			  if (i == other)
			  {
				  temp = cards[i];
			  }
			  else if (i == another)
			  {
				  cards[other] = cards[i]; // swaps cards on position other and another
				  cards[i] = temp;
			  }
		  }
	}
}

void Deck::suit_count(const char * other) // displays the number of card from the deck with the gives suit
{
	int indicator, counter = 0; // declare indicator to check for the given suit
	                            // indicator must be int because enum returns int
	if (other == "Clubs")
	{
		indicator = 0;
	}
	if (other == "Diamonds")
	{
		indicator = 1;
	}
	if (other == "Hearths")
	{
		indicator = 2;
	}
	if (other == "Spades")
	{
		indicator = 3;
	}

	for (int i = 0; i < getSize(); i++)
	{
		if (cards[i].getCardSuit() == indicator)
		{
			counter++;
		}
	}
	cout << "There are " << counter << " cards of this suit!" << endl;
}

void Deck::rank_count(const char * other) // displays the number of card from the deck with the gives rank
{
	int indicator, counter = 0; // declare indicator to check for given rank
								// indicator must be int because enum returns int
	if (other == "Ace")
	{
		indicator = 1;
	}
	if (other == "Two")
	{
		indicator = 2;
	}
	if (other == "Three")
	{
		indicator = 3;
	}
	if (other == "Four")
	{
		indicator = 4;
	}
	if (other == "Five")
	{
		indicator = 5;
	}
	if (other == "Six")
	{
		indicator = 6;
	}
	if (other == "Seven")
	{
		indicator = 7;
	}
	if (other == "Eight")
	{
		indicator = 8;
	}
	if (other == "Nine")
	{
		indicator = 9;
	}
	if (other == "Ten")
	{
		indicator = 10;
	}
	if (other == "Jack")
	{
		indicator = 11;
	}
	if (other == "Queen")
	{
		indicator = 12;
	}
	if (other == "King")
	{
		indicator = 13;
	}

	for (int i = 0; i < getSize() - drawCounter; i++)
	{
		if (cards[i].getCardRank() == indicator)
		{
			counter++;
		}
	}

	cout << "There are " << counter << " cards of this rank!" << endl;
}

ostream & operator<<(ostream & out, const Deck & other) // operator for exist
{
	out << "Deck ID: " << other.deckId << endl;
	out << "All cards: " << endl;

	for (int i = 0; i < other.size; i++)
	{
		out << other.cards[i];
	}

	out << "Size: " << other.size << endl
		<< "Capacity: " << other.capacity << endl;

	return out;
}

istream & operator>>(istream & in, Deck & other) // input operator
{
	cout << "Enter cards:" << endl;

	for (int i = 0; i < other.size; i++)
	{
		cout << "Card: ";
		in >> other.cards[i];
	}

	return in;
}
