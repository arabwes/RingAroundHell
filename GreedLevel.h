#ifndef GREEDLEVEL_H           // Prevent multiple definitions if this 
#define GREEDLEVEL_H           // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"
#include "constants.h"
#include "Deck.h"
#include "Player.h"
#include "Button.h"
#include<vector>

class GreedLevel : public Game
{
	private:
    // game items
    TextureManager menuTexture, cardTextures, deckTexture, btnHitTexture, 
		btnDoneTexture, btnPlusTexture, btnMinusTexture, coinTexture; // textures
    Image   menu;               // menu image
    TextDX  *playerText, *dealerText, *betAmount;            // DirectX font
	Deck *deck;						//Deck of cards
	Player *player, *dealer;		//The player and dealer
	Button *btnHitMe, *btnDone;		//Buttons to interact with level
	Button *btnBetPlus, *btnBetMinus;
	Entity *coin;
	string roundText;
	float timer;					//Timer to control timings
	bool roundStart, madeBets;		//Flags 
	int betCount;
	int clickedLvl;			
	char winner;
	Card* CardFactory(int);
	bool roundOver;

public:
	
    // Constructor
    GreedLevel();
    // Destructor
    virtual ~GreedLevel();
    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();

	void beginRound();
	void ConcludeRound();
};

#endif