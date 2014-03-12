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
	coin = new Entity();
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
	roundOver = false;
	madeBets = false;
	player->turn = true;

	//Points
	playerText->initialize(graphics, 48, false, false, "Arial");
	playerText->setFontColor(graphicsNS::YELLOW);
	dealerText->initialize(graphics, 48, false, false, "Arial");
	dealerText->setFontColor(graphicsNS::BLUE);
	betAmount->initialize(graphics, 48, false, false, "Arial");
	betAmount->setFontColor(graphicsNS::GREEN);

    // background texture
    if (!menuTexture.initialize(graphics,"pictures//HellAbyss.jpg"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
    if (!coinTexture.initialize(graphics,"ArtAssets//copperCoin.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
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
    if (!background.initialize(graphics,0,0,0,&menuTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	if (!coin->initialize(this, 32, 25, 8, &coinTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	if (!btnHitMe->initialize(this, 100, 50, 1, &btnHitTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hit button"));
	if (!btnDone->initialize(this, 100, 50, 1, &btnDoneTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing done button"));
	if (!btnBetPlus->initialize(this, 25, 25, 1, &btnPlusTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	if (!btnBetMinus->initialize(this, 25, 25, 1, &btnMinusTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
	
	//Set Button positions
	btnHitMe->setX(GAME_WIDTH*(0.05));
	btnDone->setX(GAME_WIDTH*(0.05));
	btnHitMe->setY(GAME_HEIGHT*(0.4));
	btnDone->setY(GAME_HEIGHT*(0.4) + btnDone->getHeight()*(1.1));

	btnBetPlus->setX(GAME_WIDTH*(0.9));
	btnBetMinus->setX(GAME_WIDTH*(0.9));
	btnBetPlus->setY(GAME_HEIGHT*(0.5));
	btnBetMinus->setY(GAME_HEIGHT*(0.5) + btnBetMinus->getHeight()*(1.1));
	
	//Setup coin
	coin->setFrames(0, 7);	
	coin->setCurrentFrame(1);
	coin->setX(GAME_WIDTH/5);
	coin->setY(GAME_HEIGHT*.67);
	deck->Initialize(graphics);

	//Play music
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
		if(btnBetPlus->Update() && betCount < player->GetCoins())
		{
			PlaySound("CasinoSoundPackage\\chipsStack3.wav", NULL, SND_FILENAME | SND_ASYNC);
			betCount++;
		}
		if(btnBetMinus->Update() && betCount > 0)
		{
			PlaySound("CasinoSoundPackage\\chipsStack4.wav", NULL, SND_FILENAME | SND_ASYNC);
			betCount--;
		}
		if(btnDone->Update())
		{
			player->MakeBet(betCount);
			dealer->MakeBet(betCount);
			madeBets = true;
		}
	}

	if(roundOver)
	{
		ConcludeRound();
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

			if(GetTickCount() > startTime + 1000)
			{
				startTime = GetTickCount();
				dealer->DrawCard(deck->DrawCard());
			}
			
		}
		else if(GetTickCount() > startTime + 3000)
		{
			dealer->turn = false;
			roundOver = true;
		}
	}
	
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
	coin->update(frameTime*10);

    graphics->spriteBegin();                // begin drawing sprites
	
	background.draw();
	if(madeBets)
	{
		btnHitMe->draw();
	}
	else
	{
		btnBetPlus->draw();
		btnBetMinus->draw();
	}
	btnDone->draw();
	deck->draw();
	coin->draw();

	dealer->ShowHand();		//Draw dealer's hand
	player->ShowHand();		//Draw player's hand

	playerText->print(to_string((long double)player->GetHandPoints()), GAME_WIDTH/2, GAME_HEIGHT*.65);
	playerText->print(to_string((long double)player->GetCoins()), GAME_WIDTH/4, GAME_HEIGHT*.65);
	playerText->print(to_string((long double)betCount), GAME_WIDTH*(0.89), GAME_HEIGHT*(0.4));
	
	if(results)
	{
		dealerText->print(roundText, GAME_WIDTH/3, GAME_HEIGHT*.25);
		if(GetTickCount() > startTime + 3000)
		{
			paused = false;
			results = false;
		}
	}
	
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
	
	if(dealer->GetHandCount() < 2)
	{
		if(GetTickCount() > startTime + 1000)
		{
			startTime = GetTickCount();
			dealer->DrawCard(deck->DrawCard());
		}
	}

	if(player->GetHandCount() < 2)
	{
		if(GetTickCount() > startTime + 1000)
		{
			startTime = GetTickCount();
			player->DrawCard(deck->DrawCard());	
		}
	}
	if(player->GetHandCount() == 2)
	{
		dealer->turn = false;
		player->turn = true;
		roundStart = true;
	}
}

void GreedLevel::ConcludeRound()
{
	if(!dealer->turn && !player->turn)
	{
		if(player->GetHandPoints() > 21)
		{
			winner = 'D';
		}
		else if(dealer->GetHandPoints() > 21)
		{
			winner = 'P';
		}
		else if(player->GetHandPoints() > dealer->GetHandPoints())
		{
			winner = 'P';
		}
		else if(dealer->GetHandPoints() > player->GetHandPoints())
		{
			winner = 'D';
		}
	}

	if(winner == 'P')
	{

		player->UpdateBet(true);
		dealer->UpdateBet(false);
		roundText = "You Win!";
	}
	else if(winner == 'D')
	{
		player->UpdateBet(false);
		dealer->UpdateBet(true);
		roundText = "You Lose!";
	}

	madeBets = false;
	roundStart = false;
	results = true;
	player->turn = true;
	betCount = 0;
	//Empty hands
	player->EmptyHand();	
	dealer->EmptyHand();
	roundOver = false;
	paused = true;
	startTime = GetTickCount();
}