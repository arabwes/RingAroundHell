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
    TextureManager menuTexture, cardTextures, deckTexture, btnHitTexture, btnDoneTexture; // textures
    Image   menu;               // menu image
    TextDX  *playerPoints, *dealerPoints;            // DirectX font
	Deck *deck;
	Player *player, *dealer;
	Button *btnHitMe, *btnDone;
	int clickedLvl;
	Card* CardFactory(int);
	bool roundStart;

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
};

#endif