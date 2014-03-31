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
	if (!backGroundTexture.initialize(graphics,"ArtAssets//SeaFloor2.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if (!sinTextures.initialize(graphics,"ArtAssets//FishSprites.png"))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if (!background.initialize(graphics,0,0,0,&backGroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	
	
	int tNum = (int)((rand() % 4) + 12) * 2;	//Generate random number for target sin
	targetSin = SinFactory(tNum);				//Create target sin
	//sins.push_back(targetSin);					//Insert target sin first so it is always rendered in the back
	for(int i = 0; i < numFish; i++)
	{
		sins.push_back(SinFactory((int)((rand()%12)*2)));	//create a bunch more sins and add to vector
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
	if (GetTickCount() > startTime + 1000)
	{
		startTime = GetTickCount();			//The timer goes down every second
		time--;
	}
	std::vector<VisualSin *>::iterator sinIt;
	for(sinIt = sins.begin(); sinIt != sins.end(); )
	{
		(*sinIt)->update(frameTime * 4);
		(*sinIt)->Move(frameTime);
		if((*sinIt)->Update())
		{
			delete (*sinIt);
			time -= 5;
			sinIt = sins.erase(sinIt);
			break; 
		}
		else
		{
			++sinIt;
		}
	}
	targetSin->update(frameTime * 4);
	targetSin->Move(frameTime);

	//If the target is found, then start the new level
	if (targetSin->Update())
	{
		time += 5;
		if (time > 50)
		{
			time = 50;
		}
		level++;
		NewRound();
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
	
	std::vector<VisualSin*>::iterator sinIt;
	for(sinIt = sins.begin(); sinIt != sins.end(); sinIt++)
	{
		(*sinIt)->draw();
	}
	targetSin->draw();

	CombineString(timer, "Time: ", " ", (int)time);
	dxText->print(timer, GAME_WIDTH *0.01, GAME_HEIGHT*0.1);
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

	if(!sin->initialize(this, 100, 100, 8, &sinTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sin texture"));

	//Positions of the buttons
	float tX = rand() % (GAME_WIDTH - 100);
	float tY = rand() % ((int)(GAME_HEIGHT * 0.8) - 100) + GAME_HEIGHT*0.2;

	sin->setFrames(i, i+1);
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

	std::vector<VisualSin*>::iterator sinIt;
	for (sinIt = sins.begin(); sinIt != sins.end(); sinIt++)
	{
		delete (*sinIt);
	}
	sins.clear();

	int tNum = (int)((rand() % 4) + 12) * 2;	//Generate random number for target sin
	targetSin = SinFactory(tNum);				//Create target sin
	//sins.push_back(targetSin);					//Insert target sin first so it is always rendered in the back
	for (int i = 0; i < numFish; i++)
	{
		sins.push_back(SinFactory((int)((rand() % 12) * 2)));	//create a bunch more sins and add to vector
	}

	targetImage = SinFactory(tNum);				//Make a copy of targetSin so it's image can be 
	targetImage->setX(GAME_WIDTH*0.4);			// produced in the UI to be found
	targetImage->setY(GAME_HEIGHT*0.08);

}

