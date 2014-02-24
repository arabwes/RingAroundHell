//Deck.cpp
//Wasim Nasir

#include "Deck.h"

Deck::Deck(Game* level) : Entity()
{
	game = level;
	for(int l = 1; l <= 2; l++)
	{
		for(int i = 0; i < 52; i++)
		{
			std::string tFName, tName, tSuit, tFile, tBack;
			int tVal, tNum;

			// Assign Suit to cards
			if(i < 13)
				tSuit = "Club";
			else if(i < 26)
				tSuit = "Diamond";
			else if(i < 39)
				tSuit = "Heart";
			else if(i < 52)
				tSuit = "Spade";
		
			// Assign values and names to cards
			switch(i%13)
			{
			case 1:
				tFName = "Ace of " + tSuit;
				tName = "Ace";
				tVal = 1;
				tNum = i;
				break;
			case 2:
				tFName = "2 of " + tSuit;
				tName = "2";
				tVal = 2;
				tNum = i;
				break;
			case 3:
				tFName = "3 of " + tSuit;
				tName = "3";
				tVal = 3;
				tNum = i;
				break;
			case 4:
				tFName = "4 of " + tSuit;
				tName = "4";
				tVal = 4;
				tNum = i;
				break;
			case 5:
				tFName = "5 of " + tSuit;
				tName = "5";
				tVal = 5;
				tNum = i;
				break;
			case 6:
				tFName = "6 of " + tSuit;
				tName = "6";
				tVal = 6;
				tNum = i;
				break;
			case 7:
				tFName = "7 of " + tSuit;
				tName = "7";
				tVal = 7;
				tNum = i;
				break;
			case 8:
				tFName = "8 of " + tSuit;
				tName = "8";
				tVal = 8;
				tNum = i;
				break;
			case 9:
				tFName = "9 of " + tSuit;
				tName = "9";
				tVal = 9;
				tNum = i;
				break;
			case 10:
				tFName = "10 of " + tSuit;
				tName = "10";
				tVal = 10;
				tNum = i;
				break;
			case 11:
				tFName = "Jack of " + tSuit;
				tName = "Jack";
				tVal = 10;
				tNum = i;
				break;
			case 12:
				tFName = "Queen of " + tSuit;
				tName = "Queen";
				tVal = 10;
				tNum = i;
				break;
			case 0:
				tFName = "King of " + tSuit;
				tName = "King";
				tVal = 10;
				tNum = 13;
				break;
			}
		
			// Create Filename of each card
			if(i <= 13)
				CombineString(tFile, "ArtAssets\\c", ".png", i%13);			
			else if(i <= 26)
				CombineString(tFile,"ArtAssets\\d", ".png", i%13);
			else if(i <= 39)
				CombineString(tFile,"ArtAssets\\h", ".png", i%13);
			else if(i <= 52)
				CombineString(tFile,"ArtAssets\\s", ".png", i%13);
			
			if(l == 1)
				tBack = "ArtAssets\\backblue1.png";
			else if(l == 2)
				tBack = "ArtAssets\\backred1.png";

			Card *tempCard = new Card(tFName, tName, tSuit, tVal, tNum, tFile, tBack);	//Create the Card
			
			//tempCard->Initialize(graphics, game);	//Set textures onto cards
			cardList.push_back(tempCard);	//Push card into Deck		
		}
	}
}

void Deck::Initialize(Graphics* graphics)
{
	ShuffleCards();
	
	std::vector<Card*>::iterator deckIt;
	for(deckIt = cardList.begin(); deckIt < cardList.end(); deckIt++)
	{
		(*deckIt)->Initialize(graphics, game);
		deck.push((*deckIt));
	}
	
	if (!texMan.initialize(graphics, "ArtAssets\\deckView2.png"))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing card textures"));

	if(!this->initialize(game, 81, 106, 1, &texMan))
	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing card texture"));
	this->setX(GAME_WIDTH/2 - spriteData.width/2);
	this->setY(GAME_HEIGHT/2 - spriteData.height/2);
	deckInitialized = true;
}

Card* Deck::DrawCard()
{
	if(deckInitialized)
	{
		Card *tCard = deck.top();
		deck.pop();
		return tCard;
	}
	return NULL;
}

void Deck::ShuffleCards()
{
	// Swap cards in list
	for(int i = 0; i < 400; i++)
	{
		Card *Temp;
		int TempL = rand()%104;
		int TempR = rand()%104;

		Temp = cardList[TempR];
		cardList[TempR] = cardList[TempL];
		cardList[TempL] = Temp;
	}
}

void CombineString(string &tString,string Letter1, string Letter2, int Number)
{
	stringstream SStm;
	
	SStm << Letter1 << Number << Letter2;
	tString = SStm.str();
}