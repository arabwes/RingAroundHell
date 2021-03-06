#include"FindIt.h"
#include"LevelManager.h"

//=============================================================================
// Constructor
//=============================================================================
FindIt::FindIt()
{
    dxText = new TextDX();  // DirectX font
	time = 30;
	level = 1;
	numFish = 8;
	isTimeChanged = false;
	isFound = false;
}

//=============================================================================
// Destructor
//=============================================================================
FindIt::~FindIt()
{
    releaseAll();           // call onLostDevice() for every graphics item
    safeDelete(dxText);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void FindIt::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	dxText->initialize(graphics, 36, false, false, "Arial");
	dxText->setFontColor(graphicsNS::CYAN);

    // menu texture
	if (!backGroundTexture.initialize(graphics,"ArtAssets//HellScape1.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if (!sinTextures.initialize(graphics,"ArtAssets//SkullSprites.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if (!background.initialize(graphics,0,0,0,&backGroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	
	
	int tNum = (int)((rand() % 3));	//Generate random number for target sin
	targetSin = SinFactory(tNum);				//Create target sin
	//sins.push_back(targetSin);					//Insert target sin first so it is always rendered in the back
	for(int i = 0; i < numFish; i++)
	{
		sins.push_back(SinFactory((int)((rand()%6))));	//create a bunch more sins and add to vector
	}

	targetImage = SinFactory(tNum);				//Make a copy of targetSin so it's image can be 
	targetImage->setX(GAME_WIDTH*0.4);			// produced in the UI to be found
	targetImage->setY(GAME_HEIGHT*0.08);

	startTime = GetTickCount();
}

//=============================================================================
// Update all game items
//=============================================================================
void FindIt::update()
{
	//If the target is found, then start the new level
	if (targetSin->Update())
	{
		time += 5;
		if (time > 50)
		{
			time = 50;
		}
		level++;
		//NewRound();
		isFound = true;
	}
	if (!isFound)
	{
		if (GetTickCount() > startTime + 1000)
		{
			startTime = GetTickCount();			//The timer goes down every second
			time--;
		}
		std::vector<VisualSin *>::iterator sinIt;
		for (sinIt = sins.begin(); sinIt != sins.end();)
		{
			(*sinIt)->update(frameTime * 4);
			(*sinIt)->Move(frameTime);
			if ((*sinIt)->Update())
			{
				delete (*sinIt);
				time -= 5;
				sinIt = sins.erase(sinIt);
				isTimeChanged = true;
				tTimer = GetTickCount();
				break;
			}
			else
			{
				++sinIt;
			}
		}
		
		targetSin->Move(frameTime);
	}
	else
	{
		//Delete all non-target sins
		std::vector<VisualSin*>::iterator sinIt;
		for (sinIt = sins.begin(); sinIt != sins.end(); sinIt++)
		{
			delete (*sinIt);
		}
		sins.clear();

		//Pause 2 seconds and then move onto the next level
		if (GetTickCount() > startTime + 2000)
		{
			startTime = GetTickCount();			//The timer goes down every second
			isFound = false;
			NewRound();
		}
	}
	
	targetSin->update(frameTime * 4);
	if (isTimeChanged && GetTickCount() > tTimer + 300)
	{
		isTimeChanged = false;
	}

	if (time <= 0)
	{
		time = 0;
		gameOver = true;
		
		//RecordScore();
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

	targetSin->draw();
	std::vector<VisualSin*>::iterator sinIt;
	for(sinIt = sins.begin(); sinIt != sins.end(); sinIt++)
	{
		(*sinIt)->draw();
		
	}

	CombineString(timer, "Time: ", " ", (int)time);
	dxText->print(timer, GAME_WIDTH *0.01, GAME_HEIGHT*0.1);

	if (isTimeChanged)
	{
		dxText->print("-5", GAME_WIDTH *0.15, GAME_HEIGHT*0.18);
	}
	CombineString(timer, "Level: ", "", level);
	dxText->print(timer, GAME_WIDTH *0.7, GAME_HEIGHT*0.1);
	dxText->print("FIND!", GAME_WIDTH*0.4, GAME_HEIGHT*0.01);
	targetImage->draw();
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void FindIt::releaseAll()
{
    dxText->onLostDevice();
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
	dxText->onResetDevice();
    Game::resetAll();
    return;
}


VisualSin* FindIt::SinFactory(int i)
{
	VisualSin * sin;
	sin = new VisualSin();

	if(!sin->initialize(this, 100, 100, 3, &sinTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sin texture"));

	//Positions of the buttons
	float tX = rand() % (GAME_WIDTH - 100);
	float tY = rand() % ((int)(GAME_HEIGHT * 0.8) - 100) + GAME_HEIGHT*0.2;

	sin->setFrames(i, i);
	sin->setCurrentFrame(i);
	sin->setX(tX);
	sin->setY(tY);
	return sin;
}

void FindIt::NewRound()
{
	
	if (level%10 == 0)
	{
		numFish = level/10 * 8;
	}
	if (numFish > 50)
	{
		numFish = 50;
	}

	int tNum = (int)((rand() % 4));	//Generate random number for target sin
	targetSin = SinFactory(tNum);				//Create target sin

	for (int i = 0; i < numFish; i++)
	{
		sins.push_back(SinFactory((int)((rand() % 6))));	//create a bunch more sins and add to vector
	}

	targetImage = SinFactory(tNum);				//Make a copy of targetSin so it's image can be 
	targetImage->setX(GAME_WIDTH*0.4);			// produced in the UI to be found
	targetImage->setY(GAME_HEIGHT*0.08);

}

