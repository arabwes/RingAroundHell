#ifndef PLAYER_H
#define PLAYER_H
//Player.h
//The player has a hand of 14 cards
//and can discard/drop/draw cards from the Field(deck)

#include <vector>
#include "Card.h"

class Player
{
private:
	string name;			//Player's Name
	vector<Card*> hand;		//The Player's Hand
	vector<Card*>::iterator handIt;	//Iterator for hand
	int currentPoints;
	int coins, bet;
	bool dropped51;			//Flag to recognize if player has dropped a value of 51
	

public:
	int handY;	//Y coordinate of hand 
	int GetHandPoints();		//Returns cumutalitive total of all card's value in hand
	int GetHandCount();			//Returns amount of cards in hand
	bool turn;	//Flag to tell if player can play or not
	void DrawCard(Card *tCard);		//Adds Card to Hand
	void ShowHand();			//Reveals/conceals own hand to player
	void UpdateHand();			//Visual update of hand
	void MakeBet(int amount);	//Make a bet with specified amount 
	void UpdateBet(bool win);	//Win bet, lose bet depending on round result
	Player(string tName, int Y);			//Player Constructor
	Player();
	~Player();
};

#endif