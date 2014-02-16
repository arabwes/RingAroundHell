#include "Level1.h"
Level1::Level1()
{
	initialized=false;

}
Level1:: ~Level1()
{
	releaseAll();
}
// Initialize the game
void Level1::initialize(HWND hwnd)
{
	 Game::initialize(hwnd); // throws GameError
	 // 
	 if (!BgTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializingbackground"));
	//
	 if (!PlayerTextures.initialize(graphics,"ArtAssets\\Jeramiah.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	//
	if (!background.initialize(this, BgNS::WIDTH, BgNS::HEIGHT, &BgTexture))
      throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg"));
	//
	 if (!player1.initialize(this, BumNS::WIDTH, BumNS::HEIGHT, BumNS::TEXTURE_COLS, &PlayerTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bum"));
	 //
		 //

	 player1.setFrames(BumNS::BUM_START_FRAME, BumNS::BUM_END_FRAME);
	 player1.setCurrentFrame(BumNS::BUM_START_FRAME);
	 player1.setColorFilter(SETCOLOR_ARGB(255,255,255,255));
	 //
	 player1.setX(GAME_WIDTH/4-BumNS::WIDTH);
	 player1.setY(GAME_HEIGHT/2-BumNS::HEIGHT);
	 player1.setVelocity(VECTOR2(0,BumNS::SPEED));
	 //
	return;
}
void Level1::update()
{
	if(player1.getActive())
	{
		if (input->isKeyDown(SHIP1_LEFT_KEY) || input->getGamepadDPadLeft(0))   // if turn ship1 left
		{
			player1.setmoving(true);
			player1.setDirectL(true);
		}
		else{player1.setmoving(false);player1.setDirectL(false);}
		if (input->isKeyDown(SHIP1_RIGHT_KEY) || input->getGamepadDPadRight(0)) // if turn ship1 right
		{
			player1.setmoving(true);
			player1.setDirectR(true);
		}
		else{player1.setmoving(false);player1.setDirectR(false);}
	}

player1.update(frameTime);
	background.update(frameTime);
	
}
void Level1::ai()
{
}
void Level1::collisions()
{
}
void Level1::render()
{
	graphics->spriteBegin();	
	background.draw();
	player1.draw();

	 graphics->spriteEnd();
}
void Level1::consoleCommand()
{
}
void Level1::roundStart()
{
}
void Level1::releaseAll()
{
	PlayerTextures.onLostDevice();
	BgTexture.onLostDevice();
	Game::releaseAll();
}
void Level1::resetAll()
{

	PlayerTextures.onResetDevice();
	BgTexture.onResetDevice();
}