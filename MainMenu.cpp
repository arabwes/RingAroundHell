#include"MainMenu.h"
#include"LevelManager.h"

//=============================================================================
// Constructor
//=============================================================================
MainMenu::MainMenu()
{
    dxFont = new TextDX();  // DirectX font
}

//=============================================================================
// Destructor
//=============================================================================
MainMenu::~MainMenu()
{
    releaseAll();           // call onLostDevice() for every graphics item
    safeDelete(dxFont);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void MainMenu::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // menu texture
	if (!splashScreenTexture.initialize(graphics,"ArtAssets//SplashScreen.jpg"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if (!creditTexture.initialize(graphics,"ArtAssets//CreditScreen.jpg"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
    if (!menuTexture.initialize(graphics,"pictures//HellAbyss.jpg"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

	// button game textures
    if (!btnTextures.initialize(graphics,"pictures\\Buttons.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button textures"));

    // menu image
    if (!menu.initialize(graphics,0,0,0,&menuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if (!splashScreen.initialize(graphics,0,0,0,&splashScreenTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash Screen"));
	if (!creditScreen.initialize(graphics,0,0,0,&creditTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash Screen"));

	Button *button;
	for(int i = 0; i < 9; i++)
	{
		button = ButtonFactory(i);
		buttons.push_back(button);
	}

	startTime = GetTickCount();
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void MainMenu::update()
{
	std::vector<Button*>::iterator it;
	for(it = buttons.begin(); it < buttons.end(); it++)
	{
		(*it)->Update();
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void MainMenu::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void MainMenu::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void MainMenu::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	menu.draw();
	std::vector<Button*>::iterator it;
	for(it = buttons.begin(); it < buttons.end(); it++)
	{
		(*it)->draw();
	}

	if(GetTickCount() < startTime + 5000)
		splashScreen.draw();
	else if(GetTickCount() < startTime + 10000)
		creditScreen.draw();
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void MainMenu::releaseAll()
{
    dxFont->onLostDevice();
    menuTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void MainMenu::resetAll()
{
    menuTexture.onResetDevice();
    dxFont->onResetDevice();
    Game::resetAll();
    return;
}

Button* MainMenu::ButtonFactory(int i)
{
	Button * btn;
	btn = new Button(i+1);
	//Offsets so that buttons draw in the center of the screen
	int wOffset = GAME_WIDTH/2 - 150;		//Offset from the left where buttons start drawing
	int hOffset = GAME_HEIGHT/2 - 150;		//Offset from the top where buttons start drawing

	if(!btn->initialize(this, 100, 100, 3, &btnTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button texture"));
	int row = 0;
	//Positions of the buttons
	float tX = wOffset + 100*(i%3);	
	switch(i)
	{
	case 0: case 1: case 2:
		row = 0;
		break;
	 case 3: case 4: case 5:
		row = 1;
		break;
	 case 6: case 7: case 8:
		row = 2;
		break;
	};

	float tY = hOffset + 100*(row);

	btn->setFrames(i, i);
	btn->setCurrentFrame(i);
	btn->setX(tX);
	btn->setY(tY);
	return btn;
}

int MainMenu::UpdateLevel(int lvl)
{
	return lvl;
}

int MainMenu::ButtonListener()
{
	std::vector<Button*>::iterator it;
	for(it = buttons.begin(); it < buttons.end(); it++)
	{
		if((*it)->Update())
		{
			return (*it)->GetBtnLevel();
		}
	}
	return 0;

}