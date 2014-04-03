#include"LevelConstruction.h"
#include"LevelManager.h"

//=============================================================================
// Constructor
//=============================================================================
LevelConstruction::LevelConstruction()
{
	dxFont = new TextDX();  // DirectX font
}

//=============================================================================
// Destructor
//=============================================================================
LevelConstruction::~LevelConstruction()
{
	releaseAll();           // call onLostDevice() for every graphics item
	safeDelete(dxFont);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void LevelConstruction::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	// menu texture
	if (!backgroundTexture.initialize(graphics, "ArtAssets//HellConstruction.png"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));


	
	// menu image
	if (!background.initialize(graphics, 0, 0, 0, &backgroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

}

//=============================================================================
// Update all game items
//=============================================================================
void LevelConstruction::update()
{

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void LevelConstruction::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void LevelConstruction::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void LevelConstruction::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	background.draw();

	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void LevelConstruction::releaseAll()
{
	dxFont->onLostDevice();
	backgroundTexture.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void LevelConstruction::resetAll()
{
	backgroundTexture.onResetDevice();
	dxFont->onResetDevice();
	Game::resetAll();
	return;
}
