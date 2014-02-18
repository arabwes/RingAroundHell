#include "SSenemy.h"

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
	if(move)
	{
		velocity.x -= enemyNS::SPEED2 * frameTime;
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