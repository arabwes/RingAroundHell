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
#include"Card.h"
#include<vector>

void CombineString(string &TempString,string Letter1, string Letter2, int Number);

class GreedLevel : public Game
{
	private:
    // game items
    TextureManager menuTexture, cardTextures; // textures
    Image   menu;               // menu image
    TextDX  *dxFont;            // DirectX font
	std::vector<Card*> deck;
	int clickedLvl;
	Card* CardFactory(int);


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

	void CreateDeck();
};

#endif