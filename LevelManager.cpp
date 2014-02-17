#include "LevelManager.h"
#include "spacewar.h"
#include "Level1.h"
#include "MainMenu.h"
#include "GreedLevel.h"
#include "Level7.h"

LevelManager::LevelManager()
{	
	//Initialize();
	//To add more levels change numOfLvls and edit LevelFactory
	currentLvlNum = 0;
	numOfLvls = 5;
	for(int i = 0; i < numOfLvls; i++)
	{
		levels.push_back(LevelFactory(i));
	}
	//To demonstrate a level: change number to 2 or 3 depending on if you put both of your lvls in there
	currentLevel = levels[4];
}

LevelManager::~LevelManager()
{
	for(lvlIt = levels.begin(); lvlIt < levels.end(); lvlIt++)
	{
		(*lvlIt)->deleteAll();
	}
}


//=============================================================================
// Window message handler
//=============================================================================
LRESULT LevelManager::messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return currentLevel->messageHandler(hwnd, msg, wParam, lParam);
}


void LevelManager::Initialize(HWND hwnd)
{
	currentLevel->initialize(hwnd);
	input = currentLevel->getInput();
}

void LevelManager::GoToLevel(int lvlNumber)
{
	currentLvlNum = lvlNumber;
	//currentLevel->deleteAll();
	currentLevel = levels[lvlNumber];
	currentLevel->initialize(hwnd);
}

int LevelManager::getCurrentLevel()
{
	int count = 0;
	for(lvlIt = levels.begin(); lvlIt < levels.end(); lvlIt++)
	{
		count++;
		if(currentLevel == *lvlIt)
		{
			return count;
		}
	}
	return 0;
}

void LevelManager::Update(HWND hd)
{

	hwnd = hd;
	if(currentLvlNum == 0)
	{
		MainMenu *menu;
		menu = (MainMenu*) levels[0];
		int lvl = menu->ButtonListener();
		if(lvl != 0)
		{
			GoToLevel(lvl);
		}
	}
	currentLevel->run(hwnd);	
	
	if(currentLvlNum != 0)
	{
		if(currentLevel->getInput()->wasKeyPressed(VK_ESCAPE))
		{
			GoToLevel(0);
		}
	}
}

Game* LevelManager::LevelFactory(int lvl)
{
	//To add more levels, just make a new case and put in the constructor as done in the first 2

	Game * tGame;
	switch(lvl)
	{
	case 0:
		tGame = new MainMenu();
		break;
	case 1:
		tGame = new Level1();
		break;
	case 2:
		tGame = new GreedLevel();
		break;
	case 3:
		tGame = new Spacewar;
		break;
	case 4:
		tGame = new Level7();
		break;
	default:
		break;
	};

	return tGame;
}