#include"GreedLevel.h"
#include"LevelManager.h"
#include"constants.h"

//=============================================================================
// Constructor
//=============================================================================
GreedLevel::GreedLevel()
{
    dxFont = new TextDX();  // DirectX font
}

//=============================================================================
// Destructor
//=============================================================================
GreedLevel::~GreedLevel()
{
    releaseAll();           // call onLostDevice() for every graphics item
    safeDelete(dxFont);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void GreedLevel::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // menu texture
    if (!menuTexture.initialize(graphics,"pictures//HellAbyss.jpg"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

    // menu image
    if (!menu.initialize(graphics,0,0,0,&menuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	//Error here!!!!
	CreateDeck();

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void GreedLevel::update()
{
	int count = 0;
	std::vector<Card*>::iterator it;

	for(it = deck.begin(); it < deck.end(); it++)
	{
		count++;
		(*it)->Reposition(0+30*count, 0+96*(count%4));
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void GreedLevel::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void GreedLevel::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void GreedLevel::render()
{
    graphics->spriteBegin();                // begin drawing sprites
	
	std::vector<Card*>::iterator it;
	for(it = deck.begin(); it < deck.end(); it++)
	{
		(*it)->draw();
	}

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void GreedLevel::releaseAll()
{
    dxFont->onLostDevice();
    menuTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void GreedLevel::resetAll()
{
    menuTexture.onResetDevice();
    dxFont->onResetDevice();
    Game::resetAll();
    return;
}

void GreedLevel::CreateDeck()
{
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
			tempCard->Initialize(graphics, this);	//Set textures onto cards
			deck.push_back(tempCard);	//Push card into Deck		
		}
	}
}

void CombineString(string &tString,string Letter1, string Letter2, int Number)
{
	stringstream SStm;
	
	SStm << Letter1 << Number << Letter2;
	tString = SStm.str();
}