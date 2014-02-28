//Player.cpp

#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

Player::Player(string tName, int Y)
{
	name = tName;
	//dropped51 = false;
	turn = false;
	handY = Y;
	
}

//The player adds a card to their hand
void Player::DrawCard(Card *tCard)
{
	hand.push_back(tCard);	//Push the card into the hand vector
	UpdateHand();
}


void Player::UpdateHand()
{
	int i = 0;
	currentPoints = 0;
	for(handIt = hand.begin(); handIt < hand.end(); handIt++)
	{
		i++;
		int NewX;
		NewX = 300/hand.size() * i;
		(*handIt)->Reposition(NewX+150, handY);
		(*handIt)->CardUpdate();
		currentPoints += (*handIt)->GetValue();
	}
}

void Player::ShowHand()
{	
	for(handIt = hand.begin(); handIt < hand.end(); handIt++)
	{
		(*handIt)->UpdateFace(turn);
		(*handIt)->draw();
	}
}

int Player::GetHandPoints()
{
	return currentPoints;
}