#ifndef FINDIT_H           // Prevent multiple definitions if this 
#define FINDIT_H           // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"
#include "Button.h"
#include "VisualSin.h"
#include <vector>

class FindIt : public Game
{
	private:
    // game items
    TextureManager backGroundTexture, sinTextures; // textures
    Image   background;               // menu image
    TextDX  *dxText;            // DirectX font
	VisualSin* targetSin, *targetImage;
	std::vector<VisualSin*> sins;
	float time;					//Timer to track time remaining
	int level;					//current level of the game
	int numFish;				//Number of current non-target fish of level
	string timer;

public:
    // Constructor
    FindIt();
    // Destructor
    virtual ~FindIt();
    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	VisualSin* SinFactory(int);
	void NewRound();
	//void RecordScore();
};

#endif