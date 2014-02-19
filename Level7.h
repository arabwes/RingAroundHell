// PREVENT MULTIPLE DEFINITIONS IF FILE IS INCLUDED IN MORE PLACES
#ifndef _LEVEL7_H
#define _LEVEL7_H           
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"

class Level7 : public Game
{
protected:
	// GAME ITEMS
    TextureManager	wallpaper;		// BACKGORUND TEXTURE
	TextureManager	badbitch;		// ENEMY TEXTURE
	TextureManager	bborb;			// ENEMY WEAPON TEXTURE
	TextureManager	protagonist;	// CHARACTER TEXTURE	
	TextureManager	proscythe;			// CHARACTER WEAPON TEXTURE

    Image			wall, bitch, pro;	// MENU IMAGES
	Image			orb, scythe;		
    TextDX			* dxFont;			// DIRECT X FONT
    std::string		message;
    float			messageY;

public:
	Level7();	// CONSTRUCTOR
	~Level7();	// DESTRUCTOR

    // INITIALIZATION EXCLUSIVELY FOR THE FIGHTING LEVEL
    void initialize(HWND hwnd);
    void update();				// OVERRIDDEN FROM INHERITED GAME CLASS
    void ai();					// "
    void collisions();			// "
    void render();				// "
	//void renderGame();
    void releaseAll();
    void resetAll();
};

#endif