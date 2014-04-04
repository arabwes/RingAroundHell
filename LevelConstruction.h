#ifndef LEVELCONSTRUCTION_H           // Prevent multiple definitions if this 
#define LEVELCONSTRUCTION_H           // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"


class LevelConstruction : public Game
{
private:
	// game items
	TextureManager backgroundTexture; // textures
	Image   background;               // menu image
	TextDX  *dxFont;            // DirectX font

public:
	// Constructor
	LevelConstruction();
	// Destructor
	virtual ~LevelConstruction();
	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();

};

#endif