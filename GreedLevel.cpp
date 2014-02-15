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

	// main game textures
    if (!cardTextures.initialize(graphics,"pictures\\Buttons.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button textures"));

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
			std::string TempFName, TempName, TempSuit, TempFile, TempBack;
			int TempVal, TempNum;

			// Assign Suit to cards
			if(i < 13)
				TempSuit = "Club";
			else if(i < 26)
				TempSuit = "Diamond";
			else if(i < 39)
				TempSuit = "Heart";
			else if(i < 52)
				TempSuit = "Spade";
		
			// Assign values and names to cards
			switch(i%13)
			{
			case 1:
				TempFName = "Ace of " + TempSuit;
				TempName = "Ace";
				TempVal = 1;
				TempNum = i;
				break;
			case 2:
				TempFName = "2 of " + TempSuit;
				TempName = "2";
				TempVal = 2;
				TempNum = i;
				break;
			case 3:
				TempFName = "3 of " + TempSuit;
				TempName = "3";
				TempVal = 3;
				TempNum = i;
				break;
			case 4:
				TempFName = "4 of " + TempSuit;
				TempName = "4";
				TempVal = 4;
				TempNum = i;
				break;
			case 5:
				TempFName = "5 of " + TempSuit;
				TempName = "5";
				TempVal = 5;
				TempNum = i;
				break;
			case 6:
				TempFName = "6 of " + TempSuit;
				TempName = "6";
				TempVal = 6;
				TempNum = i;
				break;
			case 7:
				TempFName = "7 of " + TempSuit;
				TempName = "7";
				TempVal = 7;
				TempNum = i;
				break;
			case 8:
				TempFName = "8 of " + TempSuit;
				TempName = "8";
				TempVal = 8;
				TempNum = i;
				break;
			case 9:
				TempFName = "9 of " + TempSuit;
				TempName = "9";
				TempVal = 9;
				TempNum = i;
				break;
			case 10:
				TempFName = "10 of " + TempSuit;
				TempName = "10";
				TempVal = 10;
				TempNum = i;
				break;
			case 11:
				TempFName = "Jack of " + TempSuit;
				TempName = "Jack";
				TempVal = 10;
				TempNum = i;
				break;
			case 12:
				TempFName = "Queen of " + TempSuit;
				TempName = "Queen";
				TempVal = 10;
				TempNum = i;
				break;
			case 0:
				TempFName = "King of " + TempSuit;
				TempName = "King";
				TempVal = 10;
				TempNum = 13;
				break;
			}
		
			// Create Filename of each card
			if(i <= 13)
				CombineString(TempFile, "ArtAssets\\c", ".png", i%13);			
			else if(i <= 26)
				CombineString(TempFile,"ArtAssets\\d", ".png", i%13);
			else if(i <= 39)
				CombineString(TempFile,"ArtAssets\\h", ".png", i%13);
			else if(i <= 52)
				CombineString(TempFile,"ArtAssets\\s", ".png", i%13);
			
			if(l == 1)
				TempBack = "ArtAssets\\backblue1.png";
			else if(l == 2)
				TempBack = "ArtAssets\\backred1.png";

			Card *tempCard = new Card(TempFName, TempName, TempSuit, TempVal, TempNum, TempFile, TempBack);	//Create the Card
			
			// card game textures
			if (!cardTextures.initialize(graphics,TempFile))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button textures"));

			if(!tempCard->initialize(this, 71, 96, 1, &cardTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing card texture"));
	
			tempCard->Reposition(455, 316);
			deck.push_back(tempCard);	//Place card into Card list
			
		}
	}
}

void CombineString(string &TempString,string Letter1, string Letter2, int Number)
{
	stringstream SStm;
	
	SStm << Letter1 << Number << Letter2;
	TempString = SStm.str();
}