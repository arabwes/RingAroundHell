#ifndef _LEVELMANAGER_H       // Prevent multiple definitions if this 
#define _LEVELMANAGER_H       // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

/*	Level manager manages levels and easily jumps inbetween levels
	To add a level to the manager, insert it as a case in the LevelFactor function
*/
class LevelManager;

#include <vector>
#include <string>
#include <fstream>
#include "game.h"
#include "constants.h"
#include "InputManager.h"
#include "input.h"
#include <vector>

class LevelManager
{
    // LevelManager properties
  private:
    int currentLvlNum;	//Number of current Level
	int numOfLvls;
	std::vector<Game*> levels;
	std::vector<Game*>::iterator lvlIt;
    Game *currentLevel;     // save pointer to graphics
    bool    initialized;    // true when successfully initialized
    HRESULT hr;             // standard return type
	HWND hwnd;
	Game* LevelFactory(int );
  public:	  
	InputManager inputMgr;
	Input *input;
    // Constructor
    LevelManager();

	// Window message handler
    LRESULT messageHandler( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

	void GoToLevel(int levelNumber);	//Goes to specified level
	void Initialize(HWND hwnd);
	int getCurrentLevel();						//Returns current level number
	void Update(HWND hd);					//Plays current level from beginning
	// Destructor
    ~LevelManager();


};


#endif