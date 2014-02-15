#ifndef Level1_H           
#define Level1_H       
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "dashboard.h"
#include "background.h"
#include "Bum.h"
#include "Level1.h"


class Level1: public Game
{
private:
	TextureManager PlayerTextures,BgTexture;
	Bum player1;
	bg background;
	bool roundOver;
public:
	Level1();
    // Destructor
    virtual ~Level1();
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