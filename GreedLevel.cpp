#include"GreedLevel.h"
#include"LevelManager.h"
#include"constants.h"

//=============================================================================
// Constructor
//=============================================================================
GreedLevel::GreedLevel()
{
    deck = new Deck(this);
	btnHitMe = new Button(NULL);
	btnDone = new Button(NULL);
	player = new Player("Player", (int) GAME_HEIGHT*(0.8));
	dealer = new Player("Dealer", 0);
	playerPoints = new TextDX();
}

//=============================================================================
// Destructor
//=============================================================================
GreedLevel::~GreedLevel()
{
    releaseAll();           // call onLostDevice() for every graphics item
	menuTexture.onLostDevice();
	cardTextures.onLostDevice();
	deckTexture.onLostDevice();
	btnHitTexture.onLostDevice();
	btnDoneTexture.onLostDevice();
    safeDelete(playerPoints);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void GreedLevel::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	srand(time(NULL));
	player->turn = true;
	//Points
	playerPoints->initialize(graphics, 48, false, false, "Arial");
	playerPoints->setFontColor(graphicsNS::YELLOW);

    // menu texture
    if (!menuTexture.initialize(graphics,"pictures//HellAbyss.jpg"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
    // Draw button texture
    if (!btnHitTexture.initialize(graphics,"ArtAssets//HitMe.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	// End turn button texture
    if (!btnDoneTexture.initialize(graphics,"ArtAssets//Done.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));

	// images
    if (!menu.initialize(graphics,0,0,0,&menuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if (!btnHitMe->initialize(this, 100, 50, 1, &btnHitTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if (!btnDone->initialize(this, 100, 50, 1, &btnDoneTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	btnHitMe->setX(GAME_WIDTH*(0.05));
	btnDone->setX(GAME_WIDTH*(0.05));
	btnHitMe->setY(GAME_HEIGHT*(0.4));
	btnDone->setY(GAME_HEIGHT*(0.4) + btnDone->getHeight()*(1.1));

	deck->Initialize(graphics);
}

//=============================================================================
// Update all game items
//=============================================================================
void GreedLevel::update()
{
	if(player->turn)
	{
		if(btnHitMe->Update())
		{
			player->DrawCard(deck->DrawCard());
		}
		else if(btnDone->Update())
		{
			player->turn = false;
			dealer->turn = true;
		}
	}
	else if(dealer->turn)
	{
		ai();
	}

	player->UpdateHand();
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void GreedLevel::ai()
{
	//do stuff then change turn to false

	dealer->turn = false;
	player->turn = true;
}

//=============================================================================
// Handle collisions
//=============================================================================
void GreedLevel::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void GreedLevel::render()
{
    graphics->spriteBegin();                // begin drawing sprites
	
	menu.draw();
	btnHitMe->draw();
	btnDone->draw();
	deck->draw();
	
	player->ShowHand();
	dealer->ShowHand();
	playerPoints->print(to_string((long double)player->GetHandPoints()), GAME_WIDTH/2, GAME_HEIGHT*.7);
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void GreedLevel::releaseAll()
{
    
    menuTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void GreedLevel::resetAll()
{
    menuTexture.onResetDevice();
    Game::resetAll();
    return;
}

