//Deck.h
//Wasim Nasir

#ifndef DECK_H           // Prevent multiple definitions if this 
#define DECK_H           // file is included in more than one place

#include "game.h"
#include "Card.h"
#include "entity.h"
#include <vector>
#include <stack>

void CombineString(string &TempString,string Letter1, string Letter2, int Number);

class Deck : public Entity
{
	std::vector<Card*> cardList;
	std::stack<Card*> deck;
	TextureManager texManFront;
	Game* game;
	bool deckInitialized;

public:
	Deck();
	Deck(Game *game);
	void Initialize(Graphics*);
	void ShuffleCards();
	Card* DrawCard();
};

#endif