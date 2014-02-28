#include "Enemy.h"

Enemy::Enemy() :Entity()
{
	spriteData.x=enemyNS::X;
	spriteData.y=enemyNS::Y;
	spriteData.width=enemyNS::WIDTH;
	spriteData.height=enemyNS::HEIGHT;
	velocity.x=0;
	frameDelay=enemyNS::ENEMY_ANIMATION_DELAY;
	startFrame= enemyNS::ENEMY_START_FRAME;
	endFrame=enemyNS::ENEMY_END_FRAME;
	currentFrame=startFrame;
	mass=enemyNS::MASS1;
	move=false;
}
bool Enemy::initialize(Game *gamePtr,int width,int height,int ncols,
	TextureManager *textureM)
{
	enemy.initialize(gamePtr->getGraphics(),width,height,ncols,textureM);
	enemy.setFrames(enemyNS::ENEMY_START_FRAME,enemyNS::ENEMY_END_FRAME);
	enemy.setCurrentFrame(enemyNS::ENEMY_START_FRAME);
	enemy.setFrameDelay(enemyNS::ENEMY_ANIMATION_DELAY);
	return (Entity::initialize(gamePtr,width,height,ncols,textureM));
}
void Enemy::draw()
{
	Image::draw();
}

void Enemy::update(float frameTime)
{
	if(move&&eID==1)
	{
		velocity.x -= enemyNS::SPEED1* frameTime;
	}
	else if(move&&eID==2)
	{
		velocity.x -= enemyNS::SPEED2* frameTime;
	}
	else if(move&&eID==3)
	{
		velocity.x -= enemyNS::SPEED3* frameTime;
	}
	else if(move&&eID==4)
	{
		velocity.x -= enemyNS::SPEED4* frameTime;
	}

	spriteData.x += frameTime * velocity.x;
	if (spriteData.x > GAME_WIDTH)           
	    spriteData.x = -enemyNS::WIDTH;       
	else if (spriteData.x < -enemyNS::WIDTH)  
	    spriteData.x = GAME_WIDTH;           
}
void Enemy::setmoving(bool m)
{
	move=m;
}
void Enemy::seteID(int e)
{
	eID=e;
}