#include"FindIt.h"
#include"LevelManager.h"

//=============================================================================
// Constructor
//=============================================================================
FindIt::FindIt()
{
    dxFont = new TextDX();  // DirectX font
}

//=============================================================================
// Destructor
//=============================================================================
FindIt::~FindIt()
{
    releaseAll();           // call onLostDevice() for every graphics item
    safeDelete(dxFont);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void FindIt::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // menu texture
	if (!backGroundTexture.initialize(graphics,"ArtAssets//SeaFloor.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if (!sinTextures.initialize(graphics,"ArtAssets//FishSprites.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	
	if (!background.initialize(graphics,0,0,0,&backGroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	

	for(int i = 0; i < 4; i++)
	{
		sins.push_back(SinFactory((int)rand()%9+1));
	}
	startTime = GetTickCount();
}

//=============================================================================
// Update all game items
//=============================================================================
void FindIt::update()
{
	std::vector<VisualSin *>::iterator sinIt;
	for(sinIt = sins.begin(); sinIt != sins.end(); )
	{
		if((*sinIt)->Update())
		{
			delete (*sinIt);
			sinIt = sins.erase(sinIt);
		}
		else
		{
			++sinIt;
		}
	}
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void FindIt::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void FindIt::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void FindIt::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	background.draw();

	std::vector<VisualSin*>::iterator sinIt;
	for(sinIt = sins.begin(); sinIt != sins.end(); sinIt++)
	{
		(*sinIt)->draw();
	}

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void FindIt::releaseAll()
{
    dxFont->onLostDevice();
    backGroundTexture.onLostDevice();
    sinTextures.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void FindIt::resetAll()
{
    backGroundTexture.onResetDevice();
    sinTextures.onResetDevice();
	dxFont->onResetDevice();
    Game::resetAll();
    return;
}


VisualSin* FindIt::SinFactory(int i)
{
	VisualSin * sin;
	sin = new VisualSin();
	//Offsets so that buttons draw in the center of the screen
	int wOffset = GAME_WIDTH/2 - 150;		//Offset from the left where buttons start drawing
	int hOffset = GAME_HEIGHT/2 - 150;		//Offset from the top where buttons start drawing

	if(!sin->initialize(this, 100, 100, 8, &sinTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sin texture"));
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

	sin->setFrames(i, i);
	sin->setCurrentFrame(i);
	sin->setX(tX);
	sin->setY(tY);
	return sin;
}