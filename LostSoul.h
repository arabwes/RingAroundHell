#ifndef ENEMY_H
#define ENEMY_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace enemyNS
{
	const int WIDTH=92;//with of each frame 
	const int HEIGHT=172;//height of each frame
	const int X = GAME_WIDTH/2 - WIDTH/2;//screen location
	const int Y = GAME_HEIGHT/2 - HEIGHT/2;//screen location
	const int TEXTURE_COLS=0;//number of columns in the sprit sheet
	const int ENEMY_START_FRAME=0;//ship start frame 
	const int ENEMY_END_FRAME=0;//ship end frame
	const float MASS1=150;
	const float MASS2=100;
	const float MASS3=50;
	const float SPEED1 =100;
	const float SPEED2 =75;
	enum DIRECTION { NONE,LEFT,RIGHT};
}

class Enemy : Entity
{
protected:
	float preLachX,preLachY;
	enemyNS::DIRECTION derection;
	Image enemy;
public:
	void toOldPosition()
	{
		spriteData.x=preLachX;
		spriteData.y=preLachY;
	}
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);
};
#endif