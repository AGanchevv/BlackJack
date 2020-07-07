#pragma once
#include"Card.h"
#include<iostream>

using std::ostream;
using std::istream;

class Deck
{
private:
	Card * cards; // declare card array
	char deckId[10]; // declare unique deck id

	int size; // it is used to input deck size
	int capacity; // max deck size

	void increaseSizeDeck(); 
	void resinSizeDeck();    

	void copy(const Deck& other);
	void destroy();

public:
	Deck(); // " bix 6 "
	Deck(const Deck& other);
	Deck& operator=(const Deck& other);
	~Deck();

	Deck(const int& newSize); // constructor which requires only size
	Deck(const int& newSize, const char* newDeckId); // requires size and deck id
	// that way the user has choice eighter to enter size and id or only size
	void setDeckId(const char* newDeckId);
	const char* getDeckId()const;

	void setSize(int newSize);
	int getSize()const;

	void setCapacity(int newCapacity);
	int getCapacity()const;

	void addCards(const Card& other);
	void removeCards(const int& index);

	Card* getAllCards()const; // returns array from all the cards in the deck

	void playWithCustomId(const char* newId); // allows user to input new id
	                                          // if the deck is already created
	void outputPlayerCards(); // after every time user draws a card, displays all drawn cards
	                        
	bool isEmpty(); // verification if all cards are drawn

	double probability(int points); // returns  the probability of player drawing a card to round up to 21 points
	                               
	void showRank(Card other); // displays card rank
	void showSuit(Card other); // displays card suit

	void shuffle(); // shuffles the deck, because when it is created the cards are soerted a certain way
	               
	Card draw(); // returns the first card value and put it on the last place 

	void swap(int other, int another); // swaps two cards in deck 

	void suit_count(const char* other); // displays number of cards in deck with searched suit
	void rank_count(const char* other); // displays number of cards in deck with searched rank


	friend ostream& operator<<(ostream& out, const Deck& other);
	friend istream& operator>>(istream& in, Deck& other);
};

