#include "Purgatory.h"
Purgatory::Purgatory()
{
	initialized=false;

}
Purgatory:: ~Purgatory()
{
	releaseAll();
}
// Initialize the game
void Purgatory::initialize(HWND hwnd)
{
	 Game::initialize(hwnd); // throws GameError
	 // 
	 if (!BgTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializingbackground"));
	//
	 if (!PlayerTextures.initialize(graphics,"ArtAssets\\Jeramiah.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	 //
	  if (!enemyTexture.initialize(graphics,"pictures\\ghoul.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ENEMY"));
	//
	if (!background.initialize(this, BgNS::WIDTH, BgNS::HEIGHT, &BgTexture))
      throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg"));
	//
	 if (!player1.initialize(this, BumNS::WIDTH, BumNS::HEIGHT, BumNS::TEXTURE_COLS, &PlayerTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bum"));
	 //
	 if (!enemy.initialize(this, BumNS::WIDTH, BumNS::HEIGHT, BumNS::TEXTURE_COLS, &enemyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
		 //
	 player1.setFrames(BumNS::BUM_START_FRAME, BumNS::BUM_END_FRAME);
	 player1.setCurrentFrame(BumNS::BUM_START_FRAME);
	 player1.setColorFilter(SETCOLOR_ARGB(255,255,255,255));
	//
	 enemy.setFrames(enemyNS::ENEMY_START_FRAME,enemyNS::ENEMY_END_FRAME);
	 enemy.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	 enemy.setColorFilter(SETCOLOR_ARGB(255,255,255,255));
	//
	 enemy.setX(GAME_WIDTH-200);
	 enemy.setY(300);
	 enemy.setVelocity(VECTOR2(0,enemyNS::SPEED1));
	 player1.setX(255);
	 player1.setY(300);
	 player1.setVelocity(VECTOR2(0,BumNS::SPEED));
	 //
	
	return;
}
void Purgatory::update()
{
	if(player1.getActive())
	{
		if (input->isKeyDown(VK_LEFT) || input->getGamepadDPadLeft(0))   // if turn ship1 left
		{
			player1.setmoving(true);
			player1.setDirectL(true);
		}
		//else{input->clearKeyPress(LEFT_KEY_RIGHT);player1.setmoving(false);player1.setDirectL(false);}
		if (input->isKeyDown(VK_RIGHT) || input->getGamepadDPadRight(0)) // if turn ship1 right
		{
			player1.setmoving(true);
			player1.setDirectR(true);
		}
		//else{input->clearKeyPress(RIGHT_KEY_RIGHT);player1.setmoving(false);player1.setDirectR(false);}
		if(input->isKeyDown(VK_UP))
		{
			player1.setjump(true);
		}
		else
		{player1.setjump(false);}
	}
	if(roundOver)
	{
		 roundStart();
	}
	if(enemy.getActive()){enemy.setmoving(true);}

	enemy.update(frameTime);
	player1.update(frameTime);
	background.update(frameTime);
	
}
void Purgatory::ai()
{
}
void Purgatory::collisions()
{
	VECTOR2 Cvector;
	if(player1.collidesWith(enemy,Cvector))
	{
		player1.setPlayerdead(true);
		roundOver=true;
	}
}
void Purgatory::render()
{
	graphics->spriteBegin();	
	background.draw();
	enemy.draw();
	player1.draw();
	 graphics->spriteEnd();
}
void Purgatory::consoleCommand()
{
}
void Purgatory::roundStart()
{
		 enemy.setX(GAME_WIDTH-200);
	 enemy.setY(GAME_HEIGHT/2-BumNS::HEIGHT);
	 enemy.setVelocity(VECTOR2(0,enemyNS::SPEED1));
	 player1.setX(255);
	 player1.setY(GAME_HEIGHT/2-BumNS::HEIGHT);
	 player1.setVelocity(VECTOR2(0,BumNS::SPEED));
	 roundOver = false;
}
void Purgatory::releaseAll()
{
	PlayerTextures.onLostDevice();
	BgTexture.onLostDevice();
	enemyTexture.onLostDevice();
	Game::releaseAll();
}
void Purgatory::resetAll()
{
	enemyTexture.onLostDevice();
	PlayerTextures.onResetDevice();
	BgTexture.onResetDevice();
}