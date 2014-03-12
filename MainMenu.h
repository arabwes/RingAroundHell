#ifndef MAINMENU_H           // Prevent multiple definitions if this 
#define MAINMENU_H           // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "textDX.h"
#include"Button.h"
#include<vector>

class MainMenu : public Game
{
	private:
    // game items
    TextureManager splashScreenTexture, creditTexture, menuTexture, btnTextures; // textures
    Image   menu, splashScreen, creditScreen;               // menu image
    TextDX  *dxFont;            // DirectX font
	std::vector<Button*> buttons;
	int clickedLvl;
	Button* ButtonFactory(int);
public:
    // Constructor
    MainMenu();
    // Destructor
    virtual ~MainMenu();
    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	int UpdateLevel(int);
	int ButtonListener();
};

#endif