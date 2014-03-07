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
	btnBetPlus = new Button(NULL);
	btnBetMinus = new Button(NULL);
	player = new Player("Player", (int) GAME_HEIGHT*(0.8));
	dealer = new Player("Dealer", 0);
	playerText = new TextDX();
	dealerText = new TextDX();
	betAmount = new TextDX();
	betCount = 0;
	timer = 0;
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
	btnMinusTexture.onLostDevice();
	btnPlusTexture.onLostDevice();

    safeDelete(playerText);
	safeDelete(dealerText);
	safeDelete(betAmount);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void GreedLevel::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	srand(time(NULL));
	roundStart = false;
	madeBets = false;
	player->turn = true;

	//Points
	playerText->initialize(graphics, 48, false, false, "Arial");
	playerText->setFontColor(graphicsNS::YELLOW);
	dealerText->initialize(graphics, 48, false, false, "Arial");
	dealerText->setFontColor(graphicsNS::BLUE);
	betAmount->initialize(graphics, 48, false, false, "Arial");
	betAmount->setFontColor(graphicsNS::GREEN);

    // menu texture
    if (!menuTexture.initialize(graphics,"pictures//HellAbyss.jpg"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
    // Draw button texture
    if (!btnHitTexture.initialize(graphics,"ArtAssets//HitMe.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button texture"));
	// End turn button texture
    if (!btnDoneTexture.initialize(graphics,"ArtAssets//Done.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing button texture"));
	// End turn button texture
    if (!btnPlusTexture.initialize(graphics,"ArtAssets//Plus.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing plus button texture"));
	// End turn button texture
    if (!btnMinusTexture.initialize(graphics,"ArtAssets//Minus.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing minus button texture"));
	
	// images
    if (!menu.initialize(graphics,0,0,0,&menuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if (!btnHitMe->initialize(this, 100, 50, 1, &btnHitTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hit button"));
	if (!btnDone->initialize(this, 100, 50, 1, &btnDoneTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing done button"));
	if (!btnBetPlus->initialize(this, 25, 25, 1, &btnPlusTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if (!btnBetMinus->initialize(this, 25, 25, 1, &btnMinusTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	
	//Set Button positions
	btnHitMe->setX(GAME_WIDTH*(0.05));
	btnDone->setX(GAME_WIDTH*(0.05));
	btnHitMe->setY(GAME_HEIGHT*(0.4));
	btnDone->setY(GAME_HEIGHT*(0.4) + btnDone->getHeight()*(1.1));

	btnBetPlus->setX(GAME_WIDTH*(0.9));
	btnBetMinus->setX(GAME_WIDTH*(0.9));
	btnBetPlus->setY(GAME_HEIGHT*(0.5));
	btnBetMinus->setY(GAME_HEIGHT*(0.5) + btnBetMinus->getHeight()*(1.1));

	deck->Initialize(graphics);
}

//=============================================================================
// Update all game items
//=============================================================================
void GreedLevel::update()
{
	if(madeBets)
	{	
		if(!roundStart)
		{
			beginRound();
		}

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
	}
	else
	{
		if(btnBetPlus->Update())
		{
			PlaySound("CasinoSoundPackage\\chipsStack3.wav", NULL, SND_FILENAME | SND_ASYNC);
			betCount++;
		}
		if(btnBetMinus->Update())
		{
			PlaySound("CasinoSoundPackage\\chipsStack4.wav", NULL, SND_FILENAME | SND_ASYNC);
			betCount--;
		}
		if(btnDone->Update())
		{
			madeBets = true;
		}
	}

	dealer->UpdateHand();
	player->UpdateHand();
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void GreedLevel::ai()
{
	//do stuff then change turn to false
	if(dealer->turn)
	{
		if(player->GetHandPoints() <= 21 && player->GetHandPoints() > dealer->GetHandPoints())
		{
			dealer->DrawCard(deck->DrawCard());
		}
	}
	/*dealer->turn = false;
	player->turn = true;*/
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
	btnBetPlus->draw();
	btnBetMinus->draw();
	deck->draw();
	
	dealer->ShowHand();		//Draw dealer's hand
	player->ShowHand();		//Draw player's hand

	playerText->print(to_string((long double)player->GetHandPoints()), GAME_WIDTH/2, GAME_HEIGHT*.65);
	dealerText->print(to_string((long double)dealer->GetHandPoints()), GAME_WIDTH/2, GAME_HEIGHT*.25);
	playerText->print(to_string((long double)betCount), GAME_WIDTH*(0.89), GAME_HEIGHT*(0.4));
	
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

void GreedLevel::beginRound()
{
	
	while(dealer->GetHandCount() < 2)
	{
		dealer->DrawCard(deck->DrawCard());		
	}

	while(player->GetHandCount() < 2)
	{
		player->DrawCard(deck->DrawCard());				
	}
	
		roundStart = true;
}