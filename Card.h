#ifndef CARD_H
#define CARD_H
// Card.h
// Basic Outline of a Playing Card

#include <stack>
#include <string>
#include "entity.h"
#include "textureManager.h"
using namespace std;

class Card : public Entity
{
private:
	string fullName;			// Full name of card (ie.. Ace of Spades)
	string name;				// Name of card (ie.. King, Ace, 10)
	int value;					// Numerical value of card (King is 10)
	int number;					// Numerical order of card
	string suit;				// Suit of card
	string fileName;			// Filename of Card image
	string facedownFileName;	// Filename of back of card
	bool isFaceDown;				// Flag for the direction the card is facing
	TextureManager texMan;

public:
	string GetSuit();		// Returns Suit of card
	int GetNum();			// Returns Number of card
	string GetName();		// Returns Name of card
	string GetFullName();	// Returns FullName of card
	bool Selected;			// Flag to recognize if a card has been selected or not
	int GetValue();			// Returns Value of card
	string UpdateFace(bool ShowFace);

	void Reposition(int x, int y);
	Card();
	Card(string TempFName, string TempName, string TempSuit, int TempVal, int TempNum, string File, string facedown);  //Creates Card
	~Card();
};

#endif