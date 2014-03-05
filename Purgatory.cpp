#include "Purgatory.h"
Purgatory::Purgatory()
{
	initialized=false;
	bCOLOR = graphicsNS::BLUE;
	box=entityNS::BOX;
	PLAYER.left=player1.getWidth()-player1.getWidth();
	PLAYER.right=player1.getWidth()-50;
	PLAYER.bottom=player1.getHeight();
	PLAYER.top=player1.getHeight()-50;
	//
	ENEMY.left=enemy[1].getWidth()-enemy[1].getWidth();
	ENEMY. right=enemy[1].getWidth()-50;
	ENEMY.bottom=enemy[1].getHeight();
	ENEMY.top=enemy[1].getHeight()-150;

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
	 scoreFont.initialize(graphics,25,false,false,"score");

	 if (!BgTexture.initialize(graphics,"ArtAssets\\Background.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializingbackground"));
	//
	 if (!PlayerTextures.initialize(graphics,"ArtAssets\\Jeramiah.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	 //
	  if (!enemyTexture.initialize(graphics,"pictures\\ghoul.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ENEMY"));
	//
	  for(int j=0;j<2;j++)
	  {
		if (!background[j].initialize(this, BgNS::WIDTH, BgNS::HEIGHT, &BgTexture))
		  throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bg"));
	  }
	//
	 if (!player1.initialize(this, BumNS::WIDTH, BumNS::HEIGHT, BumNS::TEXTURE_COLS, &PlayerTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bum"));
	 //
	 for(int i =0;i<3;i++)
	 {
	 if (!enemy[i].initialize(this, BumNS::WIDTH, BumNS::HEIGHT, BumNS::TEXTURE_COLS, &enemyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy"));
	 	 

	 enemy[i].setFrames(enemyNS::ENEMY_START_FRAME,enemyNS::ENEMY_END_FRAME);
	 enemy[i].setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	 enemy[i].setColorFilter(SETCOLOR_ARGB(255,255,255,255));
	 enemy[i].setCollisionType(box);
	 enemy[i].setEdge(ENEMY);
	
	 enemy[i].setX(650);
	 enemy[i].setY(350);
	 }
	 enemy[0].setVelocity(VECTOR2(0,enemyNS::SPEED1));enemy[1].seteID(1);
	 enemy[1].setVelocity(VECTOR2(0,enemyNS::SPEED2));enemy[2].seteID(2);
	 //
	 player1.setFrames(BumNS::BUM_START_FRAME, BumNS::BUM_END_FRAME);
	 player1.setCurrentFrame(BumNS::BUM_START_FRAME);
	 player1.setColorFilter(SETCOLOR_ARGB(255,255,255,255));
	 player1.setCollisionType(box);
	  player1.setEdge(PLAYER);
	//
	 player1.setX(50);
	 player1.setY(350);
	 player1.setVelocity(VECTOR2(BumNS::JUMP_HEIGHT,BumNS::SPEED));
	 //
	playerScore=0;
	background[0].setX(0);
	background[1].setX(GAME_WIDTH-0);
	background[0].setY(0);
	background[1].setY(0);
	return;
}

void Purgatory::update()
{
	if(player1.getActive())
	{
		if (input->isKeyDown(VK_LEFT) || input->getGamepadDPadLeft(0)) //MOVE LEFT
		{
			background[0].setmoving(false);background[1].setmoving(false);
			player1.setmoving(true);
			player1.setDirectL(true);
		}
		else{input->clearKeyPress(VK_LEFT);player1.setmoving(false);player1.setDirectL(false);}
		
		if (input->isKeyDown(VK_RIGHT) || input->getGamepadDPadRight(0))//MOVE RIGHT
		{
			background[0].setmoving(true);
			background[1].setmoving(true);
			player1.setmoving(true);
			player1.setDirectR(true);
		}
		else
		{
			input->clearKeyPress(VK_RIGHT);
			player1.setmoving(false);
			player1.setDirectR(false);
			background[0].setmoving(false);
			background[1].setmoving(false);
		}

		if(input->isKeyDown(VK_UP))
		{
			if(player1.getonground())
			{
			player1.setjump(true);
			}
		}
	}
	if(roundOver)
	{
		 roundStart();
	}
	for(int i=0;i<3;i++)
	{
		if(enemy[i].getActive())
		{
			enemy[i].setmoving(true);
		}
		if(enemy[i].getX()<=0)
		{
			playerScore+=1;
		}
		enemy[i].update(frameTime);
	}
	player1.update(frameTime);
	for(int j=0;j<2;j++)
	{
	background[j].update(frameTime);
	}
}

void Purgatory::ai()
{
}

void Purgatory::collisions()
{
	VECTOR2 Cvector;
	for(int i=0;i<3;i++)
	{
	if(player1.collidesWith(enemy[i],Cvector))
	{
		player1.setPlayerdead(true);
		roundOver=true;
	}
	}
}

void Purgatory::render()
{
	graphics->spriteBegin();	
	background[0].draw();
	background[1].draw();
	for(int i=0;i<3;i++)
	{
	enemy[i].draw();
	}
	player1.draw();
	//
	scoreFont.setFontColor(bCOLOR);
	_snprintf_s(buffer,20,"%d",(int)playerScore);
	scoreFont.print(buffer,100,10);
	 graphics->spriteEnd();
}
void Purgatory::consoleCommand()
{
}
void Purgatory::roundStart()
{
	 for(int i =0;i<3;i++)
	 {
	 enemy[i].setX(GAME_WIDTH);
	 enemy[i].setY(350);
	 }
	 enemy[0].setVelocity(VECTOR2(0,enemyNS::SPEED1));	
	 enemy[1].setVelocity(VECTOR2(0,enemyNS::SPEED2));
	 enemy[2].setVelocity(VECTOR2(0,enemyNS::SPEED3));	
	 enemy[3].setVelocity(VECTOR2(0,enemyNS::SPEED4));	
	 //
	 background[0].setmoving(false);
	 background[1].setmoving(false);
	 //
	 player1.setX(50);
	 player1.setY(350);
	 player1.setVelocity(VECTOR2(0,BumNS::SPEED));
	 roundOver = false;
	 player1.setjump(false);
	 player1.setonground(true);
}
void Purgatory::releaseAll()
{
	PlayerTextures.onLostDevice();
	BgTexture.onLostDevice();
	enemyTexture.onLostDevice();
	scoreFont.onLostDevice();
	Game::releaseAll();
	return;
}
void Purgatory::resetAll()
{
	enemyTexture.onLostDevice();
	PlayerTextures.onResetDevice();
	BgTexture.onResetDevice();
	scoreFont.onResetDevice();
	Game::releaseAll();
	return;
}