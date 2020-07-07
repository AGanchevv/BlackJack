#pragma once
#include"Card.h" // include class cards so enums can be used in it  

enum rank {   // create enum for card rank
	Ace = 1,  // assign values for each card 
	Two = 2,  
	Three = 3,
	Four = 4,
	Five = 5,
	Six = 6,
	Seven = 7,
	Eight = 8,
	Nine = 9,
	Ten = 10,
	Jack = 11,
	Queen = 12,
	King = 13
};

enum suit {  // create enum for card suit
	Clubs = 0,
	Diamonds = 1,
	Hearths = 2,
	Spades = 3
};


