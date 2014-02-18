#ifndef SSGAME_H           
#define SSGAME_H       
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "dashboard.h"
#include "background.h"
#include "Bum.h"
#include "SSenemy.h"


class SSgame: public Game
{
private:
	TextureManager PlayerTextures,BgTexture,enemyTexture;
	Bum player1;
	bg background;
	Enemy enemy;
	bool roundOver;
public:
	SSgame();
    // Destructor
    virtual ~SSgame();
    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void consoleCommand(); // process console command
    void roundStart();  // start a new round of play
    void releaseAll();
    void resetAll();
};
#endif