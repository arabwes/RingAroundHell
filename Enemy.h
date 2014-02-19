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
	const int Y = 300;//screen location
	const int TEXTURE_COLS=0;//number of columns in the sprit sheet
	const int ENEMY_START_FRAME=0;//ship start frame 
	const int ENEMY_END_FRAME=0;//ship end frame
	const int ENEMY_ANIMATION_DELAY=0.5;
	const float MASS1=150;
	const float MASS2=100;
	const float MASS3=50;
	const float SPEED1 =15;
	const float SPEED2 =15;
	enum DIRECTION { NONE,LEFT,RIGHT};
}

class Enemy : public Entity
{
protected:	
	enemyNS::DIRECTION derection;
	Image enemy;
	bool move;
public:
	Enemy();
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);
	void update(float frameTime);
	void setmoving(bool m);
};
#endif