#ifndef PURGATORY_H           
#define PURGATORY_H       
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "dashboard.h"
#include "background.h"
#include "Bum.h"
#include "Enemy.h"



class Purgatory: public Game
{
private:
	TextureManager PlayerTextures,BgTexture,enemyTexture;
	Bum player1;
	bg background[2];
	Enemy enemy[4];
	TextDX scoreFont;
	int playerScore;
	bool roundOver;
	COLOR_ARGB bCOLOR;
	entityNS::COLLISION_TYPE box;
	RECT PLAYER,ENEMY,FORPOINT;
	char buffer[20];
public:
	Purgatory();
    // Destructor
    virtual ~Purgatory();
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